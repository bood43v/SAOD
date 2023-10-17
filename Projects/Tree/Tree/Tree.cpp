/// Работа с деревом
/// @author Будаев Г.Б.
#include <iostream>
#include "TreeNode.h"
#include "BinarySearchTree.h"

using namespace std;
/// Удаление дерева
template<typename T>
void DeleteTree(TreeNode<T>* root) {
    if (root) {
        DeleteTree(root->Left());
        DeleteTree(root->Right());
        root = nullptr;
        delete root;
    }
    //if (root == nullptr)
    //    return;

    //if (root->Left() != nullptr)
    //    DeleteTree(root->Left());

    //if (root->Right() != nullptr)
    //    DeleteTree(root->Right());

    //delete root;
    //root = nullptr;
}

// Функция для обхода дерева и применения функции к каждому элементу
template<typename T>
void apply(TreeNode<T>* root, T(*func)(T)) {
    if (root != nullptr) {
        // Применяем функцию к текущему элементу
        root->SetData(func(root->Data()));
        // Рекурсивно обходим левое и правое поддеревья
        apply(root->Left(), func);
        apply(root->Right(), func);
    }
}
// Функция для возведения числа в квадрат
template<typename T>
T double_(T x) {
    return 2*x;
}


int main()
{
    /// Создание первого дерева
    BSTree<int>* t1 = new BSTree<int>();
    t1->Insert(5);
    t1->Insert(2);
    t1->Insert(3);
    t1->Insert(4);

    /// Создание второго конструктором копирования
    BSTree<int>* t2 = t1;
    int* arr2 = new int[t2->Size()];
    t2->AddToArrayLNR(arr2);

    cout << "t2: ";
    for (int i = 0; i < t2->Size(); i++)
    {
        cout << arr2[i] << " ";
    }
    cout << endl;

    /// Создание третьего и использования оператора присваивания
    BSTree<int>* t3;
    t3 = t2;

    int* arr3 = new int[t3->Size()];
    t3->AddToArrayLNR(arr3);
    cout << "t3: ";
    for (int i = 0; i < t3->Size(); i++)
    {
        cout << arr3[i] << " ";
    }

    /// Создание четвертого и использование apply для функции double_
    BSTree<int>* t4 = new BSTree<int>();
    t4 = t3;
    apply(t4->Root(), double_);

    int i = 0;
    int* arr4 = new int[t4->Size()];
    t4->AddToArrayLNR(arr4);
    cout << endl << "t4: ";
    for (int i = 0; i < t4->Size(); i++)
    {
        cout << arr4[i] << " ";
    }
}

