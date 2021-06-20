//���: ����� �������� ����������
//����� Microsoft Visual Studio Community�2019, ������ 16.10.0

//���������� �������������� ����������� (������� 3) C4996
#pragma warning(disable : 4996)

#include <cstdio>
#include "Task1.h"
#include "Task2.h"
#include "Task3.h"

//������� ��� �������� ������ ������
void testTask1() {
	printf("task1.\n\n");
	//����������� �������� ����� ��� 1 �����
	for (int i = 0; i < 8; i++) {
		TraceSignedNumToBinaryFormat<char>(0x01 << i);
	}
	//����������� �������� ������ ��� 4 ����
	for (int i = 0; i < 32; i++) {
		TraceSignedNumToBinaryFormat<int>(0x01 << i);
		TraceIntToBinaryFormat(0x01 << i);
	}
}

//������� ��� �������� ������ ������
void testTask2() {
	printf("\ntask2.\n\n");
	char data1[] = "AAA BBB AAA";
	RemoveDups(data1);
	printf("RemoveDups: [%s]\n", data1);
	char data2[] = "      ";
	RemoveDups(data2);
	printf("RemoveDups: [%s]\n", data2);
	char data3[] = "      ,      ";
	RemoveDups(data3);
	printf("RemoveDups: [%s]\n", data3);
}

//������� ��� �������� ������� ������
void testTask3() {
	printf("\ntask3.\n\n");
	List list1;
	//������ ����� ��� ���������� ������ ��������� ����������
	std::string str[] = { "_a_", "_ab_", "_abc_", "_abcd_", "_wxyz_", "_xyz_", "_yz_", "_z_" };
	for (auto& s : str) {
		list1.AddToEnd(&s);
	}
	//��������� ��������� �� ������������ ������� ������� ������
	list1.SetRandNode();
	//���������� � ����
	FILE* wb_file = fopen(List::PATH, "wb");
	if (wb_file) {
		list1.Serialize(wb_file);
		fclose(wb_file);
	}
	List list2;
	//�������� �� �����
	FILE* rb_file = fopen(List::PATH, "rb");
	if (rb_file) {
		list2.Deserialize(rb_file);
		fclose(rb_file);
	}
	printf("list1: ");
	list1.TraceList();
	printf("list2: ");
	list2.TraceList();
}

int main() {
	testTask1();
	testTask2();
	testTask3();
	return 0;
}