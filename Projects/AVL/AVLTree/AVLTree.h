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


    AVLTree(const T& data) : root(new AVLTreeNode<T>(data)), curr(nullptr) {}

    /// ����������
    ~AVLTree() {

    };

    /// ������� ������
    T Data(AVLTreeNode<T>* curr) const
    {
        return curr->Data();
    }

    /// ������� ������
    AVLTreeNode<T>* Root() {
        return root;
    }

    /// ���������� ������
    void SetRoot(AVLTreeNode<T>* newRoot) {
        root = newRoot;
    }

    /// ���������� �������
    void SetCurr(AVLTreeNode<T>* newRoot) {
        curr = newRoot;
    }

    /// �������
    void Insert(const T& key) {
        root = root->insert(root, key);
            //std::cout << "xd";
    }

    /// �������� ����
    void Delete(const T& key) {
        root = root->remove(root, key);
    }



    void Print() {
        this->PrintTree(root, 0);
    }

    // ���������� ����� ��������
    const int indentBlock = 6;

    // �������� num�������� � ������� ������
    void IndentBlanks(int num)
    {
        for (int i = 0; i < num; i++)
            std::cout << "  ";
    }

    void PrintTree()
    {
        root->PrintTree(root, 0);
    }

    /// ������
    int Size() {
        return root->Size();
    }

    ///// �����
    //AVLTreeNode<T>* Search(const T& key) {
    //    return root->Search(key);
    //}

    ///// ������
    //int Size() {
    //    return root->Size();
    //}

    ///// �������
    //int Depth() {
    //    return root->Depth();
    //}

  /*  /// ����� �����������
    AVLTreeNode<T>* FindMin() {
        return root->FindMin();
    }

    /// ����� ������������
    AVLTreeNode<T>* FindMax() {
        return root->FindMax();
    }

    /// ��������� ���������� ��� ����
    AVLTreeNode<T>* Successor(const T& key) {
        return root->Successor(key);
    }*/



   /* /// �������� � ������ LNR
    void AddToArrayLNR(T arr[]) {
        int i = 0;
        root->AddToArrayLNR(arr, i);
    }

    /// ���������� ������
    AVLTree<T>* CopyTree() {
        AVLTree<T>* copiedTree = new AVLTree<T>();
        copiedTree->SetRoot(root->CopyTree());
        return copiedTree;
    }*/


    ///// <summary>
    ///// ��������� ����� �������� � ������ BinarySearchTree, ��� � �����������
    ///// � �������� ������ � ������� LNR
    ///// </summary>
    ///// <typeparam name="T"></typeparam>
    //template<class T>
    //class Iterator {
    //private:
    //    AVLTreeNode<T>* current; // ��������� �� ������� ����
    //    std::stack<AVLTreeNode<T>*> nodeStack;  // ���� ��� ������ ������

    //    // ��������� ���� ������ ������ ���������, ������� � ��������� ����
    //    void FillStack(AVLTreeNode<T>* node)
    //    {
    //        // ���� ��������� - �� ������ ����
    //        while (node) {
    //            // ��������� � ����
    //            nodeStack.push(node);
    //            // ������� � ������ ����
    //            node = node->Left();
    //        }
    //    }
    //public:
    //    /// ����������� ��� ����������
    //    Iterator(AVLTreeNode<T>* node) : current(node)
    //    {
    //        // ��������� ���� ��������� ����������
    //        FillStack(current);
    //        // ���� ���� �� ������, �������� ��������� ���� �� �����
    //        if (!nodeStack.empty()) {
    //            current = nodeStack.top();
    //            nodeStack.pop();
    //        }
    //        else
    //            current = nullptr;
    //    }

    //    /// �������� �������������
    //    T operator*() const {
    //        return current->Data();
    //    }

    //    /// �������� ����������� ����������
    //    /// *this ���������� ������ �� ������� ������ ���������
    //    /// � ������� LNR
    //    Iterator<T>& operator++() {
    //        // ���� ���� ������ - �����
    //        if (nodeStack.empty()) {
    //            current = nullptr;
    //            return *this;
    //        }
    //        // ���� ���� �� ������, �������� ��������� ���� �� �����
    //        current = nodeStack.top();
    //        nodeStack.pop();

    //        // ��������� ���� ������ ���������� �������� ����
    //        FillStack(current->Right());

    //        return *this;
    //    }

    //    /// �������� ������������ ����������
    //    /// temp ��� ���������� ��������� �� �������� � ����������
    //    /// � ������� LNR
    //    Iterator<T> operator++(int) {
    //        Iterator temp = *this;
    //        ++(*this);
    //        return temp;
    //    }

    //    /// �������� "�����"
    //    bool operator==(const Iterator<T>& it) const {
    //        return current == it.current;
    //    }

    //    /// ��������� "�� �����"
    //    bool operator!=(const Iterator<T>& it) const {
    //        return !(*this == it);
    //    }
    //};

    ///// ������ ������� ������
    //Iterator<T> begin() const {
    //    return Iterator<T>(root);
    //}

    ///// �������, ��������� �� ��������� ��������� ������
    //Iterator<T> end() const {
    //    return Iterator<T>(nullptr);
    //}
};