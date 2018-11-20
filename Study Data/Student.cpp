#include "Student.h"



Student::Student()
{
}


Student::~Student()
{
}

void Student::save(std::ostream & ostream)
{
	ostream << "Student\t";
	ostream << id << '\t' << name << '\t'<<courses.size()<<'\t';
	for (auto& i : courses)
	{
		ostream << i << '\t';
	}
}

bool Student::operator==(const Student & student) const
{
	return student.id == id &&
		student.name == name &&
		student.courses  == courses;
}
