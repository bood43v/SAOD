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


        MaxHeap<int> heap2(heap);
        heap2.print();

        MaxHeap<int> heap3 = heap2;

        cout << endl;
        heap3.print();

    }
    catch (const char* error_message) {
        cout << endl << error_message << endl;
    }



}
