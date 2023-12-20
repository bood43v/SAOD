#include "../AVL/AVLTree.h"
#include "KeyValue.h"
template <class K, class T>
class Map : public AVLTree<KeyValue<K, T>>
{
private:
    T defaultValue;

public:
    Map(const T& defaultval) : AVLTree<KeyValue<K,T>>(), defaultValue(defaultval) {}

T& operator[](const K& index)
{
    // ���������� ������� ������ ���� KeyValue, ���������� ������ ���������� �� ���������
    KeyValue<K, T> targetKey(index, defaultValue);

    // ������ ����, ���� �� ������, �������� targetKey
    if (this->Search(targetKey) == nullptr)
    {
        // �������� targetKey � �������� ������ ������
        AVLTree<KeyValue<K, T>>* newRootTree = dynamic_cast<AVLTree<KeyValue<K, T>>*>(this->Root()->Insert(targetKey));
        if (newRootTree != nullptr)
        {
            AVLTreeNode<KeyValue<K, T>>* newRoot = newRootTree->Root();
            if (newRoot != nullptr)
                this->SetRoot(newRoot);
        }
    }

    // ������� ������ �� ��������� ��� ����������� ������
    return this->Search(targetKey)->Data().GetValue();
}

    int InDictionary(const K& keyval)
    {
        // ���������� ������� ������ ���� KeyValue, ����������
        // ������ ���������� �� ���������
        KeyValue<K, T> tmp(keyval, defaultValue);
        int retval = 1;
        // ������ tmp �� ������, ������� ���������
        if (!this->Search(tmp))
            retval = 0;
        return retval;
    }

    void DeleteKey(const K& keyval)
    {
        KeyValue<K, T> tmp(keyval, defaultValue);
        this->Remove(tmp);
    }
};