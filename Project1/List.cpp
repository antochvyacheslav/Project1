#include <cstdio>
#include <cstring>
#include <ctime>
#include <map>
#include <vector>
#include"List.h"

const char* List::PATH = "D:\\Projects\\Saber Interactive\\bin_file.bin";

List::List() : head(NULL), tail(NULL), count(0) {

}

List::~List() {
	//������������ ������, �������� ���� ListNode ����� head � tail
	while (head) {
		tail = head->next;
		delete head;
		head = tail;
	}
	count = 0;
}

void List::AddToEnd(std::string* _data) {
	ListNode* temp = new ListNode;
	temp->next = NULL;
	temp->rand = NULL;
	//������ �������� ����� ������������ �������� ������������ - ����� �� ���� ������� ��������� ������
	temp->data = std::move(*_data);
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

void List::TraceList() {
	printf("count=%d:\n", count);
	//����������� ������ � ������
	for (ListNode* p = head; p != NULL; p = p->next) {
		printf("(data=[%s], rand=[%s])\n", p->data.c_str(), p->rand ? p->rand->data.c_str() : "NULL");
	}
	printf("\n");
}

void List::SetRandNode() {
	//������ ��� �������� ���������� �� ���� - ��� ��������� ���������� ���������� �� ��������� ����
	std::vector<ListNode*> vlist;
	//���������� � ������ ���������� �� ����������� �������
	for (ListNode* p = head; p != NULL; p = p->next) {
		vlist.push_back(p);
	}
	srand((unsigned int)time(0));
	for (ListNode* p = head; p != NULL; p = p->next) {
		//count + 3 - ����� �������� ������ �������� �� ������ ������, ����� � ������ ������ ��� ������ ��������� NULL
		int num = rand() % (count + 3);
		p->rand = num < count ? vlist[num] : NULL;
	}
}

void List::Serialize(FILE* file) {
	//��������� �� ������ ���� �������� ���������� ���������, � map �.�. ������������ �� ������, �.�. ����� �������� ��������� �� ������ - ��� ������� �����������
	//map ����� ������� ���� - ��������� �� ���� � ��� ���������� ����� (�� ������ ������������)
	std::map<ListNode*, int> mlist;
	int i = 0;
	for (ListNode* p = head; p != NULL; p = p->next, i++) {
		mlist.insert(std::pair<ListNode*, int>(p, i));
	}
	//������� �������� ���������� ��������� � ������
	fwrite(&count, sizeof(count), 1, file);
	//������ ������������� ������ ���������������� ������, ������� ������ ������������ ��������������� � ��� �������, ��� ���� ���������
	for (ListNode* temp = head; temp != NULL; temp = temp->next) {
		unsigned int length = temp->data.length();
		//������� ������� ������ ������, ��� ����� �������� � ���� 4 �����, ������� ������ ������ ������
		fwrite(&length, sizeof(length), 1, file);
		//�������� ���� ������ �������� length ���� - c_str() ���������� ��������� char* �� ������ ������, char - ��� ����, ������� � �������� ���� ������ ������������ ������� ����, ������� ������ ������
		fwrite(temp->data.c_str(), length, 1, file);
		//�������� ����� ���������� ���� (�� ���������� map) - ���������� ��������� ������ �� ������ ������������, ���� ��������� �� ��������� ������� NULL, �� ����� ����� ����� -1
		int rand_num = temp->rand ? mlist[temp->rand] : -1;
		//�������� ����� ���������� ���� - ���� 4 �����, ���������� ��������� ������ �� ������ ������������
		fwrite(&rand_num, sizeof(rand_num), 1, file);
	}
}

void List::Deserialize(FILE* file) {
	//���������� ������ ��������� � ������ �����
	unsigned int cnt_file = 0;
	//������� ������� ������ 4 �����, ������� ������ ���������� ��������� � ������
	fread(&cnt_file, sizeof(cnt_file), 1, file);
	if (cnt_file < 1) {
		printf("Deserialize. FIle is empty!\n");
		return;
	}
	//������ ��� �������� ������� ��������� ����� - ��� �������������� ��������� ������ �� ������ ������������
	std::vector<int> vrand_num;
	//������ ��� �������� ���������� �� ���� - ��� �������������� ��������� ������ �� ������ ������������
	std::vector<ListNode*> vlist;
	//���������� ��������� ������
	unsigned int cnt_cur = 0;
	for (cnt_cur = 0; cnt_cur < cnt_file; cnt_cur++) {
		unsigned int length = 0;
		//��������� 4 �����, ������� ������ ������ ������
		if (!fread(&length, sizeof(length), 1, file)) {
			break;
		}
		//������� ���������� ��� ���������� � �� ������ �� ��������� �����, �������� ������ ��� ������ �������� length ���� � �������������������
		std::string str(length, '\0');
		//����� ������� ���� ������ �������� length ����
		if (!fread(&str[0], length, 1, file)) {
			break;
		}
		int rand_num = -1;
		//����� ������� ����� ���������� ���� (4 �����)
		if (!fread(&rand_num, sizeof(rand_num), 1, file)) {
			break;
		}
		//��������� � ������ ����� ���������� ����
		vrand_num.push_back(rand_num);
		//�������� ��������� ������ � ����� ������
		//!����� ��������� ����� ��������� ���� ������� (����� �� ���������� ���� �������), ��� ������� ��� �������� ������ � � ������� ��� �������� ������ ������
		//!������ ������ ����� ������ ������������ �������� �������������, ����� �� �������� �������� ������ � ���� � �� ���������� ������ ������ � ���������� ������
		this->AddToEnd(&str);
		//����� ���������� ������ �������� � ������, ��������� ��������� �� ����������� ������� - ��������� ��������� �� ���������� ���� � ������
		vlist.push_back(tail);
	}
	if (cnt_file != cnt_cur) {
		printf("Deserialize. Not all data will be readed!\n");
	}
	//������������ ��������� �� ��������� ������� ������
	for (unsigned int i = 0; i < cnt_cur; i++) {
		vlist[i]->rand = vrand_num[i] >= 0 ? vlist[vrand_num[i]] : NULL;
	}
}