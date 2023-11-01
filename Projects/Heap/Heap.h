#pragma once
#include <vector>
template <class T>
class MaxHeap {
private:
	T* heap;      // Массив, хранящий кучу
	unsigned int capacity; // куча емкости
	unsigned int size;     // Текущий размер кучи

		// Функция фильтрации вверх, используется при вставке элемента
	void filterup(int start) {
		int curr = start;				// Текущая позиция, то есть конец массива
		int parent = (curr - 1) / 2;    // Позиция родительского узла в текущей позиции
		T temp = heap[curr];			// Ключевое значение текущего узла


		while (curr > 0) {
			// Если значение текущей позиции меньше или равно значению родительского узла, выходим из цикла
			if (temp <= heap[parent])
				break;
			else {
				// Значения текущего и родительского узла меняем местами
				heap[curr] = heap[parent];
				curr = parent;
				parent = (parent - 1) / 2;
			}
		}
		// Значение текущего узла устанавливается на свое место в куче
		heap[curr] = temp;
	}

	// Функция фильтрации вниз, используется при удалении элемента
	void filterdown(int start, int end) {
		int curr = start;			// Текущий узел, который будет удален
		int left = 2 * curr + 1;    // Позиция левого поддерева
		T temp = heap[curr];		// Ключевое значение текущего узла
		while (left <= end) {
			// Определение, какое поддерево больше - левое или правое
			if (left < end && heap[left] < heap[left + 1])
				left++;
			// Правое поддерево больше
			if (temp >= heap[left])
				// Если значение текущего узла больше или равно значению выбранного поддерева, выходим из цикла
				break;
			else {
				heap[curr] = heap[left];
				// Значение выбранного поддерева перемещается на текущий узел
				curr = left;
				left = 2 * left + 1;
			}
		}
		// Значение текущего узла устанавливается на свое место в куче
		heap[curr] = temp;
	}

		
	// Получение индекса элемента в куче
	int getIndex(T data) {
		for (int i = 0; i < size; i++)
			if (data == heap[i])
				return i;
		// Если элемент не найден, возвращаем недопустимое значение
		throw std::out_of_range("Element not found");
	}

public:

	// Конструктор 
	MaxHeap(int capacity_) : heap(0), capacity(capacity_), size(0) {
		heap = new T[capacity];
	}

	// Деструктор
	~MaxHeap() {
		delete[] heap;
	}

	int Size() {
		return size;
	}

	T Max() {
		if (size == 0) throw std::out_of_range("Heap is empty");
		T temp = heap[0];
		this->remove(heap[0]);
		return temp;
	}

	// Вставка элемента с использованием фильтрации вверх
	int insert(T data) {
		if (size >= capacity) {
			// Максимальный размер кучи достигнут
			int newCapacity = capacity * 2; // Увеличение размера в два раза
			//перевыделение памяти
			T* newHeap = new T[newCapacity];

			// Копирование существующих элементов в новый блок памяти
			for (int i = 0; i < size; i++)
			{
				newHeap[i] = heap[i];
			}

			// Освобождение старого блока памяти
			delete[] heap;

			// Обновление указателя на новый блок памяти и максимального размера кучи
			heap = newHeap;
			capacity = newCapacity;
		}
		// Если куча была пуста
		if (size == 0) {
			heap[0] = data;
			size++;
		}
		else {
			heap[size] = data;  // Помещаем элемент в конец массива
			filterup(size);		// Выполняем фильтрацию вверх
			size++;				// Увеличиваем размер кучи на 1
			return 0;
		}
	}


	// Удаление элемента с использованием фильтрации вниз
	int remove(T data) {
		int idx;
		if (size == 0)				// Если куча пуста, возвращаем недопустимое значение
			throw std::out_of_range("Heap is empty");
		idx = getIndex(data);		// Получаем индекс элементав куче
		heap[idx] = heap[--size];   // Заменяем элемент, который нужно удалить, последним элементом в куче
		filterdown(idx, size - 1);	// Выполняем фильтрацию вниз
		return 0;
	}

	// Вывод элементов кучи
	void print() {
		for (int i = 0; i < size; i++)
		{
			std::cout << heap[i] << " ";
		}
		std::cout << std::endl;
	}

	// Вывод элементов кучи в вектор
	std::vector<T> toVector()
	{
		std::vector<T> vec;
		for (int i = 0; i < size; i++)
		{
			vec.push_back(heap[i]);
		}
		return vec;
	}

	// Основная функция, выполняющая пирамидальную сортировку
	//template <class T>
	std::vector<T> heapSort()
	{
		std::vector<T> vec;
		int size_ = size;
		// Один за другим извлекаем элементы из кучи
		for (int i = 0; i < size_; i++)
		{
			vec.push_back(this->Max());
		}
		return vec;
	}
};

