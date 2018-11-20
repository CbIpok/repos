#pragma once
#include "StudyDataReader.h"
class TeacherReader :
	public StudyDataReader
{
public:
	TeacherReader();
	virtual ~TeacherReader();

	// Inherited via StudyDataReader
	virtual StudyData* read(std::istream& istream) override;
};

