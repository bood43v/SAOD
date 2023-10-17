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

int main()
{
    BSTree<int>* t1 = new BSTree<int>();
    t1->Insert(5);
    t1->Insert(2);
    t1->Insert(3);
    t1->Insert(4);

    BSTree<int>* t2 = t1;
    int* arr2 = new int();
    t2->AddToArrayLNR(arr2);

    cout << "t2: ";
    for (int i = 0; i < t2->Size(); i++)
    {
        cout << arr2[i] << " ";
    }
    cout << endl;

    BSTree<int>* t3;
    t3 = t2;

    int* arr3 = new int();
    t3->AddToArrayLNR(arr3);
    cout << "t3: ";
    for (int i = 0; i < t3->Size(); i++)
    {
        cout << arr3[i] << " ";
    }

    TreeNode<int>* t4 = new TreeNode<int>();
    t4->Insert(5);
    t4->Insert(2);
    t4->Insert(3);
    t4->apply(square);
}

