#include "Mark.h"

Mark::Mark(int id, int v, int stdid, int subjid)
{
	setMark(id, v, stdid, subjid);
}
Mark::Mark(string s)
{
	if (s[s.size() - 1] != ' ') {
		s += " ";
	}
	int last = 0;
	int c = 0;
	for (int i = 0; i < s.size(); i++) {
		if (s[i] == ' ') {
			string p = s.substr(last, i - last);
			last = i + 1;
			switch (c)
			{
			case 0:
				setId(stoi(p));
				break;
			case 1:
				setValue(stoi(p));
				break;
			case 2:
				setStudentId(stoi(p));
				break;
			case 3:
				setSubjectId(stoi(p));
				break;
			default:
				break;
			}
			c++;
		}
	}
}
Mark::Mark(const Mark& m)
{
	setMark(m.Id, m.Value, m.StudentId, m.SubjectId);
}
int Mark::getId()
{
	return Id;
}

int Mark::getValue()
{
	return Value;
}

int Mark::getStudentId()
{
	return StudentId;
}

int Mark::getSubjectId()
{
	return SubjectId;
}

void Mark::setId(int id)
{
	Id = id;
}

void Mark::setValue(int v)
{
	Value = v;
}

void Mark::setStudentId(int stdid)
{
	StudentId = stdid;
}

void Mark::setSubjectId(int subjid)
{
	SubjectId = subjid;
}

void Mark::setMark(int id, int v, int stdid, int subjid)
{
	setId(id);
	setValue(v);
	setStudentId(stdid);
	setSubjectId(subjid);
}

string Mark::ToString()
{
	return to_string(Id) + " " + to_string(Value) + " " + to_string(StudentId) + " " + to_string(SubjectId);
}
