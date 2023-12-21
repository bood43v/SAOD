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
    /// конструктор
    /// </summary>
    /// <param name="defaultval"></param>
    Map(const T& defaultValue) : AVLTree<KeyValue<K,T>>(), defaultValue(defaultValue) {}

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
    /// проверка, находится ли в словаре значение
    /// </summary>
    /// <param name="keyval"></param>
    /// <returns></returns>
    int InDictionary(const K& keyval)
    {
        // определить целевой объект типа KeyValue, содержащий
        // данные задаваемые по умолчанию
        KeyValue<K, T> tmp(keyval, defaultValue);
        int retval = 1;
        // искать tmp на дереве, вернуть результат
        if (!this->Search(tmp))
            retval = 0;
        return retval;
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



    
};