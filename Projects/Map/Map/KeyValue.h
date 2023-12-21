/// Класс KeyValue для хранения пары ключ - значение
/// @author Будаев Г.Б.
#pragma once

using namespace std;

// класс пары ключ-значение
template <class K, class T>
class KeyValue
{
protected:
    // после инициализации ключ не может быть изменен
    const K key; 
public:
    // словарные данные являются общедоступными
    T value; 

    // возврат ссылки на данные
    T& GetValue() {
        return value;
    }

    // конструктор
    // keyVal - значение ключа
    // dataValue - данные
    KeyValue(K keyVal, T dataValue) : key(keyVal), value(dataValue) {}

    // оператор присваивания, не изменяют ключ
    KeyValue<K, T>& operator =(const KeyValue<K, T> &rhs)
    {
        if (this != &rhs)
        {
            key = rhs.key;
            value = rhs.value;
        }
        return *this;
    }

    // операторы сравнения, сравнивают два ключа
    bool operator== (const KeyValue<K, T>& rhs) const
    {
        return key == rhs.key;
    }

    // оператор меньше
    bool operator< (const KeyValue<K, T>& rhs) const
    {
        return key < rhs.key;
    }

    // оператор больше
    bool operator> (const KeyValue<K, T>& rhs) const
    {
        return key > rhs.key;
    }

    // метод доступа к ключу
    K Key() const
    {
        return key;
    }

    //bool operator< (const K& keyVal) const
    //{
    //    return key < keyVal;
    //}

    //bool operator> (const K& keyVal) const
    //{
    //    return key > keyVal;
    //}
};