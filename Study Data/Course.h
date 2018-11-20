#pragma once
#include <vector>
#include <string>
#include "StudyData.h"
class Course :
	public StudyData
{
public:
	Course() = default;
	virtual ~Course() = default;
	int teacher;
	std::vector<int> students;
	// Inherited via StudyData
	virtual void save(std::ostream & ostream) override;

	bool operator == (const Course& rhs) const;
	
};

