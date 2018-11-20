#include "CourseReader.h"
#include "Course.h"


CourseReader::CourseReader()
{
}


CourseReader::~CourseReader()
{
}

StudyData* CourseReader::read(std::istream& istream)
{
	if (!istream.good())
	{
		return nullptr;
	}
	Course* course = new Course();
	istream >> (*course).id;
	istream >> (*course).name;
	istream >> (*course).teacher;
	size_t size;
	istream >> size;
	for (size_t i = 0; i < size; i++)
	{
		int student;
		istream >> student;
		(*course).students.push_back(student);
	}
	return course;
}
