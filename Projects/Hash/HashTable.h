#include <iostream>
#include <functional>
#include <list>
#include <vector>

template <class T>
class HashTable : public std::list<T> { 
protected:
    int numBuckets; // ���������� ������ � ���-�������
    std::vector<std::list<T>> buckets; // ������ ������, ���������� ��������� ������ ���������
    std::function<unsigned long(T)> hf; // ��������� �� ���-�������
    T* current; // ��������� �� ������� �������

public:
    HashTable(int nbuckets, unsigned long hashf(T key)) : numBuckets(nbuckets), hf(hashf) {
        buckets.resize(numBuckets); // �������������� ������ ������ ������ ����������� ���������
    }

    void Insert(const T& key) {
        unsigned long index = hf(key) % numBuckets; // ��������� ������ ������� ��� ������� ��������
        buckets[index].push_back(key); // ��������� ������� � ��������� ������ � ��������������� �������
    }

    int Find(const T& key) {
        unsigned long index = hf(key) % numBuckets; // ��������� ������ ������� ��� ������ ��������
        int count = 0; // ������� ������� �������� � ��������� ������
        for (const T& element : buckets[index]) { // ����������� �� ��������� ���������� ������
            if (element == key) { // ���� ������ ������� ������ �����
                return count; // ���������� ������� ��������
            }
            count++; // ����������� ������� �������
        }
        return -1; // ���� ������� �� ������
    }

    void Delete(const T& key) {
        unsigned long index = hf(key) % numBuckets; // ��������� ������ ������� ��� �������� ��������
        auto it = buckets[index].begin(); // �������� �������� �� ������ ���������� ������
        while (it != buckets[index].end()) { // ���� �� ��������� ����� ���������� ������
            if (*it == key) { // ���� ������ ������� ������ �����
                it = buckets[index].erase(it); // ������� ������� �� ���������� ������ � ��������� ��������
            }
            else {
                ++it; // ��������� � ���������� ��������
            }
        }
    }

    void ClearList() {
        for (auto& bucket : buckets) { // ����������� �� ��������
            bucket.clear(); // ������� ��������� ������ � ������ �������
        }
    }

    void Update(const T& key) {
        unsigned long index = hf(key) % numBuckets; // ��������� ������ ������� ��� ���������� ��������
        for (T& element : buckets[index]) { // ����������� �� ��������� ���������� ������
            if (element == key) { // ���� ������ ������� ������ �����
                element = key; // ��������� ������� � ����� ������
                return;
            }
        }
    }
};