/// Класс BinarySearchTree бинарного дерева
/// @author Будаев Г.Б.
#pragma once
#include "TreeNode.h"

/// <summary>
/// шаблонный класс бинарное дерево поиска, использующий класс узел дерева
/// </summary>
/// <typeparam name="T"></typeparam>
template<class T>
class BSTree
{
private:
    TreeNode<T>* root;/// корень
    TreeNode<T>* curr;/// текущий узел
   
    /// Рекурсивная функция для удаления дерева
    void DeleteTree(TreeNode<T>* node) {
        if (node) {
            DeleteTree(node->Left());   // Рекурсивно удаляем левое поддерево
            DeleteTree(node->Right());  // Рекурсивно удаляем правое поддерево
            delete node;                // Удаляем текущий узел
        }
    }
public:
    /// Конструктор без параметров
    BSTree() {
        root = new TreeNode<T>();
        curr = new TreeNode<T>();
    };

    /// Конструктор с параметром - корень дерева
    BSTree(const T& node) {
        this->Insert(node);
    };

    /// Конструктор копирования
    BSTree(const BSTree<T>& tree) {
        root = CopyTree(tree->root);
    }

    /// Оператор присваивания
    BSTree<T>& operator=(const BSTree<T>& tree) {
        if (this == &tree) {
            return *this;               /// Проверка на самоприсваивание
        }
        DeleteTree(root);               /// Освобождаем память текущего дерева
        root = CopyTree(tree->Root());  /// Копируем узлы из исходного дерева в новое дерево
        return *this;                   /// Возвращаем ссылку на текущий объект
    }

    /// Деструктор
    ~BSTree() {
        DeleteTree(root);   
    };

    /// Вернуть данные
    T Data(TreeNode<T>* curr) const
    {
        return curr->Data();
    }

    /// Вернуть корень
    TreeNode<T>* Root() {
        return root;
    }

    /// Установить корень
    void SetRoot(TreeNode<T>* newRoot) {
        root = newRoot;
    }

    /// Вставка
    void Insert(const T& key) {
        root->Insert(key);
    }
    
    /// Поиск
    TreeNode<T>* Search(const T& key) {
        return root->Search(key);
    }

    /// Размер
    int Size() {
        return root->Size();
    }

    /// Глубина
    int Depth() {
        return root->Depth();
    }

    /// Найти минимальный
    TreeNode<T>* FindMin() {
        return root->FindMin();
    }

    /// Найти максимальный
    TreeNode<T>* FindMax() {
        return root->FindMax();
    }

    /// Следующий наибольший для узла
    TreeNode<T>* Successor(const T& key) {
        return root->Successor(key); 
    }

    /// Удаление узла
    TreeNode<T>* Remove(const T& key) {
        return root->Remove(root, key);
    }

    /// Добавит в массив LNR
    void AddToArrayLNR(T arr[]) {
        int i = 0;
        root->AddToArrayLNR(arr,i);
    }

    /// Копировать дерево
    BSTree<T>* CopyTree() {
        BSTree<T>* copiedTree = new BSTree<T>();
        copiedTree->SetRoot(root->CopyTree());
        return copiedTree;
    }

    /// Удвоение значения всех узлов
    void Double() {
        root->Double(root);
    }
};