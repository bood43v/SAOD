/// ����� BinarySearchTree ��������� ������
/// @author ������ �.�.
#pragma once
#include "TreeNode.h"
#include <stack>

/// <summary>
/// ��������� ����� �������� ������ ������, ������������ ����� ���� ������
/// </summary>
/// <typeparam name="T"></typeparam>
template<class T>
class BSTree
{
private:
    TreeNode<T>* root;/// ������
    TreeNode<T>* curr;/// ������� ����
   
    /// ����������� ������� ��� �������� ������
    void DeleteTree(TreeNode<T>* node) {
        if (node) {
            DeleteTree(node->Left());   // ���������� ������� ����� ���������
            DeleteTree(node->Right());  // ���������� ������� ������ ���������
            delete node;                // ������� ������� ����
        }
    }

public:
    /// ����������� ��� ����������
    BSTree() {
        root = new TreeNode<T>();
        curr = new TreeNode<T>();
    };

    
    /// ����������� � ���������� - ������ ������
    BSTree(const T& node) {
        this->Insert(node);
    };

    /// ����������� �����������
    BSTree(const BSTree<T>& tree) {
        root = CopyTree(tree->root);
    }

    /// �������� ������������
    BSTree<T>& operator=(const BSTree<T>& tree) {
        if (this == &tree) {
            return *this;               /// �������� �� ����������������
        }
        DeleteTree(root);               /// ����������� ������ �������� ������
        root = CopyTree(tree->Root());  /// �������� ���� �� ��������� ������ � ����� ������
        return *this;                   /// ���������� ������ �� ������� ������
    }

    /// todo: ����������� �����������, �������� ������������ �����������
    


    /// ����������
    ~BSTree() {
        DeleteTree(root);   
    };

    /// �������� ������
    void ClearTree() {
        DeleteTree(root);
        root = nullptr;
    }

    /// ������� ������
    T Data(TreeNode<T>* curr) const
    {
        return curr->Data();
    }

    /// ������� ������
    TreeNode<T>* Root() {
        return root;
    }

    /// ���������� ������
    void SetRoot(TreeNode<T>* newRoot) {
        root = newRoot;
    }

    /// �������
    void Insert(const T& key) {
        root->Insert(key);
    }
    
    /// �����
    TreeNode<T>* Search(const T& key) {
        return root->Search(key);
    }

    /// ������
    int Size() {
        return root->Size();
    }

    /// �������
    int Depth() {
        return root->Depth();
    }

    /// ����� �����������
    TreeNode<T>* FindMin() {
        return root->FindMin();
    }

    /// ����� ������������
    TreeNode<T>* FindMax() {
        return root->FindMax();
    }

    /// ��������� ���������� ��� ����
    TreeNode<T>* Successor(const T& key) {
        return root->Successor(key); 
    }

    /// �������� ����
    void Remove(const T& key) {
        root = root->Remove(root, key);
    }

    /// �������� � ������ LNR
    void AddToArrayLNR(T arr[]) {
        int i = 0;
        root->AddToArrayLNR(arr,i);
    }

    /// ���������� ������
    BSTree<T>* CopyTree() {
        BSTree<T>* copiedTree = new BSTree<T>();
        copiedTree->SetRoot(root->CopyTree());
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
        TreeNode<T>* current; // ��������� �� ������� ����
        std::stack<TreeNode<T>*> nodeStack;  // ���� ��� ������ ������

        // ��������� ���� ������ ������ ���������, ������� � ��������� ����
        void FillStack(TreeNode<T>* node)
        {
            // ���� ��������� - �� ������ ����
            while (node) {
                // ��������� � ����
                nodeStack.push(node);
                // ������� � ������ ����
                node = node->Left();
            }
        }
    public:
        /// ����������� ��� ����������
        Iterator(TreeNode<T>* node) : current(node) 
        {
            // ��������� ���� ��������� ����������
            FillStack(current);
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
            FillStack(current->Right());

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










//// ������� ��� ������ ������ � ���������� ������� � ������� ��������
//template<typename T>
//void apply(TreeNode<T>* root, T(*func)(T)) {
//    if (root != nullptr) {
//        // ��������� ������� � �������� ��������
//        root->SetData(func(root->Data()));
//        // ���������� ������� ����� � ������ ����������
//        apply(root->Left(), func);
//        apply(root->Right(), func);
//    }
//}
