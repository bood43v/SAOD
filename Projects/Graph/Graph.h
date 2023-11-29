/// ���������� ������ Graph
/// @author ������ �.�.
#pragma once

#include <vector>
#include <queue>
#include <iomanip>
const int MaxGraphSize = 25;


/// <summary>
/// ����� ���� � ������������� ������������ ��������.
/// > E��� �������� ��� ������������ ����� -> ��� �������������
/// > ��� ������� ������ ����� � ������� ��������� ����������� ������ ������������� ��������. ���� ������������� -> 
/// -> ����������� ��������������� �� ������, �� �������� �������� ����
/// </summary>
/// <typeparam name="T"></typeparam>
template <class T>
class Graph
{
private:
    // �������� ������ �������� ������ ������, ������� ���������
    // � ������� ������ (����� ������) �����
    std::vector<T> vertexList;
    int edge[MaxGraphSize][MaxGraphSize];
    int graphSize;

    /// <summary>
    /// �������� ��������������� ������
    /// ����� ������� � �������
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
    /// �������� ��������������� ������
    /// �������
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
    /// ����������� ��� ����������
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
/// ������� ����
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
    /// ������� ����� (���������)
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
        //else throw "��� ������� ����� �� ������ ���!";
    }

    /// <summary>
    /// ������� �������
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
    /// ������� �����
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
    /// ������ ������� ���������
    /// </summary>
    void PrintAdjacencyMatrix() const
    {
        // ����� �������� ������ ��� ������������ ���
        std::cout << "   ";
        for (int i = 0; i < graphSize; ++i)
        {
            std::cout << std::setw(3) << vertexList[i];
        }
        std::cout << std::endl;

        // ����� �������� ������ � �������� ������� ���������
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
    /// ������ �� ����
    /// </summary>
    /// <returns></returns>
    int isEmpty() const
    {
        return graphSize == 0;
    }

    /// <summary>
    /// ������ �� ����
    /// </summary>
    /// <returns></returns>
    int isFull() const
    {
        return graphSize == MaxGraphSize;
    }

    /// <summary>
    /// ���������� ������
    /// </summary>
    /// <returns></returns>
    int NumberOfVertices() const
    {
        return graphSize;
    }


    /// <summary>
    /// ������� ��� ����� ����� ���������
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
        throw "����� ����� ���";
    }

    /// <summary>
    /// ����� �����
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
    /// ������� �������
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
    /// � �������
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
    /// � ������
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
    // ��������� ����� ���������
    class Iterator
        {
        private:
            const Graph<F>& graph;
            int currentIndex;

        public:
                Iterator(const Graph<F>& g, int index) : graph(g), currentIndex(index) {}

            // ���������� ��������� ������������� *
            F operator*() const
            {
                return graph.vertexList[currentIndex];
            }

            // ���������� ��������� ���������� ����������� ++
            Iterator<F>& operator++()
            {
                ++currentIndex;
                return *this;
            }

            // ���������� ��������� ���������� ������������ ++
            Iterator<F> operator++(int)
            {
                Iterator<F> temp = *this;
                ++(*this);
                return temp;
            }

            // ���������� ��������� ��������� ==
            bool operator==(const Iterator<F>& other) const
            {
                return currentIndex == other.currentIndex;
            }

            // ���������� ��������� ��������� !=
            bool operator!=(const Iterator<F>& other) const
            {
                return !(*this == other);
            }
     };

    // ������ begin() � end() ��� ��������� ����������
    Iterator<T> begin() const
    {
        return Iterator<T>(*this, 0);
    }

    Iterator<T> end() const
    {
        return Iterator<T>(*this, graphSize);
    }
};

