#include "StudentReader.h"
#include "Student.h"


StudentReader::StudentReader()
{
}


StudentReader::~StudentReader()
{
}

StudyData* StudentReader::read(std::istream& istream)
{
	if (!istream.good())
	{
		return nullptr;
	}
	Student* student = new Student();
	istream >> (*student).id;
	istream >> (*student).name;
	size_t size;
	istream >> size;
	for (size_t i = 0; i < size; i++)
	{
		int course;
		istream >> course;
		(*student).courses.push_back(course);
	}
	
	return student;
	
}
