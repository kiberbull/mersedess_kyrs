#pragma once
#include <string>
using namespace std;

// Класс Оценка
class Mark
{
private:
	int Id;
	
	int Value;		// Значение оценка
	int StudentId;	// id студента с оценкой
	int SubjectId;	// id предмета

public:
	Mark(int id, int v, int stdid, int subjid);
	Mark(string s);
	Mark(const Mark& m);
	
	int getId();
	int getValue();
	int getStudentId();
	int getSubjectId();

	void setId(int id);
	void setValue(int v);
	void setStudentId(int stdid);
	void setSubjectId(int subjid);

	void setMark(int id, int v, int stdid, int subjid);

	string ToString();
};

