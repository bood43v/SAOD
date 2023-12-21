// Работа с классом ALVTree
// @author Будаев Г.Б.

#include <iostream>


#include "AVLTreeNode.h"
#include "AVLTree.h"

using namespace std;
int main()
{
    //AVLTreeNode<int>* a = new AVLTreeNode<int>(1);

    //a = a->Insert(2);
    //a = a->Insert(3);
    //a = a->Insert(4);
    //a = a->Insert(5);
    //a->Insert(10);
    ////a = a->Remove(8);

    //PrintTree(a);


    AVLTree<int>* b = new AVLTree<int>(1);

    b->Insert(8);
    b->Insert(7);
    b->Insert(6);
    b->Insert(10);
    b->Remove(8);

    b->Print();

    if(b->Search(4) == nullptr)
        cout <<"nullptr";

}

