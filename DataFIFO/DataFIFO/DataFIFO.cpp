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
	delete(_buffer);
}

void * DataFIFO::getFree(size_t size)//метод, вызываемый потоком-читателем.
{
	_FIFOisWriting.lock();
	if (_isWriteBlockRented)
	{
		_FIFOisWriting.unlock();
		return nullptr;
	}
	_isWriteBlockRented = true;
	if (_isSpaceAvailable(size))
	{
		_BlockSizeInfoMutex.lock();
		_blockSizeInfo.push_back(size);
		_BlockSizeInfoMutex.unlock();
		_end += size;
		_FIFOisWriting.unlock();
		return _buffer + _start;
	}
	_isWriteBlockRented = false;
	_FIFOisWriting.unlock();
	return nullptr;
}

void DataFIFO::addReady(void * data)// метод, вызываемый потоком-читателем.
{
	//end < begin !!
	if (_isWriteBlockRented)
	{
		_isWriteBlockRented = false;
	}
}

void * DataFIFO::getReady(size_t & size)//метод, вызываемый потоком-писателем.
{
	_FIFOisReading.lock();
	if (_isReadBlockRented)
	{
		_FIFOisReading.unlock();
		return nullptr;
	}
	_isReadBlockRented = true;
	if (_blockSizeInfo.size() > 0)
	{
		size = _blockSizeInfo.front();
		_FIFOisReading.unlock();
		return _buffer + _start;
	}
	_isReadBlockRented = false;
	_FIFOisReading.unlock();
	return nullptr;
}

void DataFIFO::addFree(void * data)//метод, вызываемый потоком-писателем.
{
	if (_isReadBlockRented)
	{
		_isReadBlockRented = false;
		_start += _blockSizeInfo.front();
		_BlockSizeInfoMutex.lock();
		_blockSizeInfo.pop_front();
		_BlockSizeInfoMutex.unlock();
	}
}

bool DataFIFO::_isSpaceAvailable(size_t size)
{
	if (_start < _end && _bufferSize - _end > size)
	{
		return true;
	}
	if (_start < _end)
	{
		_trash = _end;
		_end = 0;
	}
	return (_start - _end) > size;
}
