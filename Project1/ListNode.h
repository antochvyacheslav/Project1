#pragma once

#include <string>

//структуру ListNode модифицировать нельзя
struct ListNode {
	ListNode* prev;
	ListNode* next;
	ListNode* rand; //указатель на произвольный элемент данного списка, либо NULL
	std::string data;
};