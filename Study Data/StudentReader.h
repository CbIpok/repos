#pragma once
#include "StudyDataReader.h"
class StudentReader :
	public StudyDataReader
{
public:
	StudentReader();
	virtual ~StudentReader();

	// Inherited via StudyDataReader
	virtual StudyData* read(std::istream& istream) override;
};

