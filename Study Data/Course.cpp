#include "Course.h"



//Course::Course()
//{
//}


//Course::~Course()
//{
//}

void Course::save(std::ostream & ostream)
{
	ostream << "Course\t";
	ostream << id << '\t' << name << '\t' << teacher << '\t' << students.size()<< '\t';
	for (auto& i : students)
	{
		ostream << i << '\t';
	}
}

bool Course::operator==(const Course & rhs) const
{
	return rhs.id == id &&
		rhs.name == name &&
		rhs.teacher == rhs.teacher &&
		rhs.students == students;
}
