/// ����� ���� AVL ������
/// @author ������ �.�.
#pragma once
#include "../../Tree/Tree/TreeNode.h"

/// <summary>
/// ����� ���� AVL ������
/// ����������� �� TreeNode
/// </summary>
template <class T>
class AVLTreeNode : public TreeNode<T> {

private:
	unsigned char height; // "������" ����

	/// �������� ���� � ����������� ������ �� ������ � ������ p
	AVLTreeNode<T>* RemoveMin(AVLTreeNode<T>* p)
	{
		if (p->Left() == 0)
			return dynamic_cast<AVLTreeNode<T>*>(p->Right());
		p->SetLeft(RemoveMin(dynamic_cast<AVLTreeNode<T>*>(p->Left())));
		return Balance(p);
	}

	/// �������� ������ ��� ����
	unsigned char GetHeight(AVLTreeNode<T>* p)
	{
		return p ? p->height : 0;
		//if (p == nullptr) return 0;
		//else return p->height;
	}

	/// <summary>
	/// ���������� balance factor ��������� ���� 
	/// </summary>
	/// <param name="p"></param>
	/// <returns></returns>
	int bFactor(AVLTreeNode<T>* p)
	{
		return GetHeight(dynamic_cast<AVLTreeNode<T>*>(p->Right())) -
			GetHeight(dynamic_cast<AVLTreeNode<T>*>(p->Left()));
	}

	/// <summary>
	/// ��������������� ���������� �������� ���� height ��������� ����
	/// </summary>
	/// <param name="p"></param>
	/// <returns></returns>
	void FixHeight(AVLTreeNode<T>* p)
	{
		unsigned char hl = GetHeight(dynamic_cast<AVLTreeNode<T>*>(p->Left()));
		unsigned char hr = GetHeight(dynamic_cast<AVLTreeNode<T>*>(p->Right()));
		p->height = (hl > hr ? hl : hr) + 1;
	}

	/// <summary>
	/// ������ ������� ������ p
	/// </summary>
	/// <param name="q"></param>
	/// <returns></returns>
	AVLTreeNode<T>* RotateRight(AVLTreeNode<T>* p) 
	{
		AVLTreeNode<T>* q = dynamic_cast<AVLTreeNode<T>*>(p->Left());
		p->SetLeft(q->Right());
		q->SetRight(p);
		FixHeight(p);
		FixHeight(q);
		return q;
	}

	/// <summary>
	/// ����� ������� ������ p
	/// </summary>
	/// <param name="q"></param>
	/// <returns></returns>
	AVLTreeNode<T>* RotateLeft(AVLTreeNode<T>* q) // ����� ������� ������ q
	{
		AVLTreeNode<T>* p = dynamic_cast<AVLTreeNode<T>*>(q->Right());
		q->SetRight(p->Left());
		p->SetLeft(q);
		FixHeight(q);
		FixHeight(p);
		return p;
	}

	/// <summary>
	/// ������������ ���� p
	/// �������� 1 ��� 2 �������� � ����������� �� "������" ����
	/// </summary>
	AVLTreeNode<T>* Balance(AVLTreeNode<T>* p) 
	{
		FixHeight(p);
		if (bFactor(p) == 2)
		{
			if (bFactor(dynamic_cast<AVLTreeNode<T>*>(p->Right())) < 0)
				p->SetRight(RotateRight(dynamic_cast<AVLTreeNode<T>*>(p->Right())));
			return RotateLeft(p);
		}
		if (bFactor(p) == -2)
		{
			if (bFactor(dynamic_cast<AVLTreeNode<T>*>(p->Left())) > 0)
				p->SetLeft(RotateLeft(dynamic_cast<AVLTreeNode<T>*>(p->Left())));
			return RotateRight(p);
		}
		return p; // ������������ �� �����
	}

public:
	/// <summary>
	/// ����������� � ���������� ����
	/// </summary>
	/// <param name="k"></param>
	/// <returns></returns>
	AVLTreeNode(T k) : TreeNode<T>(k, nullptr, nullptr), height(1) {}

	/// ����������� ��� ����������
	//AVLTreeNode() : TreeNode<T>(), height(1){}

	/// ����������
	~AVLTreeNode() {
		DeleteTree(this);
	}

	/// ����������� �����������
	AVLTreeNode(const AVLTreeNode<T>& node) : TreeNode<T>(node), height(node->GetHeight()) {
		if (node->Left()) {
			this->SetLeft(new AVLTreeNode<T>(dynamic_cast<AVLTreeNode<T>*>(node.Left())));
		}
		if (node->Right()) {
			this->SetRight(new AVLTreeNode<T>(dynamic_cast<AVLTreeNode<T>*>(node.Right())));
		}
	}

	// ����������� �����������



	/// ������������� ����� �������
	/// ����� k � ������ � ������ p
	AVLTreeNode<T>* Insert(T k) 
	{
		AVLTreeNode<T>* p = this;
		if (!p) return new AVLTreeNode<T>(k);
		//if (this->Data() == NULL) {
		//	this->SetData(k);
		//	return balance(p);
		//}
		//else
		if (k < p->Data())
			p->SetLeft(dynamic_cast<AVLTreeNode<T>*>(p->Left())->Insert(k));
		else
			p->SetRight(dynamic_cast<AVLTreeNode<T>*>(p->Right())->Insert(k));
		return Balance(p);
	}

	/// ������������� ����� ��������
	/// ����� k � ������ � ������ p
	AVLTreeNode<T>* Remove(T k) // �������� ����� k �� ������ p
	{
		AVLTreeNode<T>* p = this;
		if (!p) return nullptr;
		if (k < p->Data())
			p->SetLeft(dynamic_cast<AVLTreeNode<T>*>(p->Left())->Remove(k));
		else if (k > p->Data())
			p->SetRight(dynamic_cast<AVLTreeNode<T>*>(p->Right())->Remove(k));
		else //  k == p->key 
		{
			AVLTreeNode<T>* q = dynamic_cast<AVLTreeNode<T>*>(p->Left());
			AVLTreeNode<T>* r = dynamic_cast<AVLTreeNode<T>*>(p->Right());
			delete p;
			if (!r) return q;
			//AVLTreeNode<T>* min = dynamic_cast<AVLTreeNode<T>*>(r->FindMin());
			AVLTreeNode<T>* min = dynamic_cast<AVLTreeNode<T>*>(r->FindMin());
			min->SetRight(RemoveMin(r));
			min->SetLeft(q);
			FixHeight(min);
			return Balance(min);
		}
		FixHeight(p);
		return Balance(p);
	}

	
};


/// ���������� ����� �������� (��� ������)
const int indentBlock = 6;

/// <summary>
/// ������� ������ ������ �������������
/// </summary>
/// <param name="p"></param>
/// <param name="k"></param>
/// <returns></returns>
template <class T>
void PrintTree(AVLTreeNode<T>* node, int level = 0)
{
	// �������� ������ ������ ���� node, ���� �� �� ����� nullptr
	if (node != nullptr)
	{
		// �������� ������ ��������� ���� node
		PrintTree(dynamic_cast<AVLTreeNode<T>*>(node->Right()), level + 1);
		// ��������� ������� ������� � ������� ���� ������
		for (int i = 0; i < level * 6; i++)
			std::cout << "  ";
		std::cout << node->Data() << std::endl;
		// �������� ����� ��������� ���� node
		PrintTree(dynamic_cast<AVLTreeNode<T>*>(node->Left()), level + 1);
	}
}