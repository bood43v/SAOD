/// Класс узел AVL дерева
/// @author Будаев Г.Б.
#pragma once
#include <iostream>
#include "../Tree/Tree/TreeNode.h"
//#include "AVLTree.h"
template <class T>
class AVLTreeNode : public TreeNode<T>
{
private:
    int balanceFactor;


    AVLTreeNode<T>*& Left(void)
    {
        return static_cast<AVLTreeNode<T>*&>(this->left);
    }
    AVLTreeNode<T>*& Right(void)
    {
        return static_cast<AVLTreeNode<T>*&>(this->right);
    }

public:
    AVLTreeNode(const T& item, AVLTreeNode<T>* lptr = nullptr, AVLTreeNode<T>* rptr = nullptr, int balfac = 0)
        : TreeNode<T>(item, lptr, rptr), balanceFactor(balfac) {}


    int GetBalanceFactor(void)
    {
        return balanceFactor;
    }

    //friend class AVLTree;
};




