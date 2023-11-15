/// Класс AVL дерево
/// @author Будаев Г.Б.
#pragma once
#include <iostream>
#include "AVLTreeNode.h"
#include "../Tree/Tree/BinarySearchTree.h"

using namespace std;

// Значения показателя сбалансированности узла
const int leftheavy = -1;
const int balanced = 1;
const int rightheavy = 1;

// производный класс поисковых деревьев
template <class T>
class AVLTree : public BSTree<T>
{
private:
	// разместить в памяти объект типа AVLTreeNode. прервать программу,
	// если во время выделения памяти произошла ошибка
	AVLTreeNode<T>* GetAVLTreeNode(const T& item, AVLTreeNode<T>* lptr, AVLTreeNode<T>* rptr)
	{
		AVLTreeNode<T>* p;
		p = new AVLTreeNode<T>(item, lptr, rptr);
		if (p == nullptr)
		{
			throw "Ошибка выделения памяти!";
		}
		return p;
	}
	// используется конструктором копирования и оператором присваивания
	AVLTreeNode<T>* CopyTree(AVLTreeNode<T>* t);
	// используется методами Insert и Delete для восстановления
	// AVL-условий после операций включения/исключения

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

	// выполнить поворот по часовой стрелке вокруг узла р.
	// сделать 1с новой точкой вращения
	void SingleRotateRight(AVLTreeNode<T>*& p)
	{
		// левое, перевешивающее поддерево узла р
		AVLTreeNode<T>* lc;
		// назначить 1с левым поддеревом
		lc = p->Left();
		// скорректировать показатель сбалансированности для
		// родительского узла и его левого сына
		p->balanceFactor = balanced;
		lc->balanceFactor = balanced;
		// правое поддерево узла 1с в любом случае должно оставаться справа
		// от 1с. выполнить это условие, сделав st левым поддеревом узла р
		p->Left() = lc->Right();
		// переместить р в правое поддерево узла 1с.
		// сделать 1с новой точкой вращения.
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

	// двойной поворот вправо вокруг узла р
	void DoubleRotateRight(AVLTreeNode<T>*& p)
	{
		// два поддерева, подлежащих повороту
		AVLTreeNode<T>* lc, *np;
		// узел lc <= узел np < узел р
		lc = p->Left(); // левый сын узла р
		np = lc->Right(); // правый сын узла 1с
		// обновить показатели сбалансированности в узлах р, 1с и пр
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
		// перед тем как заменить родительский узел р,
		// следует отсоединить его старых детей и присоединить новых
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
		// перевешивает левое поддерево?
		if (lc->balanceFactor == leftheavy)
		{
			SingleRotateRight(p); // однократный поворот
			reviseBalanceFactor = 0;
		}
		// перевешивает правое поддерево?
		else if (lc->balanceFactor == rightheavy)
		{
			// выполнить двойной поворот
			DoubleRotateRight(p);
			// теперь корень уравновешен
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

	// специальные версии методов Insert и Delete
	void AVLInsert(AVLTreeNode<T>* &tree,AVLTreeNode<T>* newNode, 
		int & reviseBalanceFactor)
	{
		// флажок "Показатель сбалансированности был изменен"
		int rebalanceCurrNode;
			// встретилось пустое поддерево, пора включать новый узел
			if (tree == nullptr)
			{
				// вставить новый узел
				tree = newNode;
				// объявить новый узел сбалансированным
				tree->balanceFactor = balanced;
				// сообщить об изменении показателя сбалансированности
				reviseBalanceFactor = 1;
			}
		// рекурсивно спускаться по левому поддереву,
		// если новый узел меньше текущего
			else if (newNode->data < tree->data)
			{
				AVLInsert(tree->Left(), newNode, rebalanceCurrNode);
				// проверить, нужно ли корректировать balanceFactor
				if (rebalanceCurrNode)
				{
					// включение слева от узла, перевешивающего влево, будет нарушено
					// условие сбалансированности; выполнить поворот (случай 3)
					if (tree->balanceFactor == leftheavy)
						UpdateLeftTree(tree, reviseBalanceFactor);
					// вставка слева от сбалансированного узла.
					// узел станет перевешивать влево (случай 1)
					else if (tree->balanceFactor == balanced)
					{
						tree->balanceFactor = leftheavy;
						reviseBalanceFactor = 1;
					}
					// вставка слева от узла, перевешивающего вправо.
					// узел станет сбалансированным (случай 2)
					else
					{
						tree->balanceFactor = balanced;
						reviseBalanceFactor = 0;
					}
				}
				else
					// перебалансировка не требуется, не опрашивать предыдущие узлы
					reviseBalanceFactor = 0;
			}
		// иначе рекурсивно спускаться по правому поддереву
			else if (newNode->data > tree->data)
			{
				AVLInsert(tree->Right(), newNode, rebalanceCurrNode);
				// проверить, нужно ли корректировать balanceFactor
				if (rebalanceCurrNode)
				{
					// вставка справа от узла, перевешивающего вправо, будет нарушено
					// условие сбалансированности; выполнить поворот (случай 3)
					if (tree->balanceFactor == rightheavy)
						UpdateRightTree(tree, reviseBalanceFactor);
					// вставка справа от сбалансированного узла.
					// узел станет перевешивать вправо (случай 1)
					else if (tree->balanceFactor == balanced)
					{
						tree->balanceFactor = rightheavy;
						reviseBalanceFactor = 1;
					}
					// вставка справа от узла, перевешивающего влево.
					// узел станет сбалансированным (случай 2)
					else
					{
						tree->balanceFactor = balanced;
						reviseBalanceFactor = 0;
					}
				}
				else
					// перебалансировка не требуется, не опрашивать предыдущие узлы
					reviseBalanceFactor = 0;
			}
	}

	void AVLDelete(AVLTreeNode<T>* &tree, AVLTreeNode<T>* nodeToDelete, int& reviseBalanceFactor)
	{
		if (tree == nullptr)
		{
			// Узел не найден, выходим из рекурсии
			return;
		}
		else if (nodeToDelete->data < tree->data)
		{
			// Рекурсивно спускаемся по левому поддереву
			AVLDelete(tree->Left(), nodeToDelete, reviseBalanceFactor);
			// Проверяем, нужно ли корректировать balanceFactor
			if (reviseBalanceFactor)
			{
				if (tree->balanceFactor == rightheavy)
				{
					// Узел сбалансирован, перевешивает вправо
					tree->balanceFactor = balanced;
					reviseBalanceFactor = 0;
				}
				else if (tree->balanceFactor == balanced)
				{
					// Узел перевешивает влево
					tree->balanceFactor = leftheavy;
					// Нужно продолжить корректировку показателей сбалансированности выше
					reviseBalanceFactor = 1;
				}
				else
				{
					// Узел уже перевешивает влево, выполняем повороты
					UpdateLeftTree(tree, reviseBalanceFactor);
				}
			}
		}
		else if (nodeToDelete->data > tree->data)
		{
			// Рекурсивно спускаемся по правому поддереву
			AVLDelete(tree->Right(), nodeToDelete, reviseBalanceFactor);
			// Проверяем, нужно ли корректировать balanceFactor
			if (reviseBalanceFactor)
			{
				if (tree->balanceFactor == leftheavy)
				{
					// Узел сбалансирован, перевешивает влево
					tree->balanceFactor = balanced;
					reviseBalanceFactor = 0;
				}
				else if (tree->balanceFactor == balanced)
				{
					// Узел перевешивает вправо
					tree->balanceFactor = rightheavy;
					// Нужно продолжить корректировку показателей сбалансированности выше
					reviseBalanceFactor = 1;
				}
				else
				{
					// Узел уже перевешивает вправо, выполняем повороты
					UpdateRightTree(tree, reviseBalanceFactor);
				}
			}
		}
		else
		{
			// Найден узел для удаления
			if (tree->Left() == nullptr && tree->Right() == nullptr)
			{
				// Узел является листом, просто удаляем его
				delete tree;
				tree = nullptr;
				reviseBalanceFactor = 1;
			}
			else if (tree->Left() == nullptr)
			{
				// Узел имеет только правое поддерево
				AVLTreeNode<T>* temp = tree;
				tree = tree->Right();
				delete temp;
				reviseBalanceFactor = 1;
			}
			else if (tree->Right() == nullptr)
			{
				// Узел имеет только левое поддерево
				AVLTreeNode<T>* temp = tree;
				tree = tree->Left();
				delete temp;
				reviseBalanceFactor = 1;
			}
			else
			{
				// Узел имеет оба поддерева
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
		// объявить указатель AVL-дерева, используя метод
		// базового класса GetRoot.
		// произвести приведение типов для указателей
		AVLTreeNode<T>* treeRoot = static_cast<AVLTreeNode<T>*>(this->Root()), * newNode;
		// флажок, используемый функцией AVLInsert для перебалансировки узлов
		int reviseBalanceFactor = 0;
		// создать новый узел AVL-дерева с нулевыми полями указателей
		newNode = GetAVLTreeNode(key, nullptr, nullptr);
		// вызвать рекурсивную процедуру для фактической встаaвки элемента
		AVLInsert(treeRoot, newNode, reviseBalanceFactor);
		// присвоить новые значения элементам данных базового класса
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


