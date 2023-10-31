/// Работа с деревом
/// @author Будаев Г.Б.
#include <iostream>
#include "TreeNode.h"
#include "BinarySearchTree.h"

using namespace std;





int main()
{
    /// Создание первого дерева
    BSTree<int>* t1 = new BSTree<int>();
/*    t1->Insert(5);/// вырожденное 5    
    t1->Insert(10);///               10
    t1->Insert(20);///                   20
    t1->Insert(30);///                       30    
    t1->Insert(40);///                          40*/

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

    //t3->Remove(5);

    int* arr3 = new int[t3->Size()];
    t3->AddToArrayLNR(arr3);
    cout << "t3: ";
    for (int i = 0; i < t3->Size(); i++)
    {
        cout << arr3[i] << " ";
    }


    ///// Создание четвертого и использование apply для функции double_
    //BSTree<int>* t4 = new BSTree<int>();
    //t4 = t3;
    //apply(t4->Root(), double_);

    //int i = 0;
    //int* arr4 = new int[t4->Size()];
    //t4->AddToArrayLNR(arr4);
    //cout << endl << "t4: ";
    //for (int i = 0; i < t4->Size(); i++)
    //{
    //    cout << arr4[i] << " ";
    //}
    cout << endl << endl << "t2 used iterator: " << endl;
    for (BSTree<int>::Iterator<int> it = t2->Begin(); it != t2->End(); ++it) {
        int value = *it;
        cout << value << " ";
    }



}

