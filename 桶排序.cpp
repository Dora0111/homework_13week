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
	const int RADIX = 10;//以10为基进行排序
	int tmp;
	Num* topBox[RADIX];//桶中最新添加进去的元素
	Num* bottomBox[RADIX];//桶底元素

	for (int i = 0; i < RADIX; ++i) {
		topBox[i] = bottomBox[i] = new Num;
	}

	//找最大值
	tmp = arr[0];
	for (int i = 0; i < len; ++i) {
		if (tmp < arr[i])
			tmp = arr[i];
	}

	//计算最大值有多少个数位
	int digCnt = 1;
	tmp /= RADIX;
	while (tmp) {
		++digCnt;
		tmp /= RADIX;
	}

	//将数组转换成链表
	Num* head = new Num;
	Num* cur;
	cur = head;
	for (int i = 0; i < len; ++i) {
		cur->next = new Num;
		cur->next->v = arr[i];
		cur = cur->next;
	}

	//开始基数排序
	int factor = 1;
	for (int i = 0; i < digCnt; ++i) {
		//散列
		for (cur = head->next; cur; cur = cur->next) {
			tmp = (cur->v / factor) % RADIX;
			topBox[tmp]->next = cur;
			topBox[tmp] = topBox[tmp]->next;
		}
		//合并
		cur = head;
		for (int j = 0; j < RADIX; ++j) {
			if (topBox[j] != bottomBox[j]) {
				cur->next = bottomBox[j]->next;
				cur = topBox[j];
				topBox[j] = bottomBox[j];
			}
		}
		//必须将最后一个数字的next赋值为NULL,否则导致链表形成环,导致再次"散列"时会死循环
		cur->next = 0;

		//扩大因子,用于取下一个数字
		factor *= RADIX;
	}

	//使用链表给数组赋值
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
	cout << "初始数组:" << endl;
	printArray(heap, len);
	//mySort(heap,0,len-1);
	sort(heap, len);
	printArray(heap, len);
	delete heap;
}
