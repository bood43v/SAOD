#pragma once
#include "../../Tree/Tree/TreeNode.h"

template <class T>
class AVLTreeNode : public TreeNode<T> {
private:

	unsigned char height;

	//
	AVLTreeNode<T>* findmin(AVLTreeNode<T>* p) // ����� ���� � ����������� ������ � ������ p 
	{
		return p->Left() ? findmin(dynamic_cast<AVLTreeNode<T>*>(p->Left())) : p;
	}

	AVLTreeNode<T>* removemin(AVLTreeNode<T>* p) // �������� ���� � ����������� ������ �� ������ p
	{
		if (p->Left() == 0)
			return dynamic_cast<AVLTreeNode<T>*>(p->Right());
		p->SetLeft(removemin(dynamic_cast<AVLTreeNode<T>*>(p->Left())));
		return balance(p);
	}

	unsigned char getHeight(AVLTreeNode<T>* p)
	{
		return p ? p->height : 0;
		//if (p == nullptr) return 0;
		//else return p->height;
	}

	int bFactor(AVLTreeNode<T>* p)
	{
		return getHeight(dynamic_cast<AVLTreeNode<T>*>(p->Right())) -
			getHeight(dynamic_cast<AVLTreeNode<T>*>(p->Left()));
	}

	void fixHeight(AVLTreeNode<T>* p)
	{
		unsigned char hl = getHeight(dynamic_cast<AVLTreeNode<T>*>(p->Left()));
		unsigned char hr = getHeight(dynamic_cast<AVLTreeNode<T>*>(p->Right()));
		p->height = (hl > hr ? hl : hr) + 1;
	}

	AVLTreeNode<T>* rotateRight(AVLTreeNode<T>* p) // ������ ������� ������ p
	{
		AVLTreeNode<T>* q = dynamic_cast<AVLTreeNode<T>*>(p->Left());
		p->SetLeft(q->Right());
		q->SetRight(p);
		fixHeight(p);
		fixHeight(q);
		return q;
	}

	AVLTreeNode<T>* rotateLeft(AVLTreeNode<T>* q) // ����� ������� ������ q
	{
		AVLTreeNode<T>* p = dynamic_cast<AVLTreeNode<T>*>(q->Right());
		q->SetRight(p->Left());
		p->SetLeft(q);
		fixHeight(q);
		fixHeight(p);
		return p;
	}

	AVLTreeNode<T>* balance(AVLTreeNode<T>* p) // ������������ ���� p
	{
		fixHeight(p);
		if (bFactor(p) == 2)
		{
			if (bFactor(dynamic_cast<AVLTreeNode<T>*>(p->Right())) < 0)
				p->SetRight(rotateRight(dynamic_cast<AVLTreeNode<T>*>(p->Right())));
			return rotateLeft(p);
		}
		if (bFactor(p) == -2)
		{
			if (bFactor(dynamic_cast<AVLTreeNode<T>*>(p->Left())) > 0)
				p->SetLeft(rotateLeft(dynamic_cast<AVLTreeNode<T>*>(p->Left())));
			return rotateRight(p);
		}
		return p; // ������������ �� �����
	}
public:

	AVLTreeNode(T k) : TreeNode<T>(k, nullptr, nullptr), height(1) {}

	//// ����������� ��� ����������
	//AVLTreeNode() : TreeNode<T>(), height(0){}

	~AVLTreeNode() {}

	// ���������� ����� ��������
	const int indentBlock = 6;

	//����������� ����������
	
	// �������� num�������� � ������� ������
	void IndentBlanks(int num)
	{
		for (int i = 0; i < num; i++)
			std::cout << "  ";
	}

	void PrintTree(AVLTreeNode<T>* node, int level)
	{
		// �������� ������ ������ ���� node, ���� �� �� ����� nullptr
		if (node != nullptr)
		{
			// �������� ������ ��������� ���� node
			PrintTree(dynamic_cast<AVLTreeNode<T>*>(node->Right()), level + 1);
			// ��������� ������� ������� � ������� ���� ������
			IndentBlanks(indentBlock * level);
			std::cout << node->Data() << std::endl;
			// �������� ����� ��������� ���� node
			PrintTree(dynamic_cast<AVLTreeNode<T>*>(node->Left()), level + 1);
		}
	}

	AVLTreeNode<T>* insert(AVLTreeNode<T>* p, T k) // ������� ����� k � ������ � ������ p
	{
		if (!p) return new AVLTreeNode<T>(k);
		//if (this->Data() == NULL) {
		//	this->SetData(k);
		//	return balance(p);
		//}
		//else
		if (k < p->Data())
			p->SetLeft(insert(dynamic_cast<AVLTreeNode<T>*>(p->Left()), k));
		else
			p->SetRight(insert(dynamic_cast<AVLTreeNode<T>*>(p->Right()), k));
		return balance(p);
	}




	AVLTreeNode<T>* remove(AVLTreeNode<T>* p, T k) // �������� ����� k �� ������ p
	{
		if (!p) return nullptr;
		if (k < p->Data())
			p->SetLeft(remove(dynamic_cast<AVLTreeNode<T>*>(p->Left()), k));
		else if (k > p->Data())
			p->SetRight(remove(dynamic_cast<AVLTreeNode<T>*>(p->Right()), k));
		else //  k == p->key 
		{
			AVLTreeNode<T>* q = dynamic_cast<AVLTreeNode<T>*>(p->Left());
			AVLTreeNode<T>* r = dynamic_cast<AVLTreeNode<T>*>(p->Right());
			delete p;
			if (!r) return q;
			//AVLTreeNode<T>* min = dynamic_cast<AVLTreeNode<T>*>(r->FindMin());
			AVLTreeNode<T>* min = findmin(r);
			min->SetRight(removemin(r));
			min->SetLeft(q);
			fixHeight(min);
			return balance(min);
		}
		fixHeight(p);
		return balance(p);
	}



	void PrintNode() {
		this->TreeNode<T>::PrintNodeData();
	}

};
template <class T>
AVLTreeNode<T>* search(AVLTreeNode<T>* root, T k) {
	return dynamic_cast<AVLTreeNode<T>*>(root->Search(k));
}
