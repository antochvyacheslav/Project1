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
	void AddToEnd(std::string* _data);
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