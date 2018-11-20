#pragma once
#include <unordered_map>
#include <string>
#include <sstream>
#include "StudentReader.h"
#include "TeacherReader.h"
#include "CourseReader.h"

class Reader final
{
public:
	Reader();
	~Reader();
	StudyData * read(std::istream& istream);
	

private:
	std::unordered_map<std::string, StudyDataReader*> _studyDataReaders;
};
