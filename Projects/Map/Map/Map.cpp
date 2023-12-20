#include <iostream>
#include <string>
#include "Map.h"

using namespace std;

int main()
{
    // Создание словаря с значением по умолчанию равным 0
    Map<string, int> dict(0);

    // Добавление элементов в словарь
    dict["apple"] = 10;
    dict["banana"] = 5;
    dict["orange"] = 7;

    // Использование оператора индексирования для получения значений элементов
    cout << "Number of apples: " << dict["apple"] << endl;
    cout << "Number of bananas: " << dict["banana"] << endl;
    cout << "Number of oranges: " << dict["orange"] << endl;

    // Проверка наличия элемента в словаре
    string fruit = "apple";
    if (dict.InDictionary(fruit))
    {
        cout << fruit << " is in the dictionary." << endl;
    }
    else
    {
        cout << fruit << " is not in the dictionary." << endl;
    }

    // Удаление элемента из словаря
    dict.DeleteKey("banana");

    // Проверка наличия удаленного элемента
    string deletedFruit = "banana";
    if (dict.InDictionary(deletedFruit))
    {
        cout << deletedFruit << " is in the dictionary." << endl;
    }
    else
    {
        cout << deletedFruit << " is not in the dictionary." << endl;
    }

    //cout << dict.Search("apple")->Data().GetValue() << endl;
    
    return 0;
}