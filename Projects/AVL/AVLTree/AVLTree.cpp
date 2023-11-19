// Работа с классом ALVTree
// @author Будаев Г.Б.

#include <iostream>


#include "AVLTreeNode.h"
#include "AVLTree.h"

using namespace std;
int main()
{
    //AVLTreeNode<int>* a = nullptr;

    AVLTreeNode<int>* a = new AVLTreeNode<int>(1);

    a = a->insert(a, 8);
    a = a->insert(a, 7);
    a = a->insert(a, 6);
    a = a->insert(a, 6);
    a = a->remove(a, 1);
    a = a->remove(a, 10);

    //a->insert(a, 2);
    //a->insert(a, 11);


    cout << a->Size() << endl;
    a->PrintTree(a,0);
    //cout << a->Size();

    if (search(a, 2) != nullptr)
        cout << search(a, 2)->Data();
    else cout << "not found";


    //AVLTree<int>* b = new AVLTree<int>();
    //b->Insert(6);
    //b->Insert(5);
    //b->Insert(7);
    //b->Insert(2);
    //b->Insert(11);
    //b->PrintTree();

    //b->

    //AVLTreeNode<int>* b = new AVLTreeNode<int>();
    //b->insert(b, 5);
    //b->insert(b,3);
    //b->insert(b,1);
    ////b->Insert(-1);
    ////b->Insert(-10);
    //b->PrintTree(b,0);

}

