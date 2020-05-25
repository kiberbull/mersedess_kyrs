#include <iostream>
#include "Subject.h"
#include "Worker.h"

#include <vector>
#include <fstream>

#pragma once
// ����� ������ �� ����������
class SubjectWorker : Worker
{
public:
	SubjectWorker(string p);

	void Load();
	void Save();

	Subject* getSubjectById(int id);

	int AddSubject(Subject s);
	void DeleteSubjectById(int id);
	bool existId(int id);

	int Count();

	// ��������� ������ �������� ���������
	string* subjectNames();
	// ��������� ������ ������ ���������� � ���������
	string* getInfo();
private:
	string path;
	vector<Subject> subjects;
};

