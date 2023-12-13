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
    hashTable.Insert(5);
    hashTable.Insert(12);
    hashTable.Insert(7);
    hashTable.Insert(18);
    hashTable.Insert(25);

    // Поиск элемента в хеш-таблице
    int key = 8;
    if (hashTable.Find(key)) {
        std::cout << "Элемент найден: " << key << std::endl;
    }
    else {
        std::cout << "Элемент не найден" << std::endl;
    }

    // Итерация по хеш-таблице с помощью итератора
    std::cout << "Элементы хеш-таблицы: ";
    for (auto it = hashTable.begin(); it != hashTable.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // Обновление элемента в хеш-таблице
    int newKey = 12;
    hashTable.Update(newKey);

    // Удаление элемента из хеш-таблицы
    int deleteKey = 5;
    hashTable.Delete(deleteKey);

    // Очистка хеш-таблицы
    hashTable.ClearList();

    return 0;
}