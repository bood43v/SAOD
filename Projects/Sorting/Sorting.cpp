/// Турнирная сортировка 
/// @author Будаев Г.Б.

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/// Печать вектора
template<typename T>
void print(vector<T> vec)
{
    int n = vec.size();
    for (int i = 0; i < n; i++) {
        cout << vec[i] << " ";
    }
}

/// Турнирная сортировка по возрастанию с изменением вектора, который был передан
template<typename T>
void tournamentSort(vector<T>& vec)
{
    int vecSize = vec.size();
    /// Определяем размер турнирного дерева
    int treeSize = 1;
    while (treeSize <= vecSize) {
        treeSize *= 2;
    }

    // Создаем массив размером с общее количество узлов (элементов) в дереве турнира
    int size = (2 * treeSize);
    vector<T> tree(size);

    // Назначает каждому узлу в дереве максимальное значение используемого типа 
    for (int i = 0; i < size; i++) {
        tree[i] = numeric_limits<T>::max();
    }

    // Присваивает элементы из несортированного массива в листья
    for (int i = 0; i < vecSize; i++) {
        tree[treeSize + i] = vec[i];
    }

    // Построение турнирного дерева
    for (int i = treeSize - 1; i >= 1; i--) {
        tree[i] = min(tree[2 * i], tree[2 * i + 1]);
    }

    // Извлечение и перестроение дерева
    int sortIndex = 0;
    while (sortIndex < vecSize) {
        // Заполнение в вектор и присваивание корню максимального значения
        vec[sortIndex] = tree[1];
        sortIndex++;
        tree[1] = numeric_limits<T>::max();

        // Заменяет минимальное значение на "максимальное"
        int node = 1;
        while (node < treeSize) {
            int leftChild = 2 * node;
            int rightChild = 2 * node + 1;

            // Узлу присваивается порядковый номер наименьшего значения тернарным оператором
            node = (tree[leftChild] < tree[rightChild]) ? leftChild : rightChild;

            // Изменяет наименьшее на "максимальное"
            if (tree[leftChild] < tree[rightChild]) {
                tree[leftChild] = numeric_limits<T>::max();
            }
            else {
                tree[rightChild] = numeric_limits<T>::max();
            }
        }

        // Построение турнирного дерева
        for (int i = treeSize - 1; i >= 1; i--) {
            tree[i] = min(tree[2 * i], tree[2 * i + 1]);
        }
    }
}

/// Тестирование турнирной соритровки
template <class T>
void testSort(vector<T> vec) {
    tournamentSort(vec);
    if (is_sorted(vec.begin(), vec.end()))
    {
        cout << "Successful sort" << endl;
    }
    else
        cout << "Sort error" << endl;

}

int main() {
    vector<int> vec1 = { 44, 55, 1, -5, 1 };
    vector<int> vec2 = { 1,2,3,4,5,6,7,8,9 };
    vector<int> vec3 = { 9,8,7,6,5,4,3,2,1 };
    vector<int> vec4 = { 65 };

    testSort(vec1);
    testSort(vec2);
    testSort(vec3);
    testSort(vec4);
}