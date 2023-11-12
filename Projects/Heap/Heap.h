/// Шаблонный класс кучи
/// Минимальный capacity для кучи при инициализации - 1.
/// В случае, если параметром конструктора с одним параметром параметр <= 0 -> capacity автоматически приравнивается 1.
/// @author Будаев Г.Б.

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

	/// Функция фильтрации вниз, используется при удалении элемента
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


	/// Получение индекса элемента в куче
	int getIndex(T data) {
		for (int i = 0; i < size; i++)
			if (data == heap[i])
				return i;
		// Если элемент не найден, возвращаем недопустимое значение
		return -1;
	}

public:
	/// Конструктор с размером
	MaxHeap(unsigned int capacity_) : heap(nullptr), capacity(capacity_ < 0 ? capacity_ : 1), size(0) {
		//if (capacity_ <= 0) capacity = 1;
		heap = new T[capacity];
	}

	// Конструктор без параметров
	MaxHeap() : heap(nullptr), capacity(1), size(0) {
		heap = new T[capacity];
	}

	// Конструктор с вектором
	// Если размер вектора = 0, то capacity = 1, чтобы была выделена память под 1 элемент
	MaxHeap(const std::vector<T>& arr) : heap(nullptr), capacity(arr.size() != 0 ? arr.size() : 1), size(0) {
		heap = new T[capacity];
		/// вставка элементов из вектора в кучу итератором
		for (const T& item : arr) {
			insert(item);
		}
	}

	/// Конструктор копирования
	MaxHeap(const MaxHeap& heap_) : heap(nullptr), capacity(heap_.capacity), size(heap_.Size()) {
		heap = new T[capacity];
		memcpy(heap, heap_.heap, capacity * sizeof(T));

		/*std::cout << "Copy constructor" << std::endl;*/
	}

	/// Конструктор перемещения
	MaxHeap(MaxHeap&& heap_) noexcept : heap(heap_.heap), capacity(heap_.capacity), size(heap_.size) {
		heap_.heap = nullptr;
		heap_.capacity = 0;
		heap_.size = 0;

	/*	std::cout << "Move constructor" << std::endl;*/
	}

	/// Оператор присваивания копированием
	MaxHeap<T>& operator=(const MaxHeap<T>& heap_) {
		if (this != &heap_) {
			delete[] heap;
			capacity = heap_.capacity;
			size = heap_.size;
			heap = new T[capacity];
			memcpy(heap, heap_.heap, capacity * sizeof(T));
			//for (int i = 0; i < size; i++) {
			//	heap[i] = heap_.heap[i];
			//}
		}
		/*std::cout << "Assignment operator" << std::endl;*/
		return *this;
	}

	// Для обозначения объекта, который готов к перемещению(и может быть украден), 
	// используется r-value ссылка(&&).Функция std::move() преобразует объект в r-value ссылку, 
	// что позволяет вызывать конструкторы перемещения или операторы присваивания перемещением.

	/// Оператор присваивания перемещением
	MaxHeap<T>& operator=(MaxHeap<T>&& heap_) noexcept {
		if (this != &heap_) {
			delete[] heap;
			heap = heap_.heap;
			capacity = heap_.capacity;
			size = heap_.size;
			heap_.heap = nullptr;
			heap_.capacity = 0;
			heap_.size = 0;
		}
		/*std::cout << "Move Assignment Operator" << std::endl;*/
		return *this;
	}


	/// Деструктор
	~MaxHeap() {
		delete[] heap;
	}

	/// Размер
	int Size() const {
		return size;
	}

	/// вывод наибольшего значения кучи 
	T Max() {
		if (size == 0) throw "Heap is empty";
		T temp = heap[0];
		this->remove(heap[0]);
		return temp;
	}

	/// Вставка элемента с использованием фильтрации вверх
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
		// Если куча была пуста и под её массив не выделена память
		if (size == 0 && capacity == 0) {
			// Максимальный размер кучи достигнут
			int newCapacity = 1; // Размер 1
			// перевыделение памяти
			T* newHeap = new T[newCapacity];
			// Освобождение старого блока памяти
			delete[] heap;
			// Обновление указателя на новый блок памяти и максимального размера кучи
			heap = newHeap;
			capacity = newCapacity;
			heap[0] = data;
			size = 1;
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


	/// Удаление элемента с использованием фильтрации вниз
	void remove(T data) {
		int idx;
		if (size == 0)
			return;
		//throw "Heap is empty"; // Если куча пуста, возвращаем недопустимое значение
		idx = getIndex(data);		// Получаем индекс элементав куче
		if (idx != -1) {
			heap[idx] = heap[--size];   // Заменяем элемент, который нужно удалить, последним элементом в куче
			filterdown(idx, size - 1);	// Выполняем фильтрацию вниз
		}
		//return 0;
	}

	// Вывод элементов кучи
	void print() {
		for (int i = 0; i < size; i++)
		{
			std::cout << heap[i] << " ";
		}
		std::cout << std::endl;
	}

	/// Вывод элементов кучи в вектор
	std::vector<T> toVector()
	{
		std::vector<T> vec;
		for (int i = 0; i < size; i++)
		{
			vec.push_back(heap[i]);
		}
		return vec;
	}

	/// Основная функция, выполняющая сортировку кучей
	///template <class T>
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

