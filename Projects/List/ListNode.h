/// ����� ���� ������
/// @author ������ �.�.
#pragma once

/// <summary>
/// ��������� ����� ���� ������������ ������
/// </summary>
/// <typeparam name="T"></typeparam>
template <class T>
class ListNode
{
private:
	T data;			   /// ������ ����
	ListNode<T>* prev; /// ��������� �� ���������� ����
	ListNode<T>* next; /// ��������� �� ��������� ����
public:
	/// ����������� ��� ����������
	ListNode() : next(nullptr), prev(nullptr) {}

	/// ����������� � ���������� "������"
	ListNode(const T& data_) : data(data_), next(nullptr), prev(nullptr) {}

	/// ���������� Next
	void SetNext(ListNode<T>* newNext) {
		next = newNext;
		if (newNext != nullptr) {
			newNext->prev = this;
		}
	}
	/// ���������� Prev
	void SetPrev(ListNode<T>* newPrev) {
		prev = newPrev;
		if (newPrev != nullptr) {
			newPrev->next = this;
		}
	}

	/// ������� next
	T Data() {
		return data;
	}

	/// ������� next
	ListNode* Next() {
		return next;
	}

	/// ������� prev
	ListNode* Prev() {
		return prev;
	}
};