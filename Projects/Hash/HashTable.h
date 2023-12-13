#include <iostream>
#include <functional>
#include <vector>
#include <list>

using namespace std;

template <class T>
class HashTablelterator;
template <class T>
class HashTable : public list<T>
{
protected:
	// число блоков; представляет размер таблицы
	int numBuckets;
	// хеш-таблица есть массив связанных списков
	vector<list<T>> buckets;
	// хеш-функция и адрес элемента данных,
	//к которому обращались последний раз
	unsigned long (*hf)(T key);
	T* current;
public:
	// конструктор с параметрами, включающими
	// размер таблицы и хеш-функцию
	HashTable(int nbuckets, unsigned long hashf(T key))
		: numBuckets(nbuckets), hf(hashf), current(nullptr)
	{
		buckets.resize(numBuckets);
	}


	template <class T>
	void Insert(const T& key)
	{
		int hashval = int(hf(key) % numBuckets);
		list<T>& lst = buckets[hashval];
		for (auto it = lst.begin(); it != lst.end(); ++it)
		{
			if (*it == key)
			{
				*it = key;
				current = &(*it);
				return;
			}
		}
		lst.push_back(key);
		current = &lst.back();
	}

	template <class T>
	int Find(T& key)
	{
		int hashval = int(hf(key) % numBuckets);
		list<T>& lst = buckets[hashval];
		for (auto it = lst.begin(); it != lst.end(); ++it)
		{
			if (*it == key)
			{
				key = *it;
				current = &(*it);
				return 1;
			}
		}
		return 0;
	}
	virtual void Delete(const T& key)
	{
		int hashval = int(hf(key) % numBuckets);
		list<T>& lst = buckets[hashval];
		for (auto it = lst.begin(); it != lst.end(); ++it)
		{
			if (*it == key)
			{
				lst.erase(it);
				return;
			}
		}
	}
	virtual void ClearList(void)
	{
		for (auto& lst : buckets)
		{
			lst.clear();
		}
	}
	void Update(const T& key)
	{
		int hashval = int(hf(key) % numBuckets);
		list<T>& lst = buckets[hashval];
		for (auto it = lst.begin(); it != lst.end(); ++it)
		{
			if (*it == key)
			{
				*it = key;
				current = &(*it);
				return;
			}
		}
	}

	template <class T>
	class HashTableIterator {
	private:
		HashTable<T>& hashTable;
		int currentBucket;
		typename std::list<T>::iterator currentIterator;

	public:
		HashTableIterator(HashTable<T>& ht)
			: hashTable(ht), currentBucket(0)
		{
			if (hashTable.numBuckets > 0)
				currentIterator = hashTable.buckets[0].begin();
		}

		HashTableIterator<T>& operator++() {
			if (currentBucket >= hashTable.numBuckets)
				return *this;
			++currentIterator;
			while (currentBucket < hashTable.numBuckets && currentIterator == hashTable.buckets[currentBucket].end()) {
				++currentBucket;
				if (currentBucket < hashTable.numBuckets)
					currentIterator = hashTable.buckets[currentBucket].begin();
			}
			return *this;
		}

		HashTableIterator<T> operator++(int) {
			HashTableIterator<T> temp = *this;
			++(*this);
			return temp;
		}

		bool operator==(const HashTableIterator<T>& it) const {
			return currentBucket == it.currentBucket && currentIterator == it.currentIterator;
		}

		bool operator!=(const HashTableIterator<T>& it) const {
			return !(*this == it);
		}

		T& operator*() const {
			return *currentIterator;
		}
	};

	HashTableIterator<T> begin() const
	{
		return HashTableIterator<T>(*this);
	}

	HashTableIterator<T> end() const
	{
		return HashTableIterator<T>();
	}

};
	