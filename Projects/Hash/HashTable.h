#include <iostream>
#include <functional>
#include <vector>
#include <list>
#include "List/LinkedList.h"
using namespace std;

//template <class T>
//class HashTablelterator;
template <class T>
class HashTable
{
protected:
	// представляет размер таблицы
	int tableSize;
	// хеш-таблица есть массив связанных списков
	vector<LinkedList<T>> buckets;
	// хеш-функция 
	unsigned long (*hf)(T key);

public:
	/// <summary>
	/// конструктор с параметрами размер таблицы и хеш-функцию
	/// </summary>
	/// <param name="size"></param>
	/// <param name="hashf"></param>
	HashTable(int size, unsigned long hashf(T key)) : tableSize(size), hf(hashf)
	{
		buckets.resize(tableSize);
	}

	/// <summary>
	/// вставка в таблицу
	/// </summary>
	/// <param name="key"></param>
	void Insert(const T& key)
	{
		// вычисление хеша
		int hashValue = hf(key);
		// остаток от деления вынесен из хеш функции для гарантированного попадания в размер таблицы
		int bucketIndex = hashValue % tableSize;
		// вставка ключа в таблицу по индексу, вычисленному в хеш-функции
		buckets[bucketIndex].InsertAtTail(key);
	}

	/// <summary>
	/// найден элемент в таблице или нет
	/// </summary>
	/// <param name="key"></param>
	/// <returns></returns>
	bool Find(T& key)
	{
		// вычисление хеша
		int hashValue = hf(key);
		// остаток от деления вынесен из хеш функции для гарантированного попадания в размер таблицы
		int bucketIndex = hashValue % tableSize;
		// поиск по списку
		if (buckets[bucketIndex].Search(key) == nullptr)
			false;
		else
			return true;
	}

	/// <summary>
	/// удаление ключа из таблицы
	/// </summary>
	/// <param name="key"></param>
	void Delete(const T& key)
	{
		// вычисление хеша
		int hashValue = hf(key);
		// остаток от деления вынесен из хеш функции для гарантированного попадания в размер таблицы
		int bucketIndex = hashValue % tableSize;
		// удаление из списка (цепочки)
		buckets[bucketIndex].Remove(key);
	}

	/// <summary>
	/// очистка таблицы (вектора списков)
	/// </summary>
	/// <param name=""></param>
	void ClearList(void)
	{
		for (auto& lst : buckets)
		{
			lst.ClearList();
		}
	}

	/// <summary>
	/// замена на новое значение
	/// </summary>
	/// <param name="oldKey"></param>
	/// <param name="newKey"></param>
	void Update(const T& key, const T& new_key)
	{
		// вычисление хеша для старого и нового ключей
		int oldHashValue = hf(key);
		int newHashValue = hf(new_key);
		// остаток от деления для попадания в таблицу
		int oldBucketIndex = oldHashValue % tableSize;
		int newBucketIndex = newHashValue % tableSize;
		
		// если ключи находятся в одном списке, то заменям
		if (oldBucketIndex == newBucketIndex) {
			buckets[oldBucketIndex].Update(key, new_key);
		}
		// если в разных - удаляем старый и вставляем новый в соответсвующих списках
		else {
			buckets[oldBucketIndex].Remove(key);
			buckets[newBucketIndex].InsertAtTail(new_key);
		}
	}

	/// <summary>
	/// Печать таблицы
	/// </summary>
	void PrintTable()
	{
		for (int i = 0; i < tableSize; ++i)
		{

			cout << "Строка " << i << ": ";
			// итерируемся по каждому списку в таблице
			for (LinkedList<int>::LinkedListIterator<int> it = buckets[i].begin(); it != buckets[i].end(); ++it) {
				cout << *it << " ";
			}
			
			cout << endl;
		}
	}

	/// <summary>
	/// итератор для хеш-таблицы
	/// </summary>
	/// <typeparam name="T"></typeparam>
	template <class T>
	class HashTableIterator
	{
	private:
		using ListIterator = typename LinkedList<T>::template LinkedListIterator<T>;

		const HashTable<T>& hashTable;  // Ссылка на хеш-таблицу
		int currentIndex;               // Текущий индекс корзины
		ListIterator currentIterator;   // Итератор текущего списка


	public:
		// конструторк
		HashTableIterator(const HashTable<T>& table)
			: hashTable(table), currentIndex(0), currentIterator(table.buckets[0].begin())
		{
			// Находим первую непустую корзину
			while (currentIndex < hashTable.tableSize && currentIterator == hashTable.buckets[currentIndex].end())
			{
				++currentIndex;
				if (currentIndex < hashTable.tableSize)
					currentIterator = hashTable.buckets[currentIndex].begin();
			}
		}

		T operator*() const
		{
			return *currentIterator;
		}

		HashTableIterator& operator++()
		{
			// Переходим к следующему элементу
			++currentIterator;

			// Если достигнут конец текущего списка, переходим к следующей непустой корзине
			while (currentIndex < hashTable.tableSize && currentIterator == hashTable.buckets[currentIndex].end())
			{
				++currentIndex;
				if (currentIndex < hashTable.tableSize)
					currentIterator = hashTable.buckets[currentIndex].begin();
			}

			return *this;
		}

		bool operator!=(const HashTableIterator& other) const
		{
			return currentIndex != other.currentIndex || currentIterator != other.currentIterator;
		}
	};

	

	HashTableIterator<T> begin() {
		// Находим первую непустую корзину
		int currentIndex = 0;
		while (currentIndex < tableSize && buckets[currentIndex].IsEmpty())
			++currentIndex;

		// Если таблица пуста, возвращаем итератор, указывающий на конец таблицы
		if (currentIndex == tableSize)
			return HashTableIterator<T>(this, nullptr);

		// Возвращаем итератор на первый элемент в первой непустой корзине
		return HashTableIterator<T>(this, buckets[currentIndex].begin());
	}


	HashTableIterator<T> end() {
		// Создаем итератор, указывающий на конец последней корзины
		return HashTableIterator<T>(this, buckets[tableSize - 1].end());
	}


	/*template <class T>
	class HashTableIterator : public LinkedList<T>::LinkedListIterator<T> {
	private:
		const vector<LinkedList<T>>& buckets;

	public:
		HashTableIterator(const vector<LinkedList<T>>& b, LinkedList<T>::LinkedListIterator<T> p)
			: LinkedList<T>::LinkedListIterator<T>(p), buckets(b) {}

		HashTableIterator<T>& operator++() {
			LinkedList<T>::LinkedListIterator<T>::operator++();
			return *this;
		}

		HashTableIterator<T> operator++(int) {
			HashTableIterator<T> temp = *this;
			LinkedList<T>::LinkedListIterator<T>::operator++();
			return temp;
		}

		bool operator==(const HashTableIterator<T>& other) const {
			return LinkedList<T>::LinkedListIterator<T>::operator==(other);
		}

		bool operator!=(const HashTableIterator<T>& other) const {
			return LinkedList<T>::LinkedListIterator<T>::operator!=(other);
		}

		T operator*() const {
			return typename LinkedList<T>::LinkedListIterator<T>::GetCurrentNode()->Data();
		}
	};

	HashTableIterator<T> begin()
	{
		for (auto& lst : buckets)
		{
			if (!lst.IsEmpty())
				return HashTableIterator<T>(buckets, lst.begin());
		}
		return HashTableIterator<T>(buckets, nullptr);
	}

	HashTableIterator<T> end()
	{
		return HashTableIterator<T>(buckets, nullptr);
	}*/
	
};
