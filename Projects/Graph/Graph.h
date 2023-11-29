/// Реализация класса Graph
/// @author Будаев Г.Б.
#pragma once

using namespace std;

#include <vector>
#include <queue>
#include <iomanip>
const int MaxGraphSize = 25;


/// <summary>
/// класс граф с фиксированным максимальным размером.
/// > Eсли вставить уже существующее ребро -> Оно перезапишется
/// > При вставке нового ребра в матрицу смежности вставляется только положительное значение. Если отрицательное -> 
/// -> вставляется противоположное по модулю, но меняется источник дуги
/// </summary>
/// <typeparam name="T"></typeparam>
template <class T>
class Graph
{
private:
    // Основные данные включают список вершин, матрицу смежности
    // и текущий размер (число вершин) графа
    vector<T> vertexList;
    int edge[MaxGraphSize][MaxGraphSize];
    int graphSize;

    /// <summary>
    /// закрытые вспомогательные методы
    /// поиск вершины в массиве
    /// </summary>
    /// <param name="L"></param>
    /// <param name="vertex"></param>
    /// <returns></returns>
    int FindVertex(const vector<T>& L, const T& vertex)
    {
        for (int i = 0; i < L.size(); ++i)
        {
            if (L[i] == vertex)
            {
                return i;
            }
        }
        return -1;
    }

    /// <summary>
    /// закрытые вспомогательные методы
    /// позиция
    /// </summary>
    /// <param name="vertex"></param>
    /// <returns></returns>
    int GetVertexPos(const T& vertex)
    {
        return FindVertex(vertexList, vertex);
    }


    /// <summary>
    /// рекурсивный вспомогательный метод обхода в глубину 
    /// </summary>
    /// <param name="vertex"></param>
    /// <param name="marked"></param>
    /// <param name="visited"></param>
    void DepthFirstSearchHelper(int vertex, vector<bool>& marked, vector<T>& visited)
    {
        marked[vertex] = true;                  // пометка текущей вершины, как посещенной
        visited.push_back(vertexList[vertex]);  // добавляем текущую вершину в вектор посещенных
        for (int i = 0; i < graphSize; ++i)     // перебор смежных вершин
        {
            // если существует ребро между текущей вершиной и смежной вершиной 
            // и смежная вершина i еще не была посещена
            if (edge[vertex][i] != 0 && !marked[i])
            {
                // рекурсивно вызываем метод DepthFirstSearchHelper для смежной вершины i
                DepthFirstSearchHelper(i, marked, visited);
            }
        }
    }

public:

    /// <summary>
    /// конструктор без параметров
    /// </summary>
    Graph()
    {
        graphSize = 0;
        for (int i = 0; i < MaxGraphSize; ++i)
        {
            for (int j = 0; j < MaxGraphSize; ++j)
            {
                edge[i][j] = 0;
            }
        }
    }

    /// <summary>
    /// вставка узла
    /// </summary>
    /// <param name="vertex"></param>
    void InsertVertex(const T& vertex)
    {
        if (graphSize < MaxGraphSize)
        {
            vertexList.push_back(vertex);
            graphSize++;
        }
    }

    /// <summary>
    /// вставка ребра (установка)
    /// </summary>
    /// <param name="vertex1"></param>
    /// <param name="vertex2"></param>
    /// <param name="weight"></param>
    void InsertEdge(const T& vertex1, const T& vertex2, int weight)
    {
        if (weight == 0) throw "Вес не может быть нулевым!";
        int pos1 = GetVertexPos(vertex1);
        int pos2 = GetVertexPos(vertex2);
        if (pos1 != -1 && pos2 != -1)
        {
            if (weight >= 0)
                edge[pos1][pos2] = weight;
            if (weight <= 0)
                edge[pos2][pos1] = -weight;
        }
        //else throw "Как минимум одной из вершин нет!";
    }

    /// <summary>
    /// удалить вершину
    /// </summary>
    /// <param name="vertex"></param>
    void DeleteVertex(const T& vertex)
    {
        int pos = GetVertexPos(vertex);
        if (pos != -1)
        {
            vertexList.erase(vertexList.begin() + pos);
            for (int i = pos; i < graphSize - 1; ++i)
            {
                for (int j = 0; j < graphSize; ++j)
                {
                    edge[i][j] = edge[i + 1][j];
                }
            }
            for (int i = 0; i < graphSize; ++i)
            {
                for (int j = pos; j < graphSize - 1; ++j)
                {
                    edge[i][j] = edge[i][j + 1];
                }
            }
            graphSize--;
        }
    }

    /// <summary>
    /// удалить ребро
    /// </summary>
    /// <typeparam name="T"></typeparam>
    void DeleteEdge(const T& vertex1, const T& vertex2)
    {
        int pos1 = GetVertexPos(vertex1);
        int pos2 = GetVertexPos(vertex2);
        if (pos1 != -1 && pos2 != -1)
        {
            edge[pos1][pos2] = 0;
            edge[pos2][pos1] = 0;
        }
    }

    /// <summary>
    /// печать матрицы смежности с выводом значений вершин
    /// </summary>
    void PrintAdjacencyMatrix() const
    {
        // Вывод значений вершин для вертикальной оси
        std::cout << "   ";
        for (int i = 0; i < graphSize; ++i)
        {
            std::cout << std::setw(3) << vertexList[i];
        }
        std::cout << std::endl;

        // Вывод значений вершин и значений матрицы смежности
        for (int i = 0; i < graphSize; ++i)
        {
            std::cout << std::setw(3) << vertexList[i];
            for (int j = 0; j < graphSize; ++j)
            {
                std::cout << std::setw(3) << edge[i][j];
            }
            std::cout << std::endl;
        }
    }

    /// <summary>
    /// пустой ли граф
    /// </summary>
    /// <returns></returns>
    int isEmpty() const
    {
        return graphSize == 0;
    }

    /// <summary>
    /// полный ли граф
    /// </summary>
    /// <returns></returns>
    int isFull() const
    {
        return graphSize == MaxGraphSize;
    }

    /// <summary>
    /// количество вершин
    /// </summary>
    /// <returns></returns>
    int NumberOfVertices() const
    {
        return graphSize;
    }


    /// <summary>
    /// вернуть вес ребра между вершинами
    /// </summary>
    /// <param name="vertex1"></param>
    /// <param name="vertex2"></param>
    /// <returns></returns>
    int GetWeight(const T& vertex1, const T& vertex2)
    {
        int pos1 = GetVertexPos(vertex1);
        int pos2 = GetVertexPos(vertex2);
        if (pos1 != -1 && pos2 != -1)
        {
            return edge[pos1][pos2];
        }
        throw "Такой связи нет";
    }

    /// <summary>
    /// число ребер
    /// </summary>
    /// <returns></returns>
    int NumberOfEdges() const
    {
        int edgeCount = 0;
        for (int i = 0; i < graphSize; ++i)
        {
            for (int j = i; j < graphSize; ++j)
            {
                if (edge[i][j] != 0)
                {
                    edgeCount++;
                }
            }
        }
        return edgeCount;
    }

    /// <summary>
    /// вернуть соседей - узел не может быть соседом самому себе
    /// </summary>
    /// <param name="vertex"></param>
    /// <returns></returns>
    vector<T> GetNeighbors(const T& vertex)
    {
        vector<T> neighbors;
        int pos = GetVertexPos(vertex);
        if (pos != -1)
        {
            for (int i = 0; i < graphSize; ++i)
            {
                // которые выходят из vertex
                if (edge[pos][i] != 0 && pos != i)
                {
                    neighbors.push_back(vertexList[i]);
                }
                // которые входят в vertex
                if (edge[i][pos] != 0 && pos != i)
                {
                    neighbors.push_back(vertexList[i]);
                }
            }
        }
        // сортировка вектора для удобства
        sort(neighbors.begin(), neighbors.end());
        return neighbors;
    }



    /// <summary>
    /// обход в глубину
    /// </summary>
    /// <param name="beginVertex"></param>
    /// <returns></returns>
    vector<T> DepthFirstSearch(const T& vertex)
    {
        vector<T> visited;// посещенные вершины - значения
        vector<bool> marked(graphSize, false);// посещенные вершины - отметки
        // позиция начальной вершины в списке вершин
        int pos = GetVertexPos(vertex);
        // если начальная вершина найдена, выполняем обход в глубину
        if (pos != -1)
        {
            DepthFirstSearchHelper(pos, marked, visited);
        }
        return visited;
    }

    /// <summary>
    /// обход в ширину
    /// </summary>
    /// <typeparam name="T"></typeparam>
    vector<T> BreadthFirstSearch(const T& beginVertex)
    {
        vector<T> visited;                      // вектор для посещенных вершин
        vector<bool> marked(graphSize, false);  // вектор для отметки посещенных вершин
        int pos = GetVertexPos(beginVertex);    // Поиск позиции начальной вершины в списке вершин
        // если вершина найдена
        if (pos != -1)
        {
            queue<int> queue;// очередь для хранения вершин
            marked[pos] = true;// отмечаем начальную вершину как посещенную и помещаем в очередь
            queue.push(pos);

            // цикл обхода в ширину
            while (!queue.empty())
            {
                // извлекаем вершину из очереди
                int currVertex = queue.front();
                queue.pop();
                // добавляем посещенную вершину в вектор visited
                visited.push_back(vertexList[currVertex]);

                // перебор смежных вершин
                for (int i = 0; i < graphSize; ++i)
                {
                    // если существует ребро между текущей вершиной и смежной вершиной i
                    // и смежная вершина i еще не была посещена, то отмечаем ее как посещенную и добавляем в очередь
                    if (edge[currVertex][i] != 0 && !marked[i])
                    {
                        marked[i] = true;
                        queue.push(i);
                    }
                }
            }
        }
        return visited;
    }

    template <class F>
    // Вложенный класс итератора для Graph
    class Iterator
        {
        private:
            const Graph<F>& graph;
            int currentIndex;

        public:
            Iterator(const Graph<F>& g, int index) : graph(g), currentIndex(index) {}

            // Перегрузка оператора разыменования *
            F operator*() const
            {
                return graph.vertexList[currentIndex];
            }

            // Перегрузка оператора инкремента префиксного ++
            Iterator<F>& operator++()
            {
                ++currentIndex;
                return *this;
            }

            // Перегрузка оператора инкремента постфиксного ++
            Iterator<F> operator++(int)
            {
                Iterator<F> temp = *this;
                ++(*this);
                return temp;
            }

            // Перегрузка оператора сравнения ==
            bool operator==(const Iterator<F>& other) const
            {
                return currentIndex == other.currentIndex;
            }

            // Перегрузка оператора сравнения !=
            bool operator!=(const Iterator<F>& other) const
            {
                return !(*this == other);
            }
     };

    // первый элемент
    Iterator<T> begin() const
    {
        return Iterator<T>(*this, 0);
    }

    // последний элемент
    Iterator<T> end() const
    {
        return Iterator<T>(*this, graphSize);
    }
};

