#include <iostream>
#include <cstring>
#include <ctime>
using namespace std;

struct Num {
	int v;
	Num* next;
	Num() {
		next = 0;
	}
};
void sort(int* arr, int len) {
	const int RADIX = 10;//��10Ϊ����������
	int tmp;
	Num* topBox[RADIX];//Ͱ��������ӽ�ȥ��Ԫ��
	Num* bottomBox[RADIX];//Ͱ��Ԫ��

	for (int i = 0; i < RADIX; ++i) {
		topBox[i] = bottomBox[i] = new Num;
	}

	//�����ֵ
	tmp = arr[0];
	for (int i = 0; i < len; ++i) {
		if (tmp < arr[i])
			tmp = arr[i];
	}

	//�������ֵ�ж��ٸ���λ
	int digCnt = 1;
	tmp /= RADIX;
	while (tmp) {
		++digCnt;
		tmp /= RADIX;
	}

	//������ת��������
	Num* head = new Num;
	Num* cur;
	cur = head;
	for (int i = 0; i < len; ++i) {
		cur->next = new Num;
		cur->next->v = arr[i];
		cur = cur->next;
	}

	//��ʼ��������
	int factor = 1;
	for (int i = 0; i < digCnt; ++i) {
		//ɢ��
		for (cur = head->next; cur; cur = cur->next) {
			tmp = (cur->v / factor) % RADIX;
			topBox[tmp]->next = cur;
			topBox[tmp] = topBox[tmp]->next;
		}
		//�ϲ�
		cur = head;
		for (int j = 0; j < RADIX; ++j) {
			if (topBox[j] != bottomBox[j]) {
				cur->next = bottomBox[j]->next;
				cur = topBox[j];
				topBox[j] = bottomBox[j];
			}
		}
		//���뽫���һ�����ֵ�next��ֵΪNULL,�����������γɻ�,�����ٴ�"ɢ��"ʱ����ѭ��
		cur->next = 0;

		//��������,����ȡ��һ������
		factor *= RADIX;
	}

	//ʹ����������鸳ֵ
	cur = head->next;
	for (int i = 0; i < len; ++i, cur = cur->next) {
		arr[i] = cur->v;
	}
}

void test() {
	int len = 20;
	int* heap = new int[len];

	srand(time(0));
	for (int i = 0; i < len; ++i) {
		heap[i] = rand() % 10000;
	}
	cout << "��ʼ����:" << endl;
	printArray(heap, len);
	//mySort(heap,0,len-1);
	sort(heap, len);
	printArray(heap, len);
	delete heap;
}
