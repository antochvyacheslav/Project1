#pragma once

#include "ListNode.h"

class List {
public:
	static const char* PATH; //путь к файлу 
public:
	List();
	~List();
public:
	//добавить данные в конец списка
	template <typename T>
	void AddToEnd(T _data);
private:
	//пусть по умолчанию, если это не один из нужных типов, то заносится пустая строка
	template <typename T>
	void SetData(ListNode* temp, T _data) { temp->data = " "; }
	//!оба метода сделаны inline, чтобы в месте их вызова происходила подстановка кода, вместо генерации кода вызова
	//строки заносить через перемещающий оператор присваивания - для десериализации, чтобы не было лишнего выделения памяти
	inline void SetData(ListNode* temp, std::string* _data) { temp->data = std::move(*_data); }
	//для удобства инициализации строки заносить через обычные си-строки - это только для занесения тестовых зачений в список
	inline void SetData(ListNode* temp, const char* _data) { temp->data = _data; };
public:
	//распечатать в трассу список с начала
	void TraceList();
	//установка указателя на произвольный элемент данного списка
	void SetRandNode();
public:
	//сохранение в файл (файл открыт с помощью fopen(path, "wb"))
	void Serialize(FILE* file);
	//загрузка из файла (файл открыт с помощью fopen(path, "rb"))
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
	//если список не пустой
	if (head != NULL) {
		temp->prev = tail;
		tail->next = temp;
		tail = temp;
	}
	//иначе если список пустой
	else {
		temp->prev = NULL;
		head = tail = temp;
	}
	count++;
}