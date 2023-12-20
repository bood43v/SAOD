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
        // определить целевой объект типа KeyValue, содержащий
        // данные задаваемые по умолчанию
        KeyValue<K, T> targetKey(index, defaultValue);
        // искать ключ, если не найден, вставить targetKey
        if (!this->Search(targetKey))
            this->Insert(targetKey);
        // возвратить ссылку на найденные или вставленные данные
        return targetKey.value;
    }

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

    void DeleteKey(const K& keyval)
    {
        KeyValue<K, T> tmp(keyval, defaultValue);
        this->Remove(tmp);
    }
};