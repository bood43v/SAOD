/// ����� KeyValue ��� �������� ���� ���� - ��������
/// @author ������ �.�.
#pragma once

using namespace std;

// ����� ���� ����-��������
template <class K, class T>
class KeyValue
{
protected:
    // ����� ������������� ���� �� ����� ���� �������
    const K key; 
public:
    // ��������� ������ �������� ��������������
    T value; 

    // ������� ������ �� ������
    T& GetValue() {
        return value;
    }

    // �����������
    // keyVal - �������� �����
    // dataValue - ������
    KeyValue(K keyVal, T dataValue) : key(keyVal), value(dataValue) {}

    // �������� ������������, �� �������� ����
    KeyValue<K, T>& operator =(const KeyValue<K, T> &rhs)
    {
        if (this != &rhs)
        {
            key = rhs.key;
            value = rhs.value;
        }
        return *this;
    }

    // ��������� ���������, ���������� ��� �����
    bool operator== (const KeyValue<K, T>& rhs) const
    {
        return key == rhs.key;
    }

    // �������� ������
    bool operator< (const KeyValue<K, T>& rhs) const
    {
        return key < rhs.key;
    }

    // �������� ������
    bool operator> (const KeyValue<K, T>& rhs) const
    {
        return key > rhs.key;
    }

    // ����� ������� � �����
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