/// Класс узел AVL дерево
/// @author Будаев Г.Б.#pragma once
#include "AVLTreeNode.h"
#include "../../Tree/Tree/BinarySearchTree.h"

/// Класс AVL дерева на основе AVLTreeNode с измененными методами вставки и удаления
template <class T>
class AVLTree {
private:
    AVLTreeNode<T>* root;/// корень
    AVLTreeNode<T>* curr;/// текущий узел
public:

    /// Конструктор без параметров
    AVLTree() : root(nullptr), curr(nullptr) {}

    /// <summary>
    /// Конструктор с параметром ключ
    /// </summary>
    /// <param name="data"></param>
    AVLTree(const T& data) : root(new AVLTreeNode<T>(data)), curr(nullptr) {}

    // оператор присваивания
    template <class T>
    AVLTree<T>& operator =(const AVLTree<T>& rhs)
    {
        // нельзя копировать дерево в само себя
        if (this == &rhs)
            return *this;
        // очистить текущее дерево, скопировать новое дерево в текущий объект
        this->ClearList();
        root = CopyTree(rhs->GetRoot());
        // присвоить текущему указателю значение корня и задать размер дерева
        this->SetCurr(this->root);
        //size = tree.size;
        // возвратить ссылку на текущий объект
        return *this;
    }

    /// Деструктор
    ~AVLTree() {

    };

    /// Вернуть данные
    T Data(AVLTreeNode<T>* node) const
    {
        return node->Data();
    }

    /// Установить корень
    void SetRoot(AVLTreeNode<T>* newRoot) {
        root = newRoot;
    }

    /// Установить корень
    void SetCurr(AVLTreeNode<T>* newRoot) {
        curr = newRoot;
    }

    /// Вернуть корень
    AVLTreeNode<T>* Root() const {
        return root;
    }

    /// Вставка
    void Insert(const T& key) {
        root = root->Insert(key);
    }

    /// Удаление узла
    void Remove(const T& key) {
        root = root->Remove(key);
    }

    /// Печать дерева горизонтально
    void Print() const
    {
        PrintTree(root, 0);
    }

    /// Размер
    int Size() const {
        return root->Size();
    }

    /// Поиск
    AVLTreeNode<T>* Search(const T& key) const {
        return dynamic_cast<AVLTreeNode<T>*>(root->Search(key));
    }

    /// Очищение дерева
    void Clear() {
        DeleteTree(root);
        this->SetRoot(nullptr);
    }

    /// Глубина
    int Depth() const {
        return root->Depth();
    }

    /// Найти минимальный
    AVLTreeNode<T>* FindMin() const {
        return dynamic_cast<AVLTreeNode<T>*>(root->FindMin());
    }

    ///Найти максимальный
    AVLTreeNode<T>* FindMax() const {
        return dynamic_cast<AVLTreeNode<T>*>(root->FindMax());
    }

    /// Следующий наибольший для узла
    AVLTreeNode<T>* Successor(const T& key) {
        return dynamic_cast<AVLTreeNode<T>*>(root->Successor(key));
    }

    /// Добавить в массив LNR
    void AddToArrayLNR(T arr[])const {
        int i = 0;
        root->AddToArrayLNR(arr, i);
    }

    ///// Копировать дерево
    //AVLTree<T>* CopyTree() {
    //    AVLTree<T>* copiedTree = new AVLTree<T>();
    //    copiedTree->SetRoot(dynamic_cast<AVLTreeNode<T>*>(root->CopyTree()));
    //    return copiedTree;
    //}


    /// <summary>
    /// шаблонный класс итератор в классе BinarySearchTree, как в итерируемом
    /// с порядком обхода в глубину LNR
    /// </summary>
    /// <typeparam name="T"></typeparam>
    template<class T>
    class Iterator {
    private:
        AVLTreeNode<T>* current; // Указатель на текущий узел
        std::stack<AVLTreeNode<T>*> nodeStack;  // Стек для обхода дерева

        // Заполняет стек узлами левого поддерева, начиная с заданного узла
        void FillStack(AVLTreeNode<T>* node)
        {
            // пока указатель - не пустой узел
            while (node) {
                // добавляем в стек
                nodeStack.push(node);
                // переход к левому узлу
                node = dynamic_cast<AVLTreeNode<T>*>(node->Left());
            }
        }
    public:
        /// Конструктор без параметров
        Iterator(AVLTreeNode<T>* node) : current(node)
        {
            // Заполняем стек начальным состоянием
            FillStack(dynamic_cast<AVLTreeNode<T>*>(current));
            // Если стек не пустой, получаем следующий узел из стека
            if (!nodeStack.empty()) {
                current = nodeStack.top();
                nodeStack.pop();
            }
            else
                current = nullptr;
        }

        /// Оператор разыменования
        T operator*() const {
            return current->Data();
        }

        /// Оператор префиксного инкремента
        /// *this возвращает ссылку на текущий объект итератора
        /// с обходом LNR
        Iterator<T>& operator++() {
            // Если стек пустой - выход
            if (nodeStack.empty()) {
                current = nullptr;
                return *this;
            }
            // Если стек не пустой, получаем следующий узел из стека
            current = nodeStack.top();
            nodeStack.pop();

            // Заполняем стек правым поддеревом текущего узла
            FillStack(dynamic_cast<AVLTreeNode<T>*>(current->Right()));

            return *this;
        }

        /// Оператор постфиксного инкремента
        /// temp для сохранения состояния до перехода к следующему
        /// с обходом LNR
        Iterator<T> operator++(int) {
            Iterator temp = *this;
            ++(*this);
            return temp;
        }

        /// Оператор "равно"
        bool operator==(const Iterator<T>& it) const {
            return current == it.current;
        }

        /// Оператора "не равно"
        bool operator!=(const Iterator<T>& it) const {
            return !(*this == it);
        }


    };

    /// Первый элемент списка
    Iterator<T> begin() const {
        return Iterator<T>(root);
    }

    /// Элемент, следующий за последним элементом списка
    Iterator<T> end() const {
        return Iterator<T>(nullptr);
    }
};