/// ����� ���� AVL ������
/// @author ������ �.�.
#pragma once
#include <iostream>
#include "../Tree/Tree/TreeNode.h"

template <class T>
class AVLTreeNode : public TreeNode<T>
{
private:
	int balanceFactor;

	AVLTreeNode<T>*& Left();
	AVLTreeNode<T>*& Right();

public:

};
