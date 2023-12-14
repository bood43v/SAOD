#include <iostream>
#include <functional>
#include <vector>
#include <list>
#include "List/LinkedList.h"
using namespace std;

//template <class T>
//class HashTablelterator;
template <class T>
class HashTable : public LinkedList<T>
{
protected:
	// число блоков; представляет размер таблицы
	int numBuckets;
	// хеш-таблица есть массив связанных списков
	vector<LinkedList<T>> buckets;
	// хеш-функция и адрес элемента данных,
	//к которому обращались последний раз
	unsigned long (*hf)(T key);

public:
	// конструктор с параметрами, включающими
	// размер таблицы и хеш-функцию
	HashTable(int nbuckets, unsigned long hashf(T key)) : numBuckets(nbuckets), hf(hashf)
	{
		buckets.resize(numBuckets);
	}

	void Insert(const T& key)
	{
		unsigned long hashValue = hf(key);
		int bucketIndex = hashValue % numBuckets;
		buckets[bucketIndex].InsertAtTail(key); 
	}

	bool Find(T& key)
	{
		unsigned long hashValue = hf(key);
		int bucketIndex = hashValue % numBuckets;
		if(buckets[bucketIndex].Search(key) == nullptr)
			false;
		else
		return true;
	}

	void Delete(const T& key)
	{
		unsigned long hashValue = hf(key);
		int bucketIndex = hashValue % numBuckets;
		buckets[bucketIndex].Remove(key);
	}

	void ClearList(void)
	{
		for (auto& lst : buckets)
		{
			lst.ClearList();
		}
	}

	void Update(const T& oldKey, const T& newKey) 
	{
		unsigned long oldHashValue = hf(oldKey);
		int oldBucketIndex = oldHashValue % numBuckets;

		unsigned long newHashValue = hf(newKey);
		int newBucketIndex = newHashValue % numBuckets; 

		if (oldBucketIndex == newBucketIndex) {
			buckets[oldBucketIndex].Update(oldKey, newKey); 
		}
		else {
			buckets[oldBucketIndex].Remove(oldKey);
			buckets[newBucketIndex].InsertAtTail(newKey);
		}
	}

	//template <class T>
	//class HashTableIterator {
	//private:
	//	// указатель таблицы, подлежащей обходу
	//	HashTable<T>* hashTable;
	//	// индекс текущего просматриваемого блока
	//	//и указатель на связанный список
	//	int currentBucket;
	//	list<T>* currBucketPtr;
	//	// утилита для реализации метода Next
	//	void SearchNextNode(int cb);
	//public:
	//	// конструктор
	//	HashTablelterator(HashTable<T>& ht);
	//	// базовые методы итератора
	//	void Next();
	//	void Reset();
	//	T& Data(void);
	//	// подготовить итератор для сканирования другой таблицы
	//	void SetList(HashTable<T> &lst);
	//};


	class HashTableIterator {
	private:
		

	public:
	
	};

	
	};
	