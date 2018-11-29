#include "DataFIFO.h"


DataFIFO::DataFIFO(size_t bufferSize, size_t maxBlocks) :
	_bufferSize(bufferSize)
{
	_start =
		_end = 0;
	_buffer = new char[bufferSize];
}

DataFIFO::~DataFIFO()
{
	delete[](_buffer);
}

void * DataFIFO::getFree(size_t size)//метод, вызываемый потоком-читателем.
{
	std::lock_guard<std::mutex> lock(mutex);
	if (_isWriteBlockRented)
	{
		return nullptr;
	}
	_isWriteBlockRented = true;
	if (_isSpaceAvailable(size))
	{
		_blockSizeInfo.push_back(size);
		_end += size;
		return _buffer + _end - size;
	}
	_isWriteBlockRented = false;
	return nullptr;
}

void DataFIFO::addReady(void * data)// метод, вызываемый потоком-читателем.
{
	_isWriteBlockRented &= false;	
}

void * DataFIFO::getReady(size_t & size)//метод, вызываемый потоком-писателем.
{
	std::lock_guard<std::mutex> lock(mutex);
	if (_isReadBlockRented)
	{
		return nullptr;
	}
	_isReadBlockRented = true;
	if (_blockSizeInfo.size() > 0)
	{
		if (isEndOfBuffer())
		{
			_start = 0;
			_trash = 0;
		}
		size = _blockSizeInfo.front();
		return _buffer + _start;
	}
	_isReadBlockRented = false;
	return nullptr;
}

void DataFIFO::addFree(void * data)//метод, вызываемый потоком-писателем.
{
	
	std::lock_guard<std::mutex> lock(mutex);
	if (_isReadBlockRented)
	{
		_isReadBlockRented = false;
		_start += _blockSizeInfo.front();
		_blockSizeInfo.pop_front();
	}
	
}

bool DataFIFO::_isSpaceAvailable(size_t size)
{
	if (isPossibleToWrite(size)) //is _end Jump is not requared
	{
		return true;
	}
	if (_start <= _end && _start > size)
	{
		
		_trash = _end;
		_end = 0;
		return true;
	}
	return false;
}



bool DataFIFO::isEndOfBuffer()
{
	return _start == _bufferSize || (_trash != 0 && _start == _trash);
}

bool DataFIFO::isPossibleToWrite(size_t size)
{
	bool isPossibleWriteAfterStart = (_start <= _end && _bufferSize - _end > size);
	bool isPossibleWriteBeforeStart = (_end < _start && (_start - _end) > size);
	return isPossibleWriteAfterStart || isPossibleWriteAfterStart;
}
