/// Файл работы со словарём Map на основе AVL дерева
/// @author Будаев Г.Б.
#pragma once

#include <iostream>
#include <string>
#include "Map.h"

using namespace std;

int main()
{    
    Map<int, int> d1(0);
    d1[1] = 155;
    d1[2] = 1;
    d1[4] = 2;
    d1[5] = 3;
    
    cout << d1[1] << endl;
    cout << "d1.size = " << d1.Size() << endl << endl;

    Map<int, int> d2(1);
    d2 = d1;
    cout << d2[1] << endl;
    cout << d2[2] << endl;
    cout << d2[4] << endl;
    cout << d2[5] << endl;
    cout << d2[100] << endl;
    cout << "d2.size = " << d2.Size() << endl << endl;

    cout << d1[1] << endl;
    cout << "d1.size = " << d1.Size() << endl << endl;
    //for (typename Map<int, int>::MapIterator<int, int> it = d1.begin(); it != d1.end(); ++it)
    //{
    //    KeyValue<int, int>& keyValue = *it;
    //    int key = keyValue.Key();
    //    int value = keyValue.value;
    //    cout << "Key: " << key << ", Value: " << value << endl;
    //}
}