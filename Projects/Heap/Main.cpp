#include <iostream>
#include "Heap.h"

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
    std::cout << "Size: " << heap.Size() << std::endl;
    heap.insert(52225);
    heap.print();
    std::cout << "Size: " << heap.Size() << std::endl;

    heap.Max();
    heap.print();
    std::cout << "Size: " << heap.Size() << endl;

    int size = heap.Size();
    int* arr = new int(size);
    heap.heapSort(arr, size);

    for (int i = 0; i < heap.Size(); i++) {
        cout << arr[i] << endl;
    }
}
