/// ����� AVL ������
/// @author ������ �.�.
#pragma once
#include <iostream>
#include "AVLTreeNode.h"
#include "../Tree/Tree/BinarySearchTree.h"

using namespace std;

// �������� ���������� ������������������ ����
const int leftheavy = -1;
const int balanced = 1;
const int rightheavy = 1;

// ����������� ����� ��������� ��������
template <class T>
class AVLTree : public BSTree<T>
{
private:
	// ���������� � ������ ������ ���� AVLTreeNode. �������� ���������,
	// ���� �� ����� ��������� ������ ��������� ������
	AVLTreeNode<T>* GetAVLTreeNode(const T& item, AVLTreeNode<T>* lptr, AVLTreeNode<T>* rptr)
	{
		AVLTreeNode<T>* p;
		p = new AVLTreeNode<T>(item, lptr, rptr);
		if (p == nullptr)
		{
			throw "������ ��������� ������!";
		}
		return p;
	}
	// ������������ ������������� ����������� � ���������� ������������
	AVLTreeNode<T>* CopyTree(AVLTreeNode<T>* t);
	// ������������ �������� Insert � Delete ��� ��������������
	// AVL-������� ����� �������� ���������/����������

	void SingleRotateLeft(AVLTreeNode<T>*& p)
	{
		AVLTreeNode<T>* rc;
		rc = p->Right();

		p->balanceFactor = balanced;
		rc->balanceFactor = balanced;

		p->Right() = rc->Left();
		rc->Left() = p;

		p = rc;
	}

	// ��������� ������� �� ������� ������� ������ ���� �.
	// ������� 1� ����� ������ ��������
	void SingleRotateRight(AVLTreeNode<T>*& p)
	{
		// �����, �������������� ��������� ���� �
		AVLTreeNode<T>* lc;
		// ��������� 1� ����� ����������
		lc = p->Left();
		// ��������������� ���������� ������������������ ���
		// ������������� ���� � ��� ������ ����
		p->balanceFactor = balanced;
		lc->balanceFactor = balanced;
		// ������ ��������� ���� 1� � ����� ������ ������ ���������� ������
		// �� 1�. ��������� ��� �������, ������ st ����� ���������� ���� �
		p->Left() = lc->Right();
		// ����������� � � ������ ��������� ���� 1�.
		// ������� 1� ����� ������ ��������.
		lc->Right() = p;
		p = lc;
	}

	void DoubleRotateLeft(AVLTreeNode<T>*& p)
	{
		AVLTreeNode<T>* rc, * np;
		rc = p->Right();
		np = rc->Left();

		if (np->balanceFactor == leftheavy)
		{
			p->balanceFactor = balanced;
			rc->balanceFactor = leftheavy;
		}
		else
		{
			p->balanceFactor = leftheavy;
			rc->balanceFactor = balanced;
		}
		np->balanceFactor = balanced;

		rc->Left() = np->Right();
		np->Right() = rc;
		p->Right() = np->Left();
		np->Left() = p;

		p = np;
	}

	// ������� ������� ������ ������ ���� �
	void DoubleRotateRight(AVLTreeNode<T>*& p)
	{
		// ��� ���������, ���������� ��������
		AVLTreeNode<T>* lc, *np;
		// ���� lc <= ���� np < ���� �
		lc = p->Left(); // ����� ��� ���� �
		np = lc->Right(); // ������ ��� ���� 1�
		// �������� ���������� ������������������ � ����� �, 1� � ��
		if (np->balanceFactor == rightheavy)
		{
			p->balanceFactor = balanced;
			lc->balanceFactor = rightheavy;
		}
		else
		{
			p->balanceFactor = rightheavy;
			lc->balanceFactor = balanced;
		}
		np->balanceFactor = balanced;
		// ����� ��� ��� �������� ������������ ���� �,
		// ������� ����������� ��� ������ ����� � ������������ �����
		lc->Right() = np->Left();
		np->Left() = lc;
		p->Left() = np->Right();
		np->Right() = p;
		p = np;
	}

	void UpdateLeftTree(AVLTreeNode<T>*& p,	int reviseBalanceFactor)
	{
		AVLTreeNode<T>* lc;
		lc = p->Left();
		// ������������ ����� ���������?
		if (lc->balanceFactor == leftheavy)
		{
			SingleRotateRight(p); // ����������� �������
			reviseBalanceFactor = 0;
		}
		// ������������ ������ ���������?
		else if (lc->balanceFactor == rightheavy)
		{
			// ��������� ������� �������
			DoubleRotateRight(p);
			// ������ ������ �����������
			reviseBalanceFactor = 0;
		}
	}


	void UpdateRightTree(AVLTreeNode<T>*& p, int& reviseBalanceFactor)
	{
		AVLTreeNode<T>* rc;
		rc = p->Right();

		if (rc->balanceFactor == rightheavy)
		{
			SingleRotateLeft(p);
			reviseBalanceFactor = 0;
		}
		else if (rc->balanceFactor == leftheavy)
		{
			DoubleRotateLeft(p);
			reviseBalanceFactor = 0;
		}
	}

	// ����������� ������ ������� Insert � Delete
	void AVLInsert(AVLTreeNode<T>* &tree,AVLTreeNode<T>* newNode, 
		int & reviseBalanceFactor)
	{
		// ������ "���������� ������������������ ��� �������"
		int rebalanceCurrNode;
			// ����������� ������ ���������, ���� �������� ����� ����
			if (tree == nullptr)
			{
				// �������� ����� ����
				tree = newNode;
				// �������� ����� ���� ����������������
				tree->balanceFactor = balanced;
				// �������� �� ��������� ���������� ������������������
				reviseBalanceFactor = 1;
			}
		// ���������� ���������� �� ������ ���������,
		// ���� ����� ���� ������ ��������
			else if (newNode->data < tree->data)
			{
				AVLInsert(tree->Left(), newNode, rebalanceCurrNode);
				// ���������, ����� �� �������������� balanceFactor
				if (rebalanceCurrNode)
				{
					// ��������� ����� �� ����, ��������������� �����, ����� ��������
					// ������� ������������������; ��������� ������� (������ 3)
					if (tree->balanceFactor == leftheavy)
						UpdateLeftTree(tree, reviseBalanceFactor);
					// ������� ����� �� ����������������� ����.
					// ���� ������ ������������ ����� (������ 1)
					else if (tree->balanceFactor == balanced)
					{
						tree->balanceFactor = leftheavy;
						reviseBalanceFactor = 1;
					}
					// ������� ����� �� ����, ��������������� ������.
					// ���� ������ ���������������� (������ 2)
					else
					{
						tree->balanceFactor = balanced;
						reviseBalanceFactor = 0;
					}
				}
				else
					// ���������������� �� ���������, �� ���������� ���������� ����
					reviseBalanceFactor = 0;
			}
		// ����� ���������� ���������� �� ������� ���������
			else if (newNode->data > tree->data)
			{
				AVLInsert(tree->Right(), newNode, rebalanceCurrNode);
				// ���������, ����� �� �������������� balanceFactor
				if (rebalanceCurrNode)
				{
					// ������� ������ �� ����, ��������������� ������, ����� ��������
					// ������� ������������������; ��������� ������� (������ 3)
					if (tree->balanceFactor == rightheavy)
						UpdateRightTree(tree, reviseBalanceFactor);
					// ������� ������ �� ����������������� ����.
					// ���� ������ ������������ ������ (������ 1)
					else if (tree->balanceFactor == balanced)
					{
						tree->balanceFactor = rightheavy;
						reviseBalanceFactor = 1;
					}
					// ������� ������ �� ����, ��������������� �����.
					// ���� ������ ���������������� (������ 2)
					else
					{
						tree->balanceFactor = balanced;
						reviseBalanceFactor = 0;
					}
				}
				else
					// ���������������� �� ���������, �� ���������� ���������� ����
					reviseBalanceFactor = 0;
			}
	}

	void AVLDelete(AVLTreeNode<T>* &tree, AVLTreeNode<T>* nodeToDelete, int& reviseBalanceFactor)
	{
		if (tree == nullptr)
		{
			// ���� �� ������, ������� �� ��������
			return;
		}
		else if (nodeToDelete->data < tree->data)
		{
			// ���������� ���������� �� ������ ���������
			AVLDelete(tree->Left(), nodeToDelete, reviseBalanceFactor);
			// ���������, ����� �� �������������� balanceFactor
			if (reviseBalanceFactor)
			{
				if (tree->balanceFactor == rightheavy)
				{
					// ���� �������������, ������������ ������
					tree->balanceFactor = balanced;
					reviseBalanceFactor = 0;
				}
				else if (tree->balanceFactor == balanced)
				{
					// ���� ������������ �����
					tree->balanceFactor = leftheavy;
					// ����� ���������� ������������� ����������� ������������������ ����
					reviseBalanceFactor = 1;
				}
				else
				{
					// ���� ��� ������������ �����, ��������� ��������
					UpdateLeftTree(tree, reviseBalanceFactor);
				}
			}
		}
		else if (nodeToDelete->data > tree->data)
		{
			// ���������� ���������� �� ������� ���������
			AVLDelete(tree->Right(), nodeToDelete, reviseBalanceFactor);
			// ���������, ����� �� �������������� balanceFactor
			if (reviseBalanceFactor)
			{
				if (tree->balanceFactor == leftheavy)
				{
					// ���� �������������, ������������ �����
					tree->balanceFactor = balanced;
					reviseBalanceFactor = 0;
				}
				else if (tree->balanceFactor == balanced)
				{
					// ���� ������������ ������
					tree->balanceFactor = rightheavy;
					// ����� ���������� ������������� ����������� ������������������ ����
					reviseBalanceFactor = 1;
				}
				else
				{
					// ���� ��� ������������ ������, ��������� ��������
					UpdateRightTree(tree, reviseBalanceFactor);
				}
			}
		}
		else
		{
			// ������ ���� ��� ��������
			if (tree->Left() == nullptr && tree->Right() == nullptr)
			{
				// ���� �������� ������, ������ ������� ���
				delete tree;
				tree = nullptr;
				reviseBalanceFactor = 1;
			}
			else if (tree->Left() == nullptr)
			{
				// ���� ����� ������ ������ ���������
				AVLTreeNode<T>* temp = tree;
				tree = tree->Right();
				delete temp;
				reviseBalanceFactor = 1;
			}
			else if (tree->Right() == nullptr)
			{
				// ���� ����� ������ ����� ���������
				AVLTreeNode<T>* temp = tree;
				tree = tree->Left();
				delete temp;
				reviseBalanceFactor = 1;
			}
			else
			{
				// ���� ����� ��� ���������
				AVLTreeNode<T>* successor = Successor(tree);
				tree->data = successor->data;
				AVLDelete(tree->Right(), successor, reviseBalanceFactor);
				if (reviseBalanceFactor)
				{
					if (tree->balanceFactor == leftheavy)
					{
						tree->balanceFactor = balanced;
						reviseBalanceFactor = 0;
					}
					else if (tree->balanceFactor == balanced)
					{
						tree->balanceFactor = rightheavy;
						reviseBalanceFactor = 1;
					}
					else
					{
						UpdateRightTree(tree, reviseBalanceFactor);
					}
				}
			}
		}
	}

	void Insert(const T& key) override
	{
		// �������� ��������� AVL-������, ��������� �����
		// �������� ������ GetRoot.
		// ���������� ���������� ����� ��� ����������
		AVLTreeNode<T>* treeRoot = static_cast<AVLTreeNode<T>*>(this->Root()), * newNode;
		// ������, ������������ �������� AVLInsert ��� ���������������� �����
		int reviseBalanceFactor = 0;
		// ������� ����� ���� AVL-������ � �������� ������ ����������
		newNode = GetAVLTreeNode(key, nullptr, nullptr);
		// ������� ����������� ��������� ��� ����������� ����a��� ��������
		AVLInsert(treeRoot, newNode, reviseBalanceFactor);
		// ��������� ����� �������� ��������� ������ �������� ������
		this->SetRoot(treeRoot);
		this->SetCurr(newNode);
		this->size++;
	}

	void Delete(const T& key) override
	{
		AVLTreeNode<T>* nodeToDelete = this->Search(key);
		if (nodeToDelete != nullptr)
		{
			int reviseBalanceFactor = 0;
			AVLDelete(this, nodeToDelete, reviseBalanceFactor);
			this->size--;
		}
	}
};


