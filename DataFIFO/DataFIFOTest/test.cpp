#include "pch.h"
#include "DataFIFO.h"
#include <string.h>
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
	strcpy(data, "123");
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
	strcpy(data, "123");
	dataFIFO.addReady(data);
	size_t size;
	char* resData;
	resData = (char*)dataFIFO.getReady(size);
	ASSERT_EQ(size, 4);
	ASSERT_EQ(data, resData);
	ASSERT_EQ(strcmp("123", resData), 0);
	dataFIFO.addFree(resData);

	data = (char*)dataFIFO.getFree(4);
	strcpy(data, "456");
	dataFIFO.addReady(data);
	resData = (char*)dataFIFO.getReady(size);
	ASSERT_EQ(size, 4);
	ASSERT_EQ(data, resData);
	ASSERT_EQ(strcmp("456", resData), 0);
	dataFIFO.addFree(resData);

}


TEST(FIFOEndJump, singleJump)
{

}