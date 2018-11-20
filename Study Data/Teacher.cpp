#include "Teacher.h"



Teacher::Teacher()
{
}


Teacher::~Teacher()
{
}

void Teacher::save(std::ostream & ostream)
{
	ostream << "Teacher\t";
	ostream << id << '\t' <<name << '\t' << experience << '\t' << courses.size() << '\t';
	for (auto& i : courses)
	{
		ostream << i << '\t';
	}
}

bool Teacher::operator==(const Teacher & teacher) const
{
	return teacher.id == id &&
		teacher.name == name &&
		teacher.experience == experience &&
		teacher.courses == courses;

}
