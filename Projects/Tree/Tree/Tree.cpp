/// Работа с деревом
/// @author Будаев Г.Б.
#include <iostream>
#include "TreeNode.h"
#include "BinarySearchTree.h"

#include <algorithm>
using namespace std;

void summ(int& i, const int value) {
    i = i + value;
}

int main()
{
    /// Создание первого дерева
    BSTree<int>* t1 = new BSTree<int>();    
    t1->Insert(10);//          10  
    t1->Insert(5);//       5        15
    t1->Insert(2);///  2     6   12
    t1->Insert(6);///
    t1->Insert(15);///           
    t1->Insert(12);///  

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


    cout << endl << endl << "t2 used iterator: " << endl;
    for (BSTree<int>::Iterator<int> it = t2->begin(); it != t2->end(); ++it) {
        int value = *it;
        cout << value << " ";
    }

    // Способ работы с итератором
    cout << endl;
    for (int x : *t1) {
        cout << x << " ";
    }

    TreeNode<int> *x = new TreeNode<int>();
    
    x->PrintNodeData();
}

