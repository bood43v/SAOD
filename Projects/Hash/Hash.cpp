#include <iostream>
#include <functional>
#include "HashTable.h"

using namespace std;

unsigned long HashFunc(int key) {
    // Пример простой хеш-функции для целых чисел
    return key % 10;
}

int main() {
    setlocale(LC_ALL, "ru");
    HashTable<int> hashTable(10, HashFunc);

    // Вставка элементов в хеш-таблицу
    hashTable.Insert(1);
    hashTable.Insert(2);
    hashTable.Insert(3);

    // Поиск элемента в хеш-таблице
    int key = 3;
    if (hashTable.Find(key)) {
        std::cout << "Элемент найден: " << key << std::endl;
    }
    else {
        std::cout << "Элемент не найден" << std::endl;
    }


    cout << endl;
     // Обновление элемента в хеш-таблице
    int newKey = 12;
    hashTable.Update(newKey, 5);

    // Удаление элемента из хеш-таблицы
    int deleteKey = 5;
    hashTable.Delete(deleteKey);

    // Очистка хеш-таблицы
    hashTable.ClearList();

    return 0;
}