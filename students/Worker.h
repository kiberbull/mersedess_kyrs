#pragma once
// ����� ��� ������ � �������
class Worker
{
public:
	// ��������� ����������
	virtual void Load() = 0;
	// ���������� ����������
	virtual void Save() = 0;
};	

