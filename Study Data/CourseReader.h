#pragma once
#include "StudyDataReader.h"

class CourseReader :
	public StudyDataReader
{
public:
	CourseReader();
	virtual ~CourseReader();

	// Inherited via StudyDataReader
	virtual StudyData* read(std::istream& istream) override;
};

