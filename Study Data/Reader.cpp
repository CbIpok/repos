#include "Reader.h"

Reader::Reader()
{
	_studyDataReaders.emplace("Student", new StudentReader());
	_studyDataReaders.emplace("Teacher", new TeacherReader());
	_studyDataReaders.emplace("Course", new CourseReader());
}

Reader::~Reader()
{

}

StudyData * Reader::read(std::istream& istream)
{
	if (!istream.good())
	{
		return nullptr;
	}
	std::string type;
	istream >> type;
	try
	{
		return _studyDataReaders.at(type)->read(istream);
	}
	catch (const std::out_of_range&)
	{
		return nullptr;
	}
	
}
