#include "TeacherReader.h"
#include "Teacher.h"


TeacherReader::TeacherReader()
{
}


TeacherReader::~TeacherReader()
{
}

StudyData* TeacherReader::read(std::istream& istream)
{
	if (!istream.good())
	{
		return nullptr;
	}
	Teacher* teacher = new Teacher();
	istream >> (*teacher).id;
	istream >> (*teacher).name;
	istream >> (*teacher).experience;
	size_t size;
	istream >> size;
	for (size_t i = 0; i < size; i++)
	{
		int course;
		istream >> course;
		(*teacher).courses.push_back(course);
	}
	return teacher;
}
