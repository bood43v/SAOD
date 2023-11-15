﻿/// Турнирная сортировка 
/// @author Будаев Г.Б.

#include <iostream>
#include <vector>
#include <algorithm>
#include "../Heap/Heap.h"

using namespace std;

/// Печать вектора
template<typename T>
void print(const vector<T>& vec)
{
    int n = vec.size();
    for (int i = 0; i < n; i++) {
        cout << vec[i] << " ";
    }
    cout << endl;
}

/// Пирамидальная сортировка по возрастанию с изменением вектора, который был передан
template<typename T>
void pyramidSort(vector<T>& vec)
{
    MaxHeap<T> heap(vec);
    vector<T> sortedVec;
    vec = heap.heapSort();
}


 //массив из указателей на Т

 //Турнирная сортировка по возрастанию с изменением вектора, который был передан
 //mode - режим сортировки
 //0 - по возрастанию
 //1 - по убыванию
template<typename T>

vector<T> tournamentSort(unsigned const int mode,vector<T> arr)
{
    vector<T*> vec;
    for (int i = 0; i < arr.size(); i++) {
        vec.push_back(&arr[i]);
    }

    if ((mode != 0) && (mode != 1)) throw "Wrong sorting mode! (0 or 1)";
    else {

        int vecSize = arr.size();
        /// Определяем размер турнирного дерева
        int treeSize = 1;
        while (treeSize <= vecSize) {
            treeSize *= 2;
        }

        // Создаем массив размером с общее количество узлов (элементов) в дереве турнира
        int size = (2 * treeSize);
        vector<T*> tree(size);

        // Назначает каждому узлу в дереве максимальное значение используемого типа 
        for (int i = 0; i < size; i++) {

            tree[i] = nullptr;
        }

        // Присваивает элементы из несортированного массива в листья
        for (int i = 0; i < vecSize; i++) {
            tree[treeSize + i] = vec[i];
        }

        // Построение турнирного дерева
        for (int i = treeSize - 1; i >= 1; i--) {
            tree[i] = (mode == 1) ? *min_element(&tree[2 * i], &tree[2 * i + 1]) : *max_element(&tree[2 * i], &tree[2 * i + 1]);
        }

        // Извлечение и перестроение дерева
        int sortIndex = 0;
        while (sortIndex < vecSize) {
            // Заполнение в вектор и присваивание корню максимального значения
            vec[sortIndex] = tree[1];
            sortIndex++;

            // Найти индекс элемента с наибольшим/наименьшим значением в оставшейся части дерева
            int maxminIndex = (mode == 1) ? max_element(tree.begin() + treeSize, tree.end()) - tree.begin() : 
                min_element(tree.begin() + treeSize, tree.end()) - tree.begin();

            // Присвоить корню указатель на найденный элемент
            tree[1] = tree[maxminIndex];
            tree[maxminIndex] = nullptr;

            // Построение турнирного дерева
            for (int i = treeSize - 1; i >= 1; i--) {
                tree[i] = (mode == 1) ? *min_element(&tree[2 * i], &tree[2 * i + 1]) : *max_element(&tree[2 * i], &tree[2 * i + 1]);
            }
        }
        for (int i = 0; i < vec.size(); i++) {
            arr[i] = *vec[i];
        }
        return arr;
    }


  
}

//template<typename T>
//void tournamentSort(unsigned const int mode, vector<T>& vec)
//{
//    if ((mode != 0) && (mode != 1)) throw "Wrong sorting mode! (0 or 1)";
//    else {
//
//        int vecSize = vec.size();
//        /// Определяем размер турнирного дерева
//        int treeSize = 1;
//        while (treeSize <= vecSize) {
//            treeSize *= 2;
//        }
//
//        // Создаем массив размером с общее количество узлов (элементов) в дереве турнира
//        int size = (2 * treeSize);
//        vector<T> tree(size);
//
//        // Назначает каждому узлу в дереве максимальное значение используемого типа 
//        for (int i = 0; i < size; i++) {
//
//            tree[i] = (mode == 1) ? numeric_limits<T>::max() : numeric_limits<T>::min();
//        }
//
//        // Присваивает элементы из несортированного массива в листья
//        for (int i = 0; i < vecSize; i++) {
//            tree[treeSize + i] = vec[i];
//        }
//
//        // Построение турнирного дерева
//        for (int i = treeSize - 1; i >= 1; i--) {
//            tree[i] = (mode == 1) ? min(tree[2 * i], tree[2 * i + 1]) : max(tree[2 * i], tree[2 * i + 1]);
//        }
//
//        // Извлечение и перестроение дерева
//        int sortIndex = 0;
//        while (sortIndex < vecSize) {
//            // Заполнение в вектор и присваивание корню максимального значения
//            vec[sortIndex] = tree[1];
//            sortIndex++;
//            tree[1] = (mode == 1) ? numeric_limits<T>::max() : numeric_limits<T>::min();
//
//            // Заменяет минимальное значение на "максимальное"
//            int node = 1;
//            while (node < treeSize) {
//                int leftChild = 2 * node;
//                int rightChild = 2 * node + 1;
//
//                // Узлу присваивается порядковый номер наименьшего значения тернарным оператором
//                node = (mode == 1) ? ((tree[leftChild] < tree[rightChild]) ? leftChild : rightChild) : ((tree[leftChild] > tree[rightChild]) ? leftChild : rightChild);
//
//                // Изменяет наименьшее на "максимальное"
//                if ((mode == 1) ? (tree[leftChild] < tree[rightChild]) : (tree[leftChild] > tree[rightChild])) {
//                    tree[leftChild] = (mode == 1) ? numeric_limits<T>::max() : numeric_limits<T>::min();
//                }
//                else {
//                    tree[rightChild] = (mode == 1) ? numeric_limits<T>::max() : numeric_limits<T>::min();;
//                }
//            }
//
//            // Построение турнирного дерева
//            for (int i = treeSize - 1; i >= 1; i--) {
//                tree[i] = (mode == 1) ? min(tree[2 * i], tree[2 * i + 1]) : max(tree[2 * i], tree[2 * i + 1]);
//            }
//        }
//    }
//
//
//}


/// Тестирование турнирной соритровки
template <class T>
void testTournamentSort(unsigned const int mode, vector<T> vec) {
    //vector<T> vec2 = vec;
    tournamentSort(mode, vec);

    if (mode == 1) {
        if (is_sorted(vec.begin(), vec.end()))
        {
            cout << "Successful tournament sort" << endl;
        }
        else
            cout << "Tournament sort error" << endl;
    }
    else
        if (mode == 0) {
            if (is_sorted(vec.begin(), vec.end(), greater<T>()))
            {
                cout << "Successful tournament sort" << endl;
            }
            else
                cout << "Tournament sort error" << endl;
        }
        else throw " Wrong sort mode!";

}

/// Тестирование турнирной соритровки
template <class T>
void testPyramidSort(vector<T> vec) {
    //vector<T> vec2 = vec;
    pyramidSort(vec);
    if (is_sorted(vec.begin(), vec.end(), greater<T>()))
    {
        cout << "Successful pyramid sort" << endl;
    }
    else
        cout << "Pyramid sort error" << endl;
}

int main() {
    try {
        vector<int> vec1 = { 44, 55, 1, -5, 1 };
        //vector<int> vec2 = { 1,2,3,4,5,6,7,8,9 };
        //vector<int> vec3 = { 9,8,7,6,5,4,3,2,1 };
        //vector<int> vec4 = { 65 };

        //testTournamentSort(1, vec1);
        //testTournamentSort(1, vec2);
        //testTournamentSort(1, vec3);
        //testTournamentSort(1, vec4);

        //vector<int> vec5 = { 44, 55, 1, -5, 1 };
        //vector<int> vec6 = { 1,2,3,4,5,6,7,8,9 };
        //vector<int> vec7 = { 9,8,7,6,5,4,3,2,1 };
        //vector<int> vec8 = { 65 };

        //testTournamentSort(0, vec5);
        //testTournamentSort(0, vec6);
        //testTournamentSort(0, vec7);
        //testTournamentSort(0, vec8);

        //vector<int> vec9 = { 44, 55, 1, -5, 1 };
        //vector<int> vec10 = { 1,2,3,4,5,6,7,8,9 };
        //vector<int> vec11 = { 9,8,7,6,5,4,3,2,1 };
        //vector<int> vec12 = { 65 };

        //testPyramidSort(vec9);
        //testPyramidSort(vec10);
        //testPyramidSort(vec11);
        //testPyramidSort(vec12);

        vector<int> x = tournamentSort(0, vec1);
        print(x);

        //tournamentSort(0, vec1);
        //print(vec1);


        //pyramidSort(vec1);
        //print(vec1);
    }
    catch (const char* error_message) {
        cout << error_message << endl;
    }

}