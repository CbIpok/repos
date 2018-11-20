#pragma once
#include <istream>
#include "StudyData.h"


class StudyDataReader
{
public:
	StudyDataReader() = default;
	virtual ~StudyDataReader() = default;
	
	virtual StudyData* read(std::istream& istream) = 0;

private:

};

