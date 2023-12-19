/// ����� ����������� ������
/// @author ������ �.�.
#pragma once
#include "ListNode.h"
/// <summary>
/// ��������� ����� ������������ ������ � �������������� ����� ���� ������ (ListNode)
/// </summary>
/// <typeparam name="T"></typeparam>
template <class T>
class LinkedList {
private:
    ListNode<T>* head;            /// ��������� �� �������� ���� ������
    ListNode<T>* tail;            /// ��������� �� ��������� ���� ������
    int size;                     /// ������ ������

public:
    /// ����������� �� ���������
    LinkedList() : head(nullptr), tail(nullptr), size(0) {}

    /// ����������
    ~LinkedList() {
        ClearList();
    }

    /// ������� �������� � ������ ������
    void InsertAtHead(const T& value) {
        ListNode<T>* newNode = new ListNode<T>(value);

        if (head == nullptr) {
            // ���� ������ ����, ������������� ����� ���� ��� �������� � ���������
            head = newNode;
            tail = newNode;
        }
        else {
            // �����, ��������� ����� ���� � �������� ����� � ��������� �������� ����
            newNode->SetNext(head);
            head->SetPrev(newNode);
            head = newNode;
        }

        size++;
    }

    /// ������� �������� � ����� ������
    void InsertAtTail(const T& value) {
        ListNode<T>* newNode = new ListNode<T>(value);

        if (head == nullptr) {
            // ���� ������ ����, ������������� ����� ���� ��� �������� � ���������
            head = newNode;
            tail = newNode;
        }
        else {
            // �����, ��������� ����� ���� � ��������� ����� � ��������� ��������� ����
            newNode->SetPrev(tail);
            tail->SetNext(newNode);
            tail = newNode;
        }

        size++;
    }

    /// ����� ���� � ��������� ������
    ListNode<T>* Search(const T& key) const {
        ListNode<T>* current = head;

        while (current != nullptr) {
            if (current->Data() == key) {
                return current;
            }

            current = current->Next();
        }

        return nullptr; // ���� � ��������� ������ �� ������
    }

    /// ������� �������� ����� ���� � ��������� ������
    void InsertAfter(const T& key, const T& value) {
        ListNode<T>* node = Search(key);

        if (node == nullptr) {
            // ���� � ��������� ������ �� ������, �� ������ ������� ���������
            return;
        }

        if (node == tail) {
            // ���� ��������� ���� �������� ��������� �����, ��������� ����� ���� � ����� ������
            InsertAtTail(value);
        }
        else {
            // �����, ������� ����� ���� � ��������� ��� � ��������� ����� � ��������� �����
            ListNode<T>* newNode = new ListNode<T>(value);
            newNode->SetPrev(node);
            newNode->SetNext(node->Next());

            node->Next()->SetPrev(newNode);
            node->SetNext(newNode);
            size++;
        }
    }
   
    /// �������� �������� � ��������� ������
    void Remove(const T& key) {
        ListNode<T>* node = Search(key);

        if (node == nullptr) {
            // ���� � ��������� ������ �� ������, �� ������ ������� ���������
            return;
        }

        if (node == head) {
            // ���� ��������� ���� �������� ��������, ��������� �������� ����
            head = node->Next();
            if (head != nullptr) {
                head->SetPrev(nullptr);
            }
        }
        else if (node == tail) {
            // ���� ��������� ���� �������� ���������, ��������� ��������� ����
            tail = node->Prev();
            if (tail != nullptr) {
                tail->SetNext(nullptr);
            }
        }
        else {
            // �����, ��������� ���������� ���� � ��������� ����� � ��������� ������
            node->Prev()->SetNext(node->Next());
            node->Next()->SetPrev(node->Prev());
        }
        delete node;
        node = nullptr;
        size--;
    }

    void Update(const T& oldValue, const T& newValue) {
        ListNode<T>* current = head;
        while (current != nullptr) {
            if (current->Data() == oldValue) {
                current->SetData(newValue);
                return;
            }
            current = current->Next();
        }
    }

    /// ������� ������
    void ClearList() {
        ListNode<T>* current = head;
        while (current != nullptr) {
            ListNode<T>* temp = current;
            current = current->Next();
            delete temp;
        }

        head = nullptr;
        tail = nullptr;
        size = 0;
    }

    /// ����� ������ � ������������ ������
    T* ToListArray() const {
        if (size == 0) {
            return nullptr;
        }

        T* array = new T[size];
        ListNode<T>* current = head;
        int i = 0;

        while (current != nullptr) {
            array[i] = current->Data();
            current = current->Next();
            i++;
        }

        return array;
    }

    /// ��������� ������� ������
    int Size() const {
        return size;
    }


    /// <summary>
    /// ��������� ����� �������� � ������ LinkedList, ��� � �����������
    /// </summary>
    /// <typeparam name="T"></typeparam>
    template<class T>
    class LinkedListIterator {
    private:
        ListNode<T>* current; // ��������� �� ������� ����

    public:
        /// ����������� ��� ����������
        LinkedListIterator(ListNode<T>* node) : current(node) {}

        /// �������� �������������
        T operator*() const {
            return current->Data();
        }

        ListNode<T>* GetCurrentNode() const {
            return current;
        }

        /// �������� ����������� ����������
        /// *this ���������� ������ �� ������� ������ ���������
        LinkedListIterator<T>& operator++() {
            current = current->Next();
            return *this;
        }

        /// �������� ������������ ����������
        /// temp ��� ���������� ��������� �� �������� � ����������
        LinkedListIterator<T> operator++(int) {
            LinkedListIterator<T> temp = *this;
            current = current->Next();
            return temp;
        }

        /// �������� "�����"
        bool operator==(const LinkedListIterator<T>& it) const {
            return current == it.current;
        }

        /// ��������� "�� �����"
        bool operator!=(const LinkedListIterator<T>& it) const {
            return current != it.current;
        }
    };

    /// ������ ������� ������
    LinkedListIterator<T> begin() const {
        return LinkedListIterator<T>(head);
    }

    /// �������, ��������� �� ��������� ��������� ������
    LinkedListIterator<T> end() const {
        return LinkedListIterator<T>(nullptr);
    }
};