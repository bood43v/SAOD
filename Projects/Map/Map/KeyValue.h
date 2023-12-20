/// Класс KeyValue
/// @author Будаев Г.Б.#pragma once

using namespace std;

template <class K, class T>
class KeyValue
{
protected:
    const K key; // после инициализации ключ не может быть изменен
public:
    T value; // словарные данные являются общедоступными

    KeyValue(K keyVal, T dataValue) : key(keyVal), value(dataValue) {}

    // операторы присваивания, не изменяют ключ
    KeyValue<K, T>& operator= (const KeyValue<K, T>& rhs)
    {
        if (this != &rhs)
        {
            value = rhs.value;
        }
        return *this;
    }

    // операторы сравнения, сравнивают два ключа
    bool operator== (const KeyValue<K, T>& rhs) const
    {
        return key == rhs.key;
    }

    bool operator== (const K& keyVal) const
    {
        return key == keyVal;
    }

    bool operator< (const KeyValue<K, T>& rhs) const
    {
        return key < rhs.key;
    }

    bool operator< (const K& keyVal) const
    {
        return key < keyVal;
    }

    // метод доступа к ключу
    K Key() const
    {
        return key;
    }
};