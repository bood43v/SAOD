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
	}
	/// ���������� Prev
	void SetPrev(ListNode<T>* newPrev) {
		prev = newPrev;
	}

	/// ���������� next
	/// ���������� ������
	void SetData(const T& data_) {
		data = data_;
	}

	/// ������� Data
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