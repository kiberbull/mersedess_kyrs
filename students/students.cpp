#include <iostream>
#include <time.h>
#include <string>
#include <windows.h>;
#include "StudentsWorker.h"
#include "SubjectWorker.h"
#include "MarksWorker.h"

using namespace std;

//Проверка строки на правильность ввода (пустая строка)
bool enterString(string* s, string text) {
	cout << text << ": ";
	cin >> *s;
	if (s->size() == 0) {
		cout << "Ошибка ввода, повторите ввод: ";
		cin >> *s;
		if (s->size() == 0) {
			cout << "Ошибка ввода\n";
			return false;
		}
	}
	return true;
}

//Проверка правильности ввода даты
bool checkDate(string str) {
	static std::regex rgx{ R"((0[1-9]|[12][0-9]|3[01])[- /.](0[1-9]|1[012])[- /.](19|20\d\d))" };
	std::smatch res;
	if (std::regex_search(str, res, rgx))
	{		
		return true;
	}
	return false;
}

//Вывод меню
void menu() {
	cout << "Введите команду:\n1, если хотите добавить студента\n";
	cout << "2, если хотите удалить студента\n";
	cout << "3, если хотите добавить предмет\n";
	cout << "4, если хотите удалить предмет\n";
	cout << "5, если хотите добавить оценку\n";
	cout << "6, если хотите вывести всех студентов\n";
	cout << "7, если хотите вывести все предметы\n";
	cout << "8, если хотите выполнить вариант №20\n";
	cout << "0, если хотите выйти из программы\n";
}
void menuPrintStud() {
	cout << "Введите 1, если хотите вывести только имена студентов с их id\n";
	cout << "Введите 2, если хотите вывести всю информацию о студентах\n";
	cout << "Введите 3, если хотите вывести всю информацию о студентах с оценками\n";
}
void menuPrintSubj() {
	cout << "Введите 1, если хотите вывести только названия предметов с их id\n";
	cout << "Введите 2, если хотите вывести всю информацию о предметах\n";
}

//Выставление оценки
void SetMark(StudentsWorker* sw, SubjectWorker* sbw, MarksWorker * mw) {
	int stdid, sbjid, val, id;
	cout << "Введите id студента ";
	cin >> stdid;
	if (!sw->existId(stdid)) {
		cout << "Нет такого студента" << endl;
	}
	cout << "Введите id предмета ";
	cin >> sbjid;
	if (!sbw->existId(sbjid)) {
		cout << "Нет такого предмета" << endl;
	}
	cout << "Введите оценку ";
	cin >> val;
	id = mw->AddMark(Mark(-1, val, stdid, sbjid));
	cout << "Выставлена оценка с id = " << id << endl;
}

// Процедура вывода информации о предметах
void PrintSubj(StudentsWorker * sw, SubjectWorker * sbw, MarksWorker* mw) {
	int comand;
	string* list;
	menuPrintSubj();
	cin >> comand;
	switch (comand)
	{
	case 1:
		list = sbw->subjectNames();
		for (int i = 0; i < sbw->Count(); i++) {
			cout << list[i] << endl;
		}
		break;

	case 2:
		list = sbw->getInfo();
		for (int i = 0; i < sbw->Count(); i++) {
			cout << list[i] << endl;
		}
		break;
	default:
		break;
	}
}
// Добавление нового студента
void AddStud(StudentsWorker * sw) {
	string name, scname, patro, dob, dor, fac, group, rb, id;
	char g;
	enterString(&name, "Введите имя");
	enterString(&scname, "Введите фамилию");
	enterString(&patro, "Введите отчество");

	cout << "Введите пол (m или f) ";
	cin >> g;
	if (g != 'm' && g != 'f') {
		cout << "Ошибка ввода, повторите ввод (m или f): " << endl;
		cin >> g;
		if (g != 'm' && g != 'f') {
			cout << "Ошибка ввода\n";
			return;
		}
	}
	cout << "Введите дату рождения в формате ДД.ММ.ГГГГ: ";
	cin >> dob;
	if (!checkDate(dob)) {
		cout << "Ошибка ввода, повторите ввод: ";
		cin >> dob;
		if (!checkDate(dob)) {
			"Ошибка ввода\n";
			return;
		}
	}	

	struct tm tim;
	time_t tt = time(NULL);
	localtime_s(&tim, &tt);
	string now_day = to_string(tim.tm_mday);
	string now_month = to_string(tim.tm_mon + 1);
	if (now_day.size() == 1) {
		now_day = "0" + now_day;
	}
	if (now_month.size() == 1) {
		now_month = "0" + now_month;
	}

	dor = now_day + "/" + now_month + "/" + to_string(1900 + tim.tm_year);

	enterString(&fac, "Введите факультет");
	enterString(&group, "Введите группу");
	enterString(&rb, "Введите номер зачетки");
	id = sw->AddStudent(Student(-1, name, scname, patro, g, Date(dob), dor, fac, group, rb));

	cout << "Студент добавлен под id = " << sw->getStudentByRecordBook(rb)->getId() << endl;
}
// Удаление студента
void DeleteStud(StudentsWorker * sw) {
	int id;
	cout << "Введите id студента для удаления ";
	cin >> id;
	if (sw->existId(id)) {
		sw->DeleteStudentById(id);
	}
	else {
		cout << "Нет студента с таким id";
	}
}
// Вывод информации о студентах
void PrintStud(StudentsWorker * sw, SubjectWorker * sbw, MarksWorker* mw) {
	vector<string> list;
	char g = 'b';
	vector<int> m, ids;
	vector<pair<int, string> > a;
	int comand;
	menuPrintStud();
	cin >> comand;
	cout << "Введите b, если хотите вывести всех студентов\n        m, если хотите вывести только студентов мужского пола\n        f, если хотите вывести студентов женского пола\n";
	cin >> g;
	if (g != 'b' && g != 'f' && g != 'm') {
		cout << "Ошибка ввода";
		return;
	}
	switch (comand)
	{
	case 1:
		list = sw->studNames(g);
		for (int i = 0; i < list.size(); i++) {
			cout << list[i] << endl;
		}
		break;

	case 2:
		list = sw->getInfo(g);
		for (int i = 0; i < list.size(); i++) {
			cout << list[i] << endl;
		}
		break;
	case 3:
		ids = sw->getAllId(g);
		list = sw->getInfo(g);
		for (int i = 0; i < list.size(); i++) {
			cout << list[i] << " Оценки: ";

			m = mw->getMarksForStudent(ids[i]);
			for (auto j : m) {
				cout << j << ' ';
			}
			cout << endl;
		}
		break;
	default:
		break;
	}
}

// Добавление предмета
void AddSubj(SubjectWorker * sbw) {
	string name, info;
	enterString(&name, "Введите название");
	enterString(&info, "Введите информацию");

	int id = sbw->AddSubject(Subject(-1, name, info));

	cout << "Предмет добавлен под id = " << id << endl;
}
// Удаление предмета
void DeleteSubj(SubjectWorker * sbw) {
	int id;
	cout << "Введите id предмета для удаления ";
	cin >> id;
	if (sbw->existId(id)) {
		sbw->DeleteSubjectById(id);
	}
	else {
		cout << "Нет предмета с таким id\n";
	}
}

//выполнение варианта 20
void CourseWork(StudentsWorker* sw, SubjectWorker* sbw, MarksWorker* mw) {
	vector<string> list;
	char g = 'b';
	vector<int> m, ids;
	vector<pair<int, string> > a;
	cout << "Введите b, если хотите вывести всех студентов\n        m, если хотите вывести только студентов мужского пола\n        f, если хотите вывести студентов женского пола\n";
	cin >> g;
	if (g != 'b' && g != 'f' && g != 'm') {
		cout << "Ошибка ввода";
		return;
	}
	else {
		ids = sw->getAllId(g);
		list = sw->getInfo(g);
		a.resize(list.size());
		for (int i = 0; i < list.size(); i++) {
			a[i].second = list[i];
			m = mw->getMarksForStudent(ids[i]);
			double sum = 0;
			for (auto j : m) {
				sum += j;
			}
			if (m.size() == 0) {
				a[i].first = -1;
			}
			else {
				a[i].first = sum / m.size();
			}
		}
		sort(a.begin(), a.end());
		reverse(a.begin(), a.end());
		for (auto i : a) {
			cout << i.second << " Средний балл: " << i.first << endl;
		}
	}

}

int main()
{
	SetConsoleCP(1251); 
	SetConsoleOutputCP(1251); 
	menu();
	StudentsWorker sw("Students.txt");
	SubjectWorker sbw("Subjects.txt");
	MarksWorker mw("Marks.txt");

	sw.Load();
	sbw.Load();
	mw.Load();
	int id, comand;

	int c;
	cin >> c;
	while (1) {
		switch (c)
		{
		case 1:
			AddStud(&sw);
			break;
		case 2:
			DeleteStud(&sw);
			break;
		case 3:
			AddSubj(&sbw);
			break;
		case 4:
			DeleteSubj(&sbw);
			break;
		case 5:
			SetMark(&sw, &sbw, &mw);
			break;
		case 6:
			PrintStud(&sw, &sbw, &mw);
			break;
		case 7:
			PrintSubj(&sw, &sbw, &mw);
			break;
		case 8:
			CourseWork(&sw, &sbw, &mw);
			break;
		case 0:
			sw.Save();
			sbw.Save();
			mw.Save();
			return 0;
			break;
		default:
			cout << "Неправильная команда, повторите ввод";
			break;
		}
		menu();
		cin >> c;
	}
}
