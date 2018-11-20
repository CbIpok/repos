#include "pch.h"
#include "Student.h"
#include "Course.h"
#include "Teacher.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <Reader.h>
using namespace std;
class TestCaseFixing : public ::testing::Test {
protected:
	virtual void SetUp(void) {
		student.courses.push_back(1);
		student.name = "student";
		student.id = 1;
		teacher.id = 1;
		teacher.experience = 1;
		teacher.name = "teacher";
		teacher.courses.push_back(1);
		course.id = 0;
		course.name = "course";
		course.teacher = 1;
		course.students.push_back(1);
		studyData.push_back(&student);
		studyData.push_back(&teacher);
		studyData.push_back(&course);
	}
	virtual void TearDown(void) {
		// очистка после прогона очередного теста
	}

	Student student;
	Teacher teacher;
	Course course;
	std::vector<StudyData*> studyData;

	ostringstream studyDataStream;
	string res;
};

TEST_F(TestCaseFixing, CreateTestStudent) {

	for (auto& i : studyData)
	{
		i->save(studyDataStream);
		studyDataStream << endl;
	}
	istringstream studyDataInput(studyDataStream.str());
	vector<StudyData*> tstudyData;
	Reader reader;
	for (size_t i = 0; i < 3; i++)
	{
		tstudyData.push_back(reader.read(studyDataInput));
	}
	ASSERT_EQ(*(Student*)tstudyData.at(0), student);
	//ASSERT_EQ(*(Teacher*)tstudyData.at(1), teacher);
	//ASSERT_EQ(*(Course*)tstudyData.at(2), course);

}

TEST_F(TestCaseFixing, CreateTestTeacher) {

	for (auto& i : studyData)
	{
		i->save(studyDataStream);
		studyDataStream << endl;
	}
	istringstream studyDataInput(studyDataStream.str());
	vector<StudyData*> tstudyData;
	Reader reader;
	for (size_t i = 0; i < 3; i++)
	{
		tstudyData.push_back(reader.read(studyDataInput));
	}
	//ASSERT_EQ(*(Student*)tstudyData.at(0), student);
	ASSERT_EQ(*(Teacher*)tstudyData.at(1), teacher);
	//ASSERT_EQ(*(Course*)tstudyData.at(2), course);

}


TEST_F(TestCaseFixing, CreateTestCourse) {

	for (auto& i : studyData)
	{
		i->save(studyDataStream);
		studyDataStream << endl;
	}
	istringstream studyDataInput(studyDataStream.str());
	vector<StudyData*> tstudyData;
	Reader reader;
	for (size_t i = 0; i < 3; i++)
	{
		tstudyData.push_back(reader.read(studyDataInput));
	}
	//ASSERT_EQ(*(Student*)tstudyData.at(0), student);
	//ASSERT_EQ(*(Teacher*)tstudyData.at(1), teacher);
	ASSERT_EQ(*(Course*)tstudyData.at(2), course);

}


TEST(StudyData, EmptyInput)
{
	istringstream emptyStream;
	vector<StudyData*> tstudyData;
	Reader reader;
	for (size_t i = 0; i < 3; i++)
	{
		tstudyData.push_back(reader.read(emptyStream));
	}
	for (auto& i : tstudyData)
	{
		ASSERT_EQ(nullptr, i);
	}
}
