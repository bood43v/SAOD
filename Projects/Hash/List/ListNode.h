/// Класс узел списка
/// @author Будаев Г.Б.
#pragma once

/// <summary>
/// шаблонный класс узел односвязного списка
/// </summary>
/// <typeparam name="T"></typeparam>
template <class T>
class ListNode
{
private:
	T data;			   /// данные узла
	ListNode<T>* prev; /// указатель на предыдущий узел
	ListNode<T>* next; /// указатель на следующий узел
public:
	/// Конструктор без параметров
	ListNode() : next(nullptr), prev(nullptr) {}

	/// Конструктор с параметром "данные"
	ListNode(const T& data_) : data(data_), next(nullptr), prev(nullptr) {}

	/// Установить Next
	void SetNext(ListNode<T>* newNext) {
		next = newNext;
	}
	/// Установить Prev
	void SetPrev(ListNode<T>* newPrev) {
		prev = newPrev;
	}

	/// Установить next
	/// Установить Данные
	void SetData(const T& data_) {
		data = data_;
	}

	/// вернуть Data
	/// вернуть next
	T Data() {
		return data;
	}

	/// вернуть next
	ListNode* Next() {
		return next;
	}

	/// вернуть prev
	ListNode* Prev() {
		return prev;
	}
};