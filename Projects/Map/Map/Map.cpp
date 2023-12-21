/// Файл работы со словарём Map на основе AVL дерева
/// @author Будаев Г.Б.
#pragma once

#include <iostream>
#include <string>
#include "Map.h"

using namespace std;

int main()
{
    //Map<string, int> dict(0);

    //dict["a"] = 10;
    //dict["b"] = 5;
    //dict["c"] = 7;

    //int x = dict["a"];
    //cout << x << endl;

    // получение значений элементов
    //cout << "Number of a: " << dict["a"] << endl;
    //cout << "Number of b: " << dict["b"] << endl;
    //cout << "Number of c: " << dict["c"] << endl;

    //// проверка наличия элемента в словаре
    //string letter = "a";
    //if (dict.InDictionary(letter))
    //{
    //    cout << letter << " is in the dictionary" << endl;
    //}
    //else
    //{
    //    cout << letter << " is not in the dictionary" << endl;
    //}

    //// удаление
    //dict.DeleteKey("b");

    //// проверка наличия удаленного элемента
    //string deleteLetter = "b";
    //if (dict.InDictionary(deleteLetter))
    //{
    //    cout << deleteLetter << " is in the dictionary" << endl;
    //}
    //else
    //{
    //    cout << deleteLetter << " is not in the dictionary" << endl;
    //}
    //// проверка наличия элемента в словаре
    //letter = "w";
    //if (dict.InDictionary(letter))
    //{
    //    cout << letter << " is in the dictionary" << endl;
    //}
    //else
    //{
    //    cout << letter << " is not in the dictionary" << endl;
    //}

    //cout << dict.Size() << endl;
    
    Map<int, int> dict1(0);
    dict1[1] = 155;
    cout << "dict[1]: " << dict1[1] << endl;
    int num = 3;
    dict1[3];
    dict1.Clear();
    cout << dict1.Size() << endl;
    return 0;
}