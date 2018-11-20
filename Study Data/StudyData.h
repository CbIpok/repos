#pragma once
#include <istream>
#include <ostream>

class StudyData
{
public:
	StudyData() = default;
	virtual ~StudyData() = default;

	virtual void save(std::ostream& ostream) = 0;

	int id;
	std::string name;

private:

};
