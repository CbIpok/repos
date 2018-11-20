#include <deque>
#include <mutex>
#pragma once
class DataFIFO final
{
public:
	DataFIFO(size_t bufferSize, size_t maxBlocks); //выделяет буфер данных заданного размера, с максимальным количеством блоков.
	~DataFIFO();
	void * getFree(size_t size);// метод, вызываемый потоком-писателем
	void addReady(void * data); 
	void * getReady(size_t & size);
	void addFree(void * data); 
private:
	std::mutex _BlockSizeInfoMutex;
	std::mutex _FIFOisReading;
	std::mutex _FIFOisWriting;
	bool _isReadBlockRented = false;
	bool _isWriteBlockRented = false;
	bool _isSpaceAvailable(size_t size);
	std::deque<size_t> _blockSizeInfo;
	size_t _bufferSize;
	size_t _trash;//is end of buffer fragmented and where
	size_t _start;
	size_t _end;
	char* _buffer;
};

