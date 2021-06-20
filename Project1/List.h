#pragma once

#include "ListNode.h"

class List {
public:
	static const char* PATH; //���� � ����� 
public:
	List();
	~List();
public:
	//�������� ������ � ����� ������
	void AddToEnd(std::string* _data);
public:
	//����������� � ������ ������ � ������
	void TraceList();
	//��������� ��������� �� ������������ ������� ������� ������
	void SetRandNode();
public:
	//���������� � ���� (���� ������ � ������� fopen(path, "wb"))
	void Serialize(FILE* file);
	//�������� �� ����� (���� ������ � ������� fopen(path, "rb"))
	void Deserialize(FILE* file);
private:
	ListNode* head;
	ListNode* tail;
	int count;
};