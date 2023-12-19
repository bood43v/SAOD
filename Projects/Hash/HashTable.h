/// Класс хеш-таблица
/// @author Будаев Г.Б.
#include <iostream>
#include <functional>
#include <vector>
#include <list>
#include "List/LinkedList.h"
using namespace std;

/// <summary>
/// класс хеш-таблица с решением коллизий методом цепочек
/// </summary>
/// <typeparam name="T"></typeparam>
template <class T>
class HashTable
{
private:
	// представляет размер таблицы
	int tableSize;
	// хеш-таблица есть массив связанных списков
	vector<LinkedList<T>> buckets;
	// хеш-функция 
	unsigned long (*hf)(T key);

public:
	/// <summary>
	/// конструктор с параметрами размер таблицы и хеш-функция
	/// </summary>
	/// <param name="size"> размер таблицы </param>
	/// <param name="hashf"> хеш-функция </param>
	HashTable(int size, unsigned long hashf(T key))
	{
		tableSize = size;
		hf = hashf;
		buckets.resize(tableSize);
	}

	/// <summary>
	/// Размер таблицы
	/// </summary>
	int Size() const
	{
		return tableSize;
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
		if (!this->Find(key)) {
			int bucketIndex = hashValue % tableSize;
			// вставка ключа в таблицу по индексу, вычисленному в хеш-функции
			buckets[bucketIndex].InsertAtTail(key);
		}
	}

	/// <summary>
	/// найден элемент в таблице или нет
	/// </summary>
	/// <param name="key"></param>
	/// <returns></returns>
	bool Find(const T& key) const
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
	/// замена на новое значение. Если "старого" значения нет - просто вставляем новое
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
	/// Количество элементов в таблице
	/// </summary>
	/// <returns></returns>
	int CountElements() const
	{
		int count = 0;
		/// суммируем размеры списков в таблице
		for (int i = 0; i < tableSize; ++i)
		{
			count += buckets[i].Size();
		}
		return count;
	}

	/// <summary>
	/// Печать таблицы
	/// </summary>
	void PrintTable() const
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




	///// <summary>
	///// итератор для хеш-таблицы
	///// </summary>
	///// <typeparam name="T"></typeparam>
	//template <class T>
	//class HashTableIterator
	//{
	//private:
	//	using ListIterator = typename LinkedList<T>::template LinkedListIterator<T>;

	//	const HashTable<T>& hashTable;  // Ссылка на хеш-таблицу
	//	int currentIndex;               // Текущий индекс корзины
	//	ListIterator currentIterator;   // Итератор текущего списка


	//public:
	//	/// конструктор
	//	HashTableIterator(const HashTable<T>& table) : hashTable(table), currentIndex(0), currentIterator(table.buckets[0].begin())
	//	{
	//		// Находим первую непустую корзину
	//		while (currentIndex < hashTable.tableSize && currentIterator == hashTable.buckets[currentIndex].end())
	//		{
	//			++currentIndex;
	//			if (currentIndex < hashTable.tableSize)
	//				currentIterator = hashTable.buckets[currentIndex].begin();
	//		}
	//	}

	//	/// <summary>
	//	/// оператор разыменования
	//	/// </summary>
	//	/// <returns></returns>
	//	T operator*() const
	//	{
	//		return *currentIterator;
	//	}

	//	/// <summary>
	//	/// оператор префиксного инкремента
	//	/// </summary>
	//	/// <param name="other"></param>
	//	/// <returns></returns>
	//	HashTableIterator& operator++()
	//	{
	//		// Переходим к следующему элементу
	//		++currentIterator;

	//		// Если достигнут конец текущего списка, переходим к следующей непустой корзине
	//		while (currentIndex < hashTable.tableSize && currentIterator == hashTable.buckets[currentIndex].end())
	//		{
	//			++currentIndex;
	//			if (currentIndex < hashTable.tableSize)
	//				currentIterator = hashTable.buckets[currentIndex].begin();
	//		}

	//		return *this;
	//	}

	//	/// <summary>
	//	/// не равенство
	//	/// </summary>
	//	/// <returns></returns>
	//	bool operator!=(const HashTableIterator& other) const
	//	{
	//		return currentIndex != other.currentIndex || currentIterator != other.currentIterator;
	//	}
	//};

	///// <summary>
	///// Получить итератор, указывающий на первый элемент хеш-таблицы
	///// </summary>
	///// <returns></returns>
	//HashTableIterator<T> begin() const
	//{
	//	return HashTableIterator<T>();
	//}

	///// <summary>
	///// Получить итератор, указывающий на элемент, следующий за последним элементом хеш-таблицы
	///// </summary>
	///// <returns></returns>
	//HashTableIterator<T> end() const
	//{
	//	return HashTableIterator<T>();
	//}



	
	
};
