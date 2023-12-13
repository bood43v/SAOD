#include <iostream>
#include <functional>
#include "HashTable.h"

using namespace std;
// Пример пользовательской хэш-функции для целых чисел
unsigned long HashFunction(int key) {
    return static_cast<unsigned long>(key); // Простая хэш-функция, возвращающая само число
}

int main() {
    HashTable<int> hashTable(10, HashFunction); // Создание экземпляра HashTable с 10 корзинами и пользовательской хэш-функцией

    hashTable.Insert(10);
    hashTable.Insert(20);
    hashTable.Insert(30);

    std::cout << "Elements in hash table:" << std::endl;
    for (const int& element : hashTable) {
        std::cout << element << std::endl; // Вывод элементов хэш-таблицы
    }

    std::cout << "Find '20' at position: " << hashTable.Find(20) << std::endl; // Поиск элемента в хэш-таблице

    hashTable.Delete(20); // Удаление элемента из хэш-таблицы

    std::cout << "Elements in hash table after deletion:" << std::endl;
    for (const int& element : hashTable) {
        std::cout << element << std::endl; // Вывод элементов хэш-таблицы после удаления
    }

    return 0;
}

