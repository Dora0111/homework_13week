#include <iostream>
#include <stack>
using namespace std;

void counting_sort(int A[], int B[], int k, int n) {
	int* C = new int[k + 1]; 
	for (int i = 0; i < k + 1; i++)
		C[i] = 0;
	for (int j = 0; j < n; j++)
		C[A[j]] = C[A[j]] + 1;
	for (i = 1; i < k + 1; i++)
		C[i] = C[i] + C[i - 1];
	for (j = n - 1; j >= 0; j--) {
		B[C[A[j]] - 1] = A[j];  
		C[A[j]] = C[A[j]] - 1;
	}
	delete[] C;
}
int main() {
	int A[15] = { 3, 19, 13, 5, 6, 15, 8, 3, 18, 16, 12, 23, 8, 21, 2 };
	int length = sizeof(A) / sizeof(A[0]);

	int i;

	cout << "A[i]的值为：  ";
	for (i = 0; i < length; i++) {
		cout << A[i] << ",  ";
	}
	cout << endl << endl;

	int k = 23;
	int B[15];
	counting_sort(A, B, k, length);

	cout << "排序后A[i]的值为：  ";
	for (i = 0; i < length; i++) {
		cout << B[i] << ",  ";
	}
	cout << endl << endl;

	return 0;
}


