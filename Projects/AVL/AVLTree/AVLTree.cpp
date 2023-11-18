// Работа с классом ALVTree
// @author Будаев Г.Б.

#include <iostream>


#include "AVLTreeNode.h"
#include "AVLTree.h"

using namespace std;
int main()
{
    //AVLTreeNode<int>* a = new AVLTreeNode<int>();
    //AVLTreeNode<int>* a = nullptr;
    //a = a->insert(a, 6);
    //a = a->insert(a, 5);
    //a = a->insert(a, 7);
    //a = a->insert(a, 2);
    //a = a->insert(a, 11);

    //a->PrintTree(a,0);


    AVLTree<int>* b = new AVLTree<int>();
    b->Insert(6);
    b->Insert(5);
    b->Insert(7);
    b->Insert(2);
    b->Insert(11);
    b->PrintTree();


    //AVLTreeNode<int>* b = new AVLTreeNode<int>();
    //b->insert(b, 5);
    //b->insert(b,3);
    //b->insert(b,1);
    ////b->Insert(-1);
    ////b->Insert(-10);
    //b->PrintTree(b,0);

}

