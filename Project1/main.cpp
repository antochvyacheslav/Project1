//ФИО: Анточ Вячеслав Аркадьевич
//Среда Microsoft Visual Studio Community 2019, Версия 16.10.0

//отключение предупреждения компилятора (уровень 3) C4996
#pragma warning(disable : 4996)

#include <cstdio>
#include "Task1.h"
#include "Task2.h"
#include "Task3.h"

//функция для проверки первой задачи
void testTask1() {
	printf("task1.\n\n");
	//трассировка степеней двойи для 1 байта
	for (int i = 0; i < 8; i++) {
		TraceSignedNumToBinaryFormat<char>(0x01 << i);
	}
	//трассировка степеней двойки для 4 байт
	for (int i = 0; i < 32; i++) {
		TraceSignedNumToBinaryFormat<int>(0x01 << i);
		TraceIntToBinaryFormat(0x01 << i);
	}
}

//функция для проверки второй задачи
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

//функция для проверки третьей задачи
void testTask3() {
	printf("\ntask3.\n\n");
	List list1;
	list1.AddToEnd("_a_");
	list1.AddToEnd("_ab_");
	list1.AddToEnd("_abc_");
	list1.AddToEnd("_abcd_");
	list1.AddToEnd("_wxyz_");
	list1.AddToEnd("_xyz_");
	list1.AddToEnd("_yz_");
	list1.AddToEnd("_z_");
	list1.SetRandNode();
	//сохранение в файл
	FILE* wb_file = fopen(List::PATH, "wb");
	if (wb_file) {
		list1.Serialize(wb_file);
		fclose(wb_file);
	}
	List list2;
	//загрузка из файла
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