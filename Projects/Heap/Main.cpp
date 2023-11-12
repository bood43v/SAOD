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
        vector<int> vec{ 1, 2, 3, 4 };
        MaxHeap<int> heap1(vec);         /// Куча 1

        MaxHeap<int> heap2(heap1);       /// Конструктор копирования

        MaxHeap<int> heap3(move(heap1)); /// Конструктор перемещения
       

        MaxHeap<int> heap_(vec);         /// Куча 2        

        MaxHeap<int> heap4;            
        heap4 = heap_;                   /// Оператор присваивания копированием

        MaxHeap<int> heap5;             
        heap5 = move(heap_);             /// Оператор присваивания перемещением

    }
    catch (const char* error_message) {
        cout << endl << error_message << endl;
    }
}
