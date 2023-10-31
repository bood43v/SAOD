// Работа с функциями из библиотеки algorithm
// @author Будаев Г.Б.
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;


void PrintInt(int value)
{
    cout << value << " ";
}

void PrintIntVector(const vector<int>& v)
{
    for_each(v.begin(), v.end(), PrintInt);
}

int main() {
    //-------- for_each --------//
    // печать вектора
    vector<int> v; 
    for (int i = 1; i < 10; i++)
    {
        v.push_back(i);
    }
    // так
    PrintIntVector(v);
    cout << endl;
    // или так
    for_each(v.begin(), v.end(), [](int value) {cout << value << " "; });
    cout << endl;


    //-------- transform --------//
    // изменение вектора и сохранение результата в другом
    vector<int> source;
    for (int i = 0; i < 10; i++)
    {
        source.push_back(i);
    }
    vector<int> target(source.size());
    // target.begin - вектор сохранения действий над элементами вектора source (возведение в квадрат
    transform(source.begin(), source.end(), target.begin(), [](int& a) {return a * a; });
    // вывод нового вектора
    for_each(target.begin(), target.end(), [](int a) {cout << a << ' '; });



    //-------- copy_if --------//
    // копирование только четных значений вектора
    vector<int> target2(5);
    copy_if(source.begin(), source.end(), target2.begin(), [](int value) { return value % 2 == 0; });
    for_each(target2.begin(), target2.end(), [](int a) {cout << a << ' '; });


    //-------- any_of --------//
    // вывод наличия отрицательных элементов в векторе
    cout << endl;
    if (any_of(v.begin(), v.end(), [](int value) { return value < 0; }) == true)
        cout << "Array has negative element(s)" << endl;
    else cout << "Array hasn't negative elements" << endl;






}