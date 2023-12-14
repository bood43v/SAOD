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
    int key = 1;
    if (hashTable.Find(key)) {
        std::cout << "Элемент найден: " << key << std::endl;
    }
    else {
        std::cout << "Элемент не найден" << std::endl;
    }
    cout << endl;


    // Удаление элемента из хеш-таблицы
    hashTable.Delete(3);

    // Обновление элемента в хеш-таблице
    hashTable.Update(2, 3);
    // Поиск элемента в хеш-таблице
    key = 3;
    if (hashTable.Find(key)) {
        std::cout << "Элемент найден: " << key << std::endl;
    }
    else {
        std::cout << "Элемент не найден" << std::endl;
    }


    // Очистка хеш-таблицы
    hashTable.ClearList();

    return 0;
}