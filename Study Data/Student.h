#pragma once
#include <vector>
#include <string>
#include "StudyData.h"
class Student :
	public StudyData
{
public:
	Student();
	virtual ~Student();

	std::vector<int> courses;
	// Inherited via StudyData
	virtual void save(std::ostream & ostream) override;

	bool operator == (const Student& student)const;

};

