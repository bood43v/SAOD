#pragma once
#include "AVLTreeNode.h"
#include "../../Tree/Tree/BinarySearchTree.h"

template <class T>
class AVLTree {
private:
    AVLTreeNode<T>* root;/// ������
    AVLTreeNode<T>* curr;/// ������� ����
public:

    /// ����������� ��� ����������
    AVLTree() : root(nullptr), curr(nullptr) {}

    /// <summary>
    /// ���������� � ���������� ����
    /// </summary>
    /// <param name="data"></param>
    AVLTree(const T& data) : root(new AVLTreeNode<T>(data)), curr(nullptr) {}

    /// ����������
    ~AVLTree() {

    };

    /// ������� ������
    T Data(AVLTreeNode<T>* node) const
    {
        return node->Data();
    }

    /// ���������� ������
    void SetRoot(AVLTreeNode<T>* newRoot) {
        root = newRoot;
    }

    /// ������� ������
    AVLTreeNode<T>* Root() {
        return root;
    }

    /// �������
    void Insert(const T& key) {
        root = root->Insert(key);
    }

    /// �������� ����
    void Remove(const T& key) {
        root = root->Remove(key);
    }

    /// ������ ������ �������������
    void Print()
    {
        root->PrintTree(root, 0);
    }

    /// ������
    int Size() {
        return root->Size();
    }

    /// �����
    AVLTreeNode<T>* Search(const T& key) {
        return dynamic_cast<AVLTreeNode<T>*>(root->Search(key));
    }

    /// �������
    int Depth() {
        return root->Depth();
    }

    /// ����� �����������
    AVLTreeNode<T>* FindMin() {
        return dynamic_cast<AVLTreeNode<T>*>(root->FindMin());
    }

    ///����� ������������
    AVLTreeNode<T>* FindMax() {
        return dynamic_cast<AVLTreeNode<T>*>(root->FindMax());
    }

    /// ��������� ���������� ��� ����
    AVLTreeNode<T>* Successor(const T& key) {
        return dynamic_cast<AVLTreeNode<T>*>(root->Successor(key));
    }

    /// �������� � ������ LNR
    void AddToArrayLNR(T arr[]) {
        int i = 0;
        root->AddToArrayLNR(arr, i);
    }

    /// ���������� ������
    AVLTree<T>* CopyTree() {
        AVLTree<T>* copiedTree = new AVLTree<T>();
        copiedTree->SetRoot(dynamic_cast<AVLTreeNode<T>*>(root->CopyTree()));
        return copiedTree;
    }


    /// <summary>
    /// ��������� ����� �������� � ������ BinarySearchTree, ��� � �����������
    /// � �������� ������ � ������� LNR
    /// </summary>
    /// <typeparam name="T"></typeparam>
    template<class T>
    class Iterator {
    private:
        AVLTreeNode<T>* current; // ��������� �� ������� ����
        std::stack<AVLTreeNode<T>*> nodeStack;  // ���� ��� ������ ������

        // ��������� ���� ������ ������ ���������, ������� � ��������� ����
        void FillStack(AVLTreeNode<T>* node)
        {
            // ���� ��������� - �� ������ ����
            while (node) {
                // ��������� � ����
                nodeStack.push(node);
                // ������� � ������ ����
                node = dynamic_cast<AVLTreeNode<T>*>(node->Left());
            }
        }
    public:
        /// ����������� ��� ����������
        Iterator(AVLTreeNode<T>* node) : current(node)
        {
            // ��������� ���� ��������� ����������
            FillStack(dynamic_cast<AVLTreeNode<T>*>(current));
            // ���� ���� �� ������, �������� ��������� ���� �� �����
            if (!nodeStack.empty()) {
                current = nodeStack.top();
                nodeStack.pop();
            }
            else
                current = nullptr;
        }

        /// �������� �������������
        T operator*() const {
            return current->Data();
        }

        /// �������� ����������� ����������
        /// *this ���������� ������ �� ������� ������ ���������
        /// � ������� LNR
        Iterator<T>& operator++() {
            // ���� ���� ������ - �����
            if (nodeStack.empty()) {
                current = nullptr;
                return *this;
            }
            // ���� ���� �� ������, �������� ��������� ���� �� �����
            current = nodeStack.top();
            nodeStack.pop();

            // ��������� ���� ������ ���������� �������� ����
            FillStack(dynamic_cast<AVLTreeNode<T>*>(current->Right()));

            return *this;
        }

        /// �������� ������������ ����������
        /// temp ��� ���������� ��������� �� �������� � ����������
        /// � ������� LNR
        Iterator<T> operator++(int) {
            Iterator temp = *this;
            ++(*this);
            return temp;
        }

        /// �������� "�����"
        bool operator==(const Iterator<T>& it) const {
            return current == it.current;
        }

        /// ��������� "�� �����"
        bool operator!=(const Iterator<T>& it) const {
            return !(*this == it);
        }
    };

    /// ������ ������� ������
    Iterator<T> begin() const {
        return Iterator<T>(root);
    }

    /// �������, ��������� �� ��������� ��������� ������
    Iterator<T> end() const {
        return Iterator<T>(nullptr);
    }
};