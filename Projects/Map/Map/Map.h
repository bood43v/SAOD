/// Класс Map - словарь на основе AVL дерева
/// @author Будаев Г.Б.
#pragma once
#include "../AVL/AVLTree.h"
#include "KeyValue.h"

/// <summary>
/// Класс словарь со значением по умолчанию defaultValue, которое задаётся при создании объекта в конструкторе
/// </summary>
/// <typeparam name="T"></typeparam>
/// <typeparam name="K"></typeparam>
template <class K, class T>
class Map : public AVLTree<KeyValue<K, T>>
{
private:
    T defaultValue; /// значение по умолчанию

public:
    /// <summary>
    /// Конструктор
    /// </summary>
    /// <param name="defaultval"></param>
    Map(const T& defaultValue) : AVLTree<KeyValue<K,T>>(), defaultValue(defaultValue) {}

    /// Деструктор. Использует унаследованный Clear
    ~Map()
    {
        this->Clear();
    }

    // Конструктор перемещения
    //Map(Map<K,T>& map_moved)
    //{
    //    defaultValue = map_moved.defaultValue;

    //    map_moved->Clear();
    //}
    
    /// оператор индексирования
    /// Добавляет пару. 
    /// "поиск" - Если элемента с таким ключом нет, то добавляется пара ключ/значение по умолчанию
    T& operator[](const K& index)
    {
        // определить целевой объект типа KeyValue, содержащий
        // данные задаваемые по умолчанию
        KeyValue<K, T> targetKey(index, defaultValue);
        // искать ключ, если не найден, вставить targetKey
        if (this->Search(targetKey) == nullptr) {
            this->Insert(targetKey);
        }
            
        /*this->SetCurr(this->Search(targetKey));*/
        // возвратить ссылку на найденные или вставленные данные
        return this->Search(targetKey)->DataRef().GetValue();
    }

    /// <summary>
    /// проверка, находится ли в словаре значение. Если нет - возврат 0
    /// </summary>
    /// <param name="keyval"></param>
    /// <returns></returns>
    bool InDictionary(const K& keyval) const
    {
        // определить целевой объект типа KeyValue, содержащий
        // данные задаваемые по умолчанию
        KeyValue<K, T> tmp(keyval, defaultValue);
        // искать tmp на дереве, вернуть результат
        if (!this->Search(tmp))
            return false;
        return true;
    }

    /// <summary>
    /// удаление ключа из словаря
    /// </summary>
    /// <param name="keyval"></param>
    void DeleteKey(const K& keyval)
    {
        KeyValue<K, T> tmp(keyval, defaultValue);
        this->Remove(tmp);
    }

    /// void Clear(); - унаследован

    /// int Size(); - унаследован
    





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