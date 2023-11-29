/// –еализаци€ класса Graph
/// @author Ѕудаев √.Ѕ.
#pragma once

#include <vector>
#include <queue>
#include <iomanip>
const int MaxGraphSize = 25;


/// <summary>
/// класс граф с фиксированным максимальным размером.
/// > Eсли вставить уже существующее ребро -> ќно перезапишетс€
/// > ѕри вставке нового ребра в матрицу смежности вставл€етс€ только положительное значение. ≈сли отрицательное -> 
/// -> вставл€етс€ противоположное по модулю, но мен€етс€ источник дуги
/// </summary>
/// <typeparam name="T"></typeparam>
template <class T>
class Graph
{
private:
    // ќсновные данные включают список вершин, матрицу смежности
    // и текущий размер (число вершин) графа
    std::vector<T> vertexList;
    int edge[MaxGraphSize][MaxGraphSize];
    int graphSize;

    /// <summary>
    /// закрытые вспомогательные методы
    /// поиск вершины в массиве
    /// </summary>
    /// <param name="L"></param>
    /// <param name="vertex"></param>
    /// <returns></returns>
    int FindVertex(const std::vector<T>& L, const T& vertex)
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
    /// позици€
    /// </summary>
    /// <param name="vertex"></param>
    /// <returns></returns>
    int GetVertexPos(const T& vertex)
    {
        return FindVertex(vertexList, vertex);
    }

    /// <summary>
    /// 
    /// </summary>
    /// <typeparam name="T"></typeparam>
    void BreadthFirstSearchHelper(int vertex, std::vector<bool>& marked, std::vector<T>& visited)
    {
        std::queue<int> queue;
        marked[vertex] = true;
        queue.push(vertex);

        while (!queue.empty())
        {
            int currVertex = queue.front();
            queue.pop();
            visited.push_back(vertexList[currVertex]);

            for (int i = 0; i < graphSize; ++i)
            {
                if (edge[currVertex][i] != 0 && !marked[i])
                {
                    marked[i] = true;
                    queue.push(i);
                }
            }
        }
    }

    /// <summary>
    /// 
    /// </summary>
    /// <param name="vertex"></param>
    /// <param name="marked"></param>
    /// <param name="visited"></param>
    void DepthFirstSearchHelper(int vertex, std::vector<bool>& marked, std::vector<T>& visited)
    {
        marked[vertex] = true;
        visited.push_back(vertexList[vertex]);
        for (int i = 0; i < graphSize; ++i)
        {
            if (edge[vertex][i] != 0 && !marked[i])
            {
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
        int pos1 = GetVertexPos(vertex1);
        int pos2 = GetVertexPos(vertex2);
        if (pos1 != -1 && pos2 != -1)
        {
            if (weight >= 0)
                edge[pos1][pos2] = weight;
            if (weight <= 0)
                edge[pos2][pos1] = -weight;
        }
        //else throw " ак минимум одной из вершин нет!";
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
    /// ѕечать матрицы смежности
    /// </summary>
    void PrintAdjacencyMatrix() const
    {
        // ¬ывод значений вершин дл€ вертикальной оси
        std::cout << "   ";
        for (int i = 0; i < graphSize; ++i)
        {
            std::cout << std::setw(3) << vertexList[i];
        }
        std::cout << std::endl;

        // ¬ывод значений вершин и значений матрицы смежности
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
        throw "“акой св€зи нет";
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
                if (edge[i][j] != 0 || (i == j && edge[i][j] == 1))
                {
                    edgeCount++;
                }
            }
        }
        return edgeCount;
    }

    /// <summary>
    /// вернуть соседей
    /// </summary>
    /// <param name="vertex"></param>
    /// <returns></returns>
    std::vector<T> GetNeighbors(const T& vertex)
    {
        std::vector<T> neighbors;
        int pos = GetVertexPos(vertex);
        if (pos != -1)
        {
            for (int i = 0; i < graphSize; ++i)
            {
                if (edge[pos][i] != 0)
                {
                    neighbors.push_back(vertexList[i]);
                }
            }
        }
        sort(neighbors.begin(), neighbors.end());
        return neighbors;
    }



    /// <summary>
    /// в глубину
    /// </summary>
    /// <param name="beginVertex"></param>
    /// <returns></returns>
    std::vector<T> DepthFirstSearch(const T& beginVertex)
    {
        std::vector<T> visited;
        std::vector<bool> marked(graphSize, false);
        int pos = GetVertexPos(beginVertex);
        if (pos != -1)
        {
            DepthFirstSearchHelper(pos, marked, visited);
        }
        return visited;
    }

    /// <summary>
    /// в ширину
    /// </summary>
    /// <typeparam name="T"></typeparam>
    std::vector<T> BreadthFirstSearch(const T& beginVertex)
    {
        std::vector<T> visited;
        std::vector<bool> marked(graphSize, false);
        int pos = GetVertexPos(beginVertex);
        if (pos != -1)
        {
            BreadthFirstSearchHelper(pos, marked, visited);
        }
        return visited;
    }

    template <class F>
    // ¬ложенный класс итератора
    class Iterator
        {
        private:
            const Graph<F>& graph;
            int currentIndex;

        public:
                Iterator(const Graph<F>& g, int index) : graph(g), currentIndex(index) {}

            // ѕерегрузка оператора разыменовани€ *
            F operator*() const
            {
                return graph.vertexList[currentIndex];
            }

            // ѕерегрузка оператора инкремента префиксного ++
            Iterator<F>& operator++()
            {
                ++currentIndex;
                return *this;
            }

            // ѕерегрузка оператора инкремента постфиксного ++
            Iterator<F> operator++(int)
            {
                Iterator<F> temp = *this;
                ++(*this);
                return temp;
            }

            // ѕерегрузка оператора сравнени€ ==
            bool operator==(const Iterator<F>& other) const
            {
                return currentIndex == other.currentIndex;
            }

            // ѕерегрузка оператора сравнени€ !=
            bool operator!=(const Iterator<F>& other) const
            {
                return !(*this == other);
            }
     };

    // ћетоды begin() и end() дл€ получени€ итераторов
    Iterator<T> begin() const
    {
        return Iterator<T>(*this, 0);
    }

    Iterator<T> end() const
    {
        return Iterator<T>(*this, graphSize);
    }
};

