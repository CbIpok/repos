#include "pch.h"
#include "DataFIFO.h"
#include <string.h>
#include <vector>
#include <thread>

void reader(DataFIFO& dataFIFO, std::vector<int>& source)
{
	size_t i = 0;
	while (i < source.size())
	{
		int* data = (int*)dataFIFO.getFree(sizeof(int));
		if (data != nullptr)
		{
			*data = source[i];
			dataFIFO.addReady(data);
			i++;
		}

	}


}

void writer(DataFIFO& dataFIFO, std::vector<int>& dist, size_t size)
{
	while (size > 0)
	{
		size_t sizeOfInt;
		int* data = (int*)dataFIFO.getReady(sizeOfInt);
		if (data != nullptr)
		{
			int cdata = *data;
			dataFIFO.addFree(data);
			dist.push_back(cdata);
			size--;
		}
	}
}

TEST(FIFOwrite, DoubleUnCorrect) {
	DataFIFO dataFIFO(10000, 100);
	ASSERT_NE(dataFIFO.getFree(100), nullptr);
	ASSERT_EQ(dataFIFO.getFree(100), nullptr);
}

TEST(FIFOWrite, DoubleCorrect)
{
	DataFIFO dataFIFO(10000, 100);
	void* data = dataFIFO.getFree(100);
	ASSERT_NE(data, nullptr);
	dataFIFO.addReady(data);
	data = dataFIFO.getFree(100);
	ASSERT_NE(data, nullptr);

}

TEST(FIFOreadWrite, correctSingle)
{
	DataFIFO dataFIFO(10000, 100);
	char* data = (char*)dataFIFO.getFree(4);
	strcpy_s(data,10, "123");
	dataFIFO.addReady(data);
	size_t size;
	char* resData;
	resData = (char*)dataFIFO.getReady(size);
	ASSERT_EQ(size, 4);
	ASSERT_EQ(data, resData);
	ASSERT_EQ(strcmp("123", resData), 0);
}


TEST(FIFOreadWrite, correctDouble)
{
	DataFIFO dataFIFO(10000, 100);
	char* data = (char*)dataFIFO.getFree(4);
	strcpy_s(data,10, "123");
	dataFIFO.addReady(data);
	size_t size;
	char* resData;
	resData = (char*)dataFIFO.getReady(size);
	ASSERT_EQ(size, 4);
	ASSERT_EQ(data, resData);
	ASSERT_EQ(strcmp("123", resData), 0);
	dataFIFO.addFree(resData);

	data = (char*)dataFIFO.getFree(4);
	strcpy_s(data,10, "456");
	dataFIFO.addReady(data);
	resData = (char*)dataFIFO.getReady(size);
	ASSERT_EQ(size, 4);
	ASSERT_EQ(data, resData);
	ASSERT_EQ(strcmp("456", resData), 0);
	dataFIFO.addFree(resData);

}


TEST(FIFOEndJump, singleJump)
{
	DataFIFO dataFIFO(10000, 100);
	void* data = dataFIFO.getFree(9000);
	dataFIFO.addReady(data);
	size_t size;
	data = dataFIFO.getReady(size);
	ASSERT_EQ(size, 9000);
	dataFIFO.addFree(data);
	data = dataFIFO.getFree(8000);
}

TEST(FIFOstartJump, singleJump)
{
	DataFIFO dataFIFO(10000, 100);
	void* data = dataFIFO.getFree(9000);
	dataFIFO.addReady(data);
	size_t size;
	data = dataFIFO.getReady(size);
	ASSERT_EQ(size, 9000);
	dataFIFO.addFree(data);
	data = dataFIFO.getFree(8000);
	dataFIFO.addReady(data);
	data = dataFIFO.getReady(size);
	ASSERT_EQ(size, 8000);
	dataFIFO.addFree(data);
}


TEST(FIFOreadWrite, mutithread)
{
	DataFIFO dataFIFO(1000, 100);
	std::vector<int> source;
	std::vector<int> dist;
	for (size_t i = 0; i < 100000; i++)
	{
		source.push_back(i);
	}
	size_t size = source.size();
	std::thread treadReader(reader, std::ref(dataFIFO), std::ref(source));
	std::thread treadWriter(writer, std::ref(dataFIFO), std::ref(dist), size);
	treadReader.join();
	treadWriter.join();
	for (size_t i = 0; i < size; i++)
	{
		ASSERT_EQ(source[i], dist[i]);
	}
}
