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
	//освобождение памяти, удаление всех ListNode между head и tail
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
	//строки заносить через перемещающий оператор присваивания - чтобы не было лишнего выделения памяти
	temp->data = std::move(*_data);
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

void List::TraceList() {
	printf("count=%d:\n", count);
	//трассировка списка с начала
	for (ListNode* p = head; p != NULL; p = p->next) {
		printf("(data=[%s], rand=[%s])\n", p->data.c_str(), p->rand ? p->rand->data.c_str() : "NULL");
	}
	printf("\n");
}

void List::SetRandNode() {
	//вектор под хранение указателей на узлы - для тестового заполнения указателей на случайные узлы
	std::vector<ListNode*> vlist;
	//сохранение в вектор указателей на добавленный элемент
	for (ListNode* p = head; p != NULL; p = p->next) {
		vlist.push_back(p);
	}
	srand((unsigned int)time(0));
	for (ListNode* p = head; p != NULL; p = p->next) {
		//count + 3 - чтобы значение иногда выходило за размер списка, чтобы в списке иногда был пустой указатель NULL
		int num = rand() % (count + 3);
		p->rand = num < count ? vlist[num] : NULL;
	}
}

void List::Serialize(FILE* file) {
	//указатель на каждый узел является уникальным значением, и map д.б. отсортирован по ключам, т.е. нужен критерий сортирвки по ключам - оба условия выполняются
	//map будет хранить пару - указатель на узел и его порядковый номер (на момент сериализации)
	std::map<ListNode*, int> mlist;
	int i = 0;
	for (ListNode* p = head; p != NULL; p = p->next, i++) {
		mlist.insert(std::pair<ListNode*, int>(p, i));
	}
	//сначала записать количество элементов в списке
	fwrite(&count, sizeof(count), 1, file);
	//список подразумевает только последовательный доступ, поэтому данные записываются последовательно в том порядке, как были добавлены
	for (ListNode* temp = head; temp != NULL; temp = temp->next) {
		unsigned int length = temp->data.length();
		//сначала занести размер данных, для этого записать в файл 4 байта, которые хранят размер данных
		fwrite(&length, sizeof(length), 1, file);
		//записать сами данные размером length байт - c_str() возвращает указатель char* на данные строки, char - это байт, поэтому в двоичный файл просто записывается столько байт, сколько размер строки
		fwrite(temp->data.c_str(), length, 1, file);
		//получить номер случайного узла (из контейнера map) - сохранение состояния списка на момент сериализации, если указатель на случайный элемент NULL, то номер будет равен -1
		int rand_num = temp->rand ? mlist[temp->rand] : -1;
		//записать номер случайного узла - тоже 4 байта, сохранение состояния списка на момент сериализации
		fwrite(&rand_num, sizeof(rand_num), 1, file);
	}
}

void List::Deserialize(FILE* file) {
	//количество данных указанных в начале файла
	unsigned int cnt_file = 0;
	//сначала считать первые 4 байта, которые хранят количество элементов в списке
	fread(&cnt_file, sizeof(cnt_file), 1, file);
	if (cnt_file < 1) {
		printf("Deserialize. FIle is empty!\n");
		return;
	}
	//вектор под хранение номеров случайных узлов - для восстановления состояния списка на момент сериализации
	std::vector<int> vrand_num;
	//вектор под хранение указателей на узлы - для восстановления состояния списка на момент сериализации
	std::vector<ListNode*> vlist;
	//количество считанных данных
	unsigned int cnt_cur = 0;
	for (cnt_cur = 0; cnt_cur < cnt_file; cnt_cur++) {
		unsigned int length = 0;
		//считывать 4 байта, которые хранят размер данных
		if (!fread(&length, sizeof(length), 1, file)) {
			break;
		}
		//создать переменную для считывания в неё данных из бинарного файла, выделить память под данные размером length байт и проинициализировать
		std::string str(length, '\0');
		//затем считать сами данные размером length байт
		if (!fread(&str[0], length, 1, file)) {
			break;
		}
		int rand_num = -1;
		//затем считать номер случайного узла (4 байта)
		if (!fread(&rand_num, sizeof(rand_num), 1, file)) {
			break;
		}
		//сохранить в вектор номер случайного узла
		vrand_num.push_back(rand_num);
		//добавить считанные данные в конец списка
		//!здесь передаётся адрес созданной выше строчки (чтобы не передавать саму строчку), для которой уже выделена память и в которую уже записаны нужные данные
		//!внутри метода будет вызван перемещающий оператор присванивания, чтобы не выделять повторно память в куче и не копировать заново данные в выделенную память
		this->AddToEnd(&str);
		//после добавления нового элемента в список, сохранить указатель на добавленный элемент - сохранить указатель на последнего узла в списке
		vlist.push_back(tail);
	}
	if (cnt_file != cnt_cur) {
		printf("Deserialize. Not all data will be readed!\n");
	}
	//восстановить указатели на случайный элемент списка
	for (unsigned int i = 0; i < cnt_cur; i++) {
		vlist[i]->rand = vrand_num[i] >= 0 ? vlist[vrand_num[i]] : NULL;
	}
}