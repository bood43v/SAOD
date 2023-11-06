/// Работа с классом кучи
/// @author Будаев Г.Б.
#include <iostream>
#include "Heap.h"
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    try {
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


        //MaxHeap<int> heap2(1);
        //heap2.insert(1);
        //cout << endl << "heap2 size: " << heap2.Size();
        //heap2.remove(1);
        //cout << endl << "heap2 size: " << heap2.Size();
        //heap2.remove(1);
        MaxHeap<int> heap3(-10);
        cout << endl << "heap3 size: " << heap3.Size();
        heap3.insert(222);
        heap3.insert(1);
        heap3.insert(22);
        cout << endl << "heap3 size: " << heap3.Size();

        MaxHeap<int> heap4(1);
        heap4.insert(2);
        heap4.Max();
        heap4.Max();
    }
    catch (const char* error_message) {
        cout << error_message << endl;
    }



}
