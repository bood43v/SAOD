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

    /// ����������. ���������� �������������� Clear
    ~Map()
    {
        this->Clear();
    }

    // ����������� �����������
    //Map(Map<K,T>& map_moved)
    //{
    //    defaultValue = map_moved.defaultValue;

    //    map_moved->Clear();
    //}
    
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
    /// ��������, ��������� �� � ������� ��������. ���� ��� - ������� 0
    /// </summary>
    /// <param name="keyval"></param>
    /// <returns></returns>
    bool InDictionary(const K& keyval) const
    {
        // ���������� ������� ������ ���� KeyValue, ����������
        // ������ ���������� �� ���������
        KeyValue<K, T> tmp(keyval, defaultValue);
        // ������ tmp �� ������, ������� ���������
        if (!this->Search(tmp))
            return false;
        return true;
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

    /// void Clear(); - �����������

    /// int Size(); - �����������
    





    //template<class K, class T>
    //class MapIterator {
    //private:
    //    typename AVLTree<KeyValue<K, T>>::template Iterator<KeyValue<K, T>> iterator;

    //public:
    //    MapIterator(typename AVLTree<KeyValue<K, T>>::template Iterator<KeyValue<K, T>> it) : iterator(it) {}

    //    MapIterator& operator++() {
    //        ++iterator;
    //        return *this;
    //    }

    //    bool operator!=(const MapIterator& other) const {
    //        return iterator != other.iterator;
    //    }

    //    KeyValue<K, T>& operator*() {
    //        return iterator;
    //    }
    //};

    //MapIterator<K, T> begin() {
    //    return MapIterator<K, T>(AVLTree<KeyValue<K, T>>::begin());
    //}

    //MapIterator<K, T> end() {
    //    return MapIterator<K, T>(AVLTree<KeyValue<K, T>>::end());
    //}
};