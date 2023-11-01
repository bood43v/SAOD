#include <iostream>
#include "Heap.h"
#include <vector>
#include <algorithm>
using namespace std;




int main()
{
    MaxHeap<int> heap(5);
    heap.insert(5);
    heap.insert(10);
    heap.insert(30);
    heap.insert(7);
    heap.insert(6);

    
    heap.print();
    cout << "Size: " << heap.Size() << endl;
    heap.insert(52225);
    heap.print();
    cout << "Size: " << heap.Size() << endl;

    heap.Max();
    heap.print();
    cout << "Size: " << heap.Size() << endl;

    cout << "Sorted: " << endl;
    vector<int> vec;
    vec = heap.heapSort();

    for (int i = 0; i < vec.size(); i++)
    {
        cout << vec[i] << " ";
    }




}
