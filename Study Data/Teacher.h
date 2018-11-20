#pragma once
#include <vector>
#include <string>
#include "StudyData.h"
class Teacher :
	public StudyData
{
public:
	Teacher();
	~Teacher();

	int experience;
	std::vector<int> courses;
	// Inherited via StudyData
	virtual void save(std::ostream & ostream) override;

	bool operator == (const Teacher& teacher) const;
};

