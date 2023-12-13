#include <iostream>
#include <functional>
#include <list>
#include <vector>

template <class T>
class HashTable : public std::list<T> { 
protected:
    int numBuckets; // Количество корзин в хэш-таблице
    std::vector<std::list<T>> buckets; // Вектор корзин, содержащих связанные списки элементов
    std::function<unsigned long(T)> hf; // Указатель на хэш-функцию
    T* current; // Указатель на текущий элемент

public:
    HashTable(int nbuckets, unsigned long hashf(T key)) : numBuckets(nbuckets), hf(hashf) {
        buckets.resize(numBuckets); // Инициализируем вектор корзин нужным количеством элементов
    }

    void Insert(const T& key) {
        unsigned long index = hf(key) % numBuckets; // Вычисляем индекс корзины для вставки элемента
        buckets[index].push_back(key); // Вставляем элемент в связанный список в соответствующей корзине
    }

    int Find(const T& key) {
        unsigned long index = hf(key) % numBuckets; // Вычисляем индекс корзины для поиска элемента
        int count = 0; // Счетчик позиции элемента в связанном списке
        for (const T& element : buckets[index]) { // Итерируемся по элементам связанного списка
            if (element == key) { // Если найден элемент равный ключу
                return count; // Возвращаем позицию элемента
            }
            count++; // Увеличиваем счетчик позиции
        }
        return -1; // Если элемент не найден
    }

    void Delete(const T& key) {
        unsigned long index = hf(key) % numBuckets; // Вычисляем индекс корзины для удаления элемента
        auto it = buckets[index].begin(); // Получаем итератор на начало связанного списка
        while (it != buckets[index].end()) { // Пока не достигнут конец связанного списка
            if (*it == key) { // Если найден элемент равный ключу
                it = buckets[index].erase(it); // Удаляем элемент из связанного списка и обновляем итератор
            }
            else {
                ++it; // Переходим к следующему элементу
            }
        }
    }

    void ClearList() {
        for (auto& bucket : buckets) { // Итерируемся по корзинам
            bucket.clear(); // Очищаем связанный список в каждой корзине
        }
    }

    void Update(const T& key) {
        unsigned long index = hf(key) % numBuckets; // Вычисляем индекс корзины для обновления элемента
        for (T& element : buckets[index]) { // Итерируемся по элементам связанного списка
            if (element == key) { // Если найден элемент равный ключу
                element = key; // Обновляем элемент с новым ключом
                return;
            }
        }
    }
};