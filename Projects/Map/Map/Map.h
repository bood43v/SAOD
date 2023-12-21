/// ����� Map - ������� �� ������ AVL ������
/// @author ������ �.�.
#pragma once
#include "../AVL/AVLTree.h"
#include "KeyValue.h"

/// <summary>
/// ����� ������� �� ��������� �� ��������� defaultValue, ������� ������� ��� �������� ������� � ������������
/// </summary>
/// <typeparam name="T"></typeparam>
/// <typeparam name="K"></typeparam>
template <class K, class T>
class Map : public AVLTree<KeyValue<K, T>>
{
private:
    T defaultValue; /// �������� �� ���������

public:
    /// <summary>
    /// �����������
    /// </summary>
    /// <param name="defaultval"></param>
    Map(const T& defaultValue) : AVLTree<KeyValue<K,T>>(), defaultValue(defaultValue) {}

    /// �������� ��������������
    /// ��������� ����. 
    /// "�����" - ���� �������� � ����� ������ ���, �� ����������� ���� ����/�������� �� ���������
    T& operator[](const K& index)
    {
        // ���������� ������� ������ ���� KeyValue, ����������
        // ������ ���������� �� ���������
        KeyValue<K, T> targetKey(index, defaultValue);
        // ������ ����, ���� �� ������, �������� targetKey
        if (this->Search(targetKey) == nullptr) {
            this->Insert(targetKey);
        }
            
        /*this->SetCurr(this->Search(targetKey));*/
        // ���������� ������ �� ��������� ��� ����������� ������
        return this->Search(targetKey)->DataRef().GetValue();
    }

    /// <summary>
    /// ��������, ��������� �� � ������� ��������
    /// </summary>
    /// <param name="keyval"></param>
    /// <returns></returns>
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

    /// <summary>
    /// �������� ����� �� �������
    /// </summary>
    /// <param name="keyval"></param>
    void DeleteKey(const K& keyval)
    {
        KeyValue<K, T> tmp(keyval, defaultValue);
        this->Remove(tmp);
    }



    
};