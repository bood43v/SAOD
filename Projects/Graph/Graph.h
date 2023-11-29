#pragma once

#include <vector>
#include <queue>
const int MaxGraphSize = 25;

template <class T>
class Graph
{
private:
    // Основные данные включают список вершин, матрицу смежности
    // и текущий размер (число вершин) графа
    std::vector<T> vertexList;
    int edge[MaxGraphSize][MaxGraphSize];
    int graphSize;

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

    int GetVertexPos(const T& vertex)
    {
        return FindVertex(vertexList, vertex);
    }

public:
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

    int GraphEmpty() const
    {
        return graphSize == 0;
    }

    int GraphFull() const
    {
        return graphSize == MaxGraphSize;
    }

    int NumberOfVertices() const
    {
        return graphSize;
    }



    int GetWeight(const T& vertex1, const T& vertex2)
    {
        int pos1 = GetVertexPos(vertex1);
        int pos2 = GetVertexPos(vertex2);
        if (pos1 != -1 && pos2 != -1)
        {
            return edge[pos1][pos2];
        }
        return 0;
    }

    int NumberOfEdges() const
    {
        int edgeCount = 0;
        for (int i = 0; i < graphSize; ++i)
        {
            for (int j = 0; j < graphSize; ++j)
            {
                if (edge[i][j] != 0)
                {
                    edgeCount++;
                }
            }
        }
        return edgeCount;
    }



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
        return neighbors;
    }

    void InsertVertex(const T& vertex)
    {
        if (graphSize < MaxGraphSize)
        {
            vertexList.push_back(vertex);
            graphSize++;
        }
    }

    void InsertEdge(const T& vertex1, const T& vertex2, int weight)
    {
        int pos1 = GetVertexPos(vertex1);
        int pos2 = GetVertexPos(vertex2);
        if (pos1 != -1 && pos2 != -1)
        {
            edge[pos1][pos2] = weight;
            edge[pos2][pos1] = weight;
        }
    }

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
};

