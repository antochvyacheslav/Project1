#pragma once

#include <string>

//��������� ListNode �������������� ������
struct ListNode {
	ListNode* prev;
	ListNode* next;
	ListNode* rand; //��������� �� ������������ ������� ������� ������, ���� NULL
	std::string data;
};