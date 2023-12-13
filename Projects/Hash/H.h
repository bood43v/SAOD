#include <iostream>
#include <functional>
#include <vector>
#include <list>
#include "List/LinkedList.h"

using namespace std;

template <class T>
class HashTable : public LinkedList<T> {
protected:
    int numBuckets; // ���������� ������ � ���-�������
    vector<LinkedList<T>> buckets; // ������ ������, ���������� ��������� ������ ���������
    function<unsigned long(T)> hf; // ��������� �� ���-�������
    T* current; // ��������� �� ������� �������

public:
    HashTable(int nbuckets, unsigned long hashf(T key)) : numBuckets(nbuckets), hf(hashf) {
        buckets.resize(numBuckets); // �������������� ������ ������ ������ ����������� ���������
    }

    void Insert(const T& key) {
        unsigned long index = hf(key) % numBuckets; // ��������� ������ ������� ��� ������� ��������
        buckets[index].InsertAtTail(key); // ��������� ������� � ��������� ������ � ��������������� �������
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

    //void Delete(const T& key) {
    //    unsigned long index = hf(key) % numBuckets; // ��������� ������ ������� ��� �������� ��������
    //    auto it = buckets[index].begin(); // �������� �������� �� ������ ���������� ������
    //    while (it != buckets[index].end()) { // ���� �� ��������� ����� ���������� ������
    //        if (*it == key) { // ���� ������ ������� ������ �����
    //            it = buckets[index].Remove(*it); // ������� ������� �� ���������� ������ � ��������� ��������
    //        }
    //        else {
    //            ++it; // ��������� � ���������� ��������
    //        }
    //    }
    //}

    void ClearList() {
        for (auto& bucket : buckets) { // ����������� �� ��������
            bucket.clear(); // ������� ��������� ������ � ������ �������
        }
    }
};