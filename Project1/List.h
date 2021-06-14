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
	template <typename T>
	void AddToEnd(T _data);
private:
	//����� �� ���������, ���� ��� �� ���� �� ������ �����, �� ��������� ������ ������
	template <typename T>
	void SetData(ListNode* temp, T _data) { temp->data = " "; }
	//!��� ������ ������� inline, ����� � ����� �� ������ ����������� ����������� ����, ������ ��������� ���� ������
	//������ �������� ����� ������������ �������� ������������ - ��� ��������������, ����� �� ���� ������� ��������� ������
	inline void SetData(ListNode* temp, std::string* _data) { temp->data = std::move(*_data); }
	//��� �������� ������������� ������ �������� ����� ������� ��-������ - ��� ������ ��� ��������� �������� ������� � ������
	inline void SetData(ListNode* temp, const char* _data) { temp->data = _data; };
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

template <typename T>
void List::AddToEnd(T _data) {
	ListNode* temp = new ListNode;
	temp->next = NULL;
	temp->rand = NULL;
	this->SetData(temp, _data);
	//���� ������ �� ������
	if (head != NULL) {
		temp->prev = tail;
		tail->next = temp;
		tail = temp;
	}
	//����� ���� ������ ������
	else {
		temp->prev = NULL;
		head = tail = temp;
	}
	count++;
}