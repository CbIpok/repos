#include <iostream>
#include <fstream>
#include <vector>
#include "Course.h"
#include "Student.h"
#include "Teacher.h"
#include "Reader.h"

using namespace std;
int main()
{
	ifstream ifs("test.txt");
	if (!ifs)
	{
		abort();
	}
	for (size_t i = 0; i < 10; i++)
	{
		Reader reader;
		StudyData* sd = reader.read(ifs);
	}
}