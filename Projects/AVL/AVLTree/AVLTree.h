#pragma once
#include "AVLTreeNode.h"
#include "../../Tree/Tree/BinarySearchTree.h"

template <class T>
class AVLTree {
private:
    AVLTreeNode<T>* root;/// корень
    AVLTreeNode<T>* curr;/// текущий узел
public:

    /// Конструктор без параметров
    AVLTree() : root(nullptr), curr(nullptr) {}


    AVLTree(const T& data) : root(new AVLTreeNode<T>(data)), curr(nullptr) {}

    /// Деструктор
    ~AVLTree() {

    };

    /// Вернуть данные
    T Data(AVLTreeNode<T>* curr) const
    {
        return curr->Data();
    }

    /// Вернуть корень
    AVLTreeNode<T>* Root() {
        return root;
    }

    /// Установить корень
    void SetRoot(AVLTreeNode<T>* newRoot) {
        root = newRoot;
    }

    /// Установить текущий
    void SetCurr(AVLTreeNode<T>* newRoot) {
        curr = newRoot;
    }

    /// Вставка
    void Insert(const T& key) {
        root = root->insert(root, key);
            //std::cout << "xd";
    }

    /// Удаление узла
    void Delete(const T& key) {
        root = root->remove(root, key);
    }



    void Print() {
        this->PrintTree(root, 0);
    }

    // промежуток между уровнями
    const int indentBlock = 6;

    // вставить numпробелов в текущей строке
    void IndentBlanks(int num)
    {
        for (int i = 0; i < num; i++)
            std::cout << "  ";
    }

    void PrintTree()
    {
        root->PrintTree(root, 0);
    }

    /// Размер
    int Size() {
        return root->Size();
    }

    ///// Поиск
    //AVLTreeNode<T>* Search(const T& key) {
    //    return root->Search(key);
    //}

    ///// Размер
    //int Size() {
    //    return root->Size();
    //}

    ///// Глубина
    //int Depth() {
    //    return root->Depth();
    //}

  /*  /// Найти минимальный
    AVLTreeNode<T>* FindMin() {
        return root->FindMin();
    }

    /// Найти максимальный
    AVLTreeNode<T>* FindMax() {
        return root->FindMax();
    }

    /// Следующий наибольший для узла
    AVLTreeNode<T>* Successor(const T& key) {
        return root->Successor(key);
    }*/



   /* /// Добавить в массив LNR
    void AddToArrayLNR(T arr[]) {
        int i = 0;
        root->AddToArrayLNR(arr, i);
    }

    /// Копировать дерево
    AVLTree<T>* CopyTree() {
        AVLTree<T>* copiedTree = new AVLTree<T>();
        copiedTree->SetRoot(root->CopyTree());
        return copiedTree;
    }*/


    ///// <summary>
    ///// шаблонный класс итератор в классе BinarySearchTree, как в итерируемом
    ///// с порядком обхода в глубину LNR
    ///// </summary>
    ///// <typeparam name="T"></typeparam>
    //template<class T>
    //class Iterator {
    //private:
    //    AVLTreeNode<T>* current; // Указатель на текущий узел
    //    std::stack<AVLTreeNode<T>*> nodeStack;  // Стек для обхода дерева

    //    // Заполняет стек узлами левого поддерева, начиная с заданного узла
    //    void FillStack(AVLTreeNode<T>* node)
    //    {
    //        // пока указатель - не пустой узел
    //        while (node) {
    //            // добавляем в стек
    //            nodeStack.push(node);
    //            // переход к левому узлу
    //            node = node->Left();
    //        }
    //    }
    //public:
    //    /// Конструктор без параметров
    //    Iterator(AVLTreeNode<T>* node) : current(node)
    //    {
    //        // Заполняем стек начальным состоянием
    //        FillStack(current);
    //        // Если стек не пустой, получаем следующий узел из стека
    //        if (!nodeStack.empty()) {
    //            current = nodeStack.top();
    //            nodeStack.pop();
    //        }
    //        else
    //            current = nullptr;
    //    }

    //    /// Оператор разыменования
    //    T operator*() const {
    //        return current->Data();
    //    }

    //    /// Оператор префиксного инкремента
    //    /// *this возвращает ссылку на текущий объект итератора
    //    /// с обходом LNR
    //    Iterator<T>& operator++() {
    //        // Если стек пустой - выход
    //        if (nodeStack.empty()) {
    //            current = nullptr;
    //            return *this;
    //        }
    //        // Если стек не пустой, получаем следующий узел из стека
    //        current = nodeStack.top();
    //        nodeStack.pop();

    //        // Заполняем стек правым поддеревом текущего узла
    //        FillStack(current->Right());

    //        return *this;
    //    }

    //    /// Оператор постфиксного инкремента
    //    /// temp для сохранения состояния до перехода к следующему
    //    /// с обходом LNR
    //    Iterator<T> operator++(int) {
    //        Iterator temp = *this;
    //        ++(*this);
    //        return temp;
    //    }

    //    /// Оператор "равно"
    //    bool operator==(const Iterator<T>& it) const {
    //        return current == it.current;
    //    }

    //    /// Оператора "не равно"
    //    bool operator!=(const Iterator<T>& it) const {
    //        return !(*this == it);
    //    }
    //};

    ///// Первый элемент списка
    //Iterator<T> begin() const {
    //    return Iterator<T>(root);
    //}

    ///// Элемент, следующий за последним элементом списка
    //Iterator<T> end() const {
    //    return Iterator<T>(nullptr);
    //}
};