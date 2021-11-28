#include <iostream>
using namespace std;


void adjust_heap(int* a, int father, int len)
{
    int left = 2 * father + 1;
    int right = 2 * father + 2;
    int max = father;
    if (left <= len && a[left] > a[max])
        max = left;
    if (right <= len && a[right] > a[max])
        max = right;
    if (max != father)
    {
        swap(a[max], a[father]);
        adjust_heap(a, max, len);
    }
}

void heap_sort(int* a, int len)
{
    for (int i = len / 2; i >= 1; --i) 
        adjust_heap(a, i, len);

    for (int i = len; i >= 1; --i)
    {
        swap(a[1], a[i]);     
        adjust_heap(a, 1, i - 1); 
    }
}

int main()
{
    int a[11] = { -999, 7, 3, 4, 5, 2, 0, -1, 10, 0, 9 };
    int len = sizeof(a) / sizeof(int);


    for (int i = 1; i <= len; ++i)
        cout << a[i] << ' ';
    cout << endl;

    heap_sort(a, len);

    for (int i = 1; i <= len; ++i)
        cout << a[i] << ' ';
    cout << endl;

    return 0;
}
