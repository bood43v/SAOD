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
    ListNode<T>* head;            // ��������� �� �������� ���� ������
    ListNode<T>* tail;            // ��������� �� ��������� ���� ������
    int size;               // ������ ������

public:
    // ����������� �� ���������
    LinkedList() : head(nullptr), tail(nullptr), size(0) {}

    // ����������
    ~LinkedList() {
        ClearList();
    }

    // ������� �������� � ������ ������
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

    // ������� �������� � ����� ������
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

    // ����� ���� � ��������� ������
    ListNode<T>* Search(const T& key) {
        ListNode<T>* current = head;

        while (current != nullptr) {
            if (current->Data() == key) {
                return current;
            }

            current = current->Next();
        }

        return nullptr; // ���� � ��������� ������ �� ������
    }

    // ������� �������� ����� ���� � ��������� ������
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
   
    // �������� �������� � ��������� ������
    void Remove(const T& key) {
        ListNode<T>* node = Search(key);

        if (node == nullptr) {
            // ���� � ��������� ������ �� ������, �� ������ ������� ���������
            return;
        }

        if (node == head) {
            // ���� ��������� ���� �������� ��������, ��������� �������� ����
            head = node->next;
            if (head != nullptr) {
                head->prev = nullptr;
            }
        }
        else if (node == tail) {
            // ���� ��������� ���� �������� ���������, ��������� ��������� ����
            tail = node->prev;
            if (tail != nullptr) {
                tail->next = nullptr;
            }
        }
        else {
            // �����, ��������� ���������� ���� � ��������� ����� � ��������� ������
            node->prev->next = node->next;
            node->next->prev = node->prev;
        }

        delete node;
        size--;
    }

    // ������� ������
    void ClearList() {
        ListNode<T>* current = head;
        while (current != nullptr) {
            ListNode<T>* temp = current;
            current = current->next;
            delete temp;
        }

        head = nullptr;
        tail = nullptr;
        size = 0;
    }

    // ����� ������ � ������������ ������
    T* ToListArray() const {
        if (size == 0) {
            return nullptr;
        }

        T* array = new T[size+1];
        ListNode<T>* current = head;
        int i = 0;

        while (current != nullptr) {
            array[i] = current->Data();
            current = current->Next();
            i++;
        }

        return array;
    }

    // ��������� ������� ������
    int getSize() const {
        return size;
    }
};