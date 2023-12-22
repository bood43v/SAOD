/// ���������� ������ Graph
/// @author ������ �.�.
#pragma once

using namespace std;

#include <vector>
#include <queue>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <list> 
const int MaxGraphSize = 25;


/// <summary>
/// ����� ���� � ������������� ������������ ��������.
/// > E��� �������� ��� ������������ ����� -> ��� �������������
/// > ��� ������� ������ ����� � ������� ��������� ����������� ������ ������������� ��������. ���� ������������� -> 
/// -> ����������� ��������������� �� ������, �� �������� �������� �����. 
/// ���� ��� ����� 0 - ������ ��� ����������.
/// </summary>
/// <typeparam name="T"></typeparam>
template <class T>
class Graph
{
private:
    // �������� ������ �������� ������ ������, ������� ���������
    // � ������� ������ (����� ������) �����
    vector<T> vertexList;
    T edge[MaxGraphSize][MaxGraphSize];
    int graphSize;

    /// <summary>
    /// �������� ��������������� ������
    /// ����� ������� � �������
    /// </summary>
    /// <param name="L"></param>
    /// <param name="vertex"></param>
    /// <returns></returns>
    int FindVertex(const vector<T>& L, const T& vertex)
    {
        for (int i = 0; i < L.size(); i++)
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
    /// ����������� ��������������� ����� ������ � ������� 
    /// </summary>
    /// <param name="vertex"></param>
    /// <param name="marked"></param>
    /// <param name="visited"></param>
    void DepthFirstSearch_(int vertex, vector<bool>& marked, vector<T>& visited)
    {
        marked[vertex] = true;                  // ������� ������� �������, ��� ����������
        visited.push_back(vertexList[vertex]);  // ��������� ������� ������� � ������ ����������
        for (int i = 0; i < graphSize; i++)     // ������� ������� ������
        {
            // ���� ���������� ����� ����� ������� �������� � ������� �������� 
            // � ������� ������� i ��� �� ���� ��������
            if (edge[vertex][i] != 0 && !marked[i])
            {
                // ���������� �������� ����� DepthFirstSearchHelper ��� ������� ������� i
                DepthFirstSearch_(i, marked, visited);
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
        // ���������� ������
        std::fill(edge[0], edge[0] + MaxGraphSize * MaxGraphSize, 0);

        //std::cout << "Constructor w/o parameters";
    }

    /// <summary>
    /// ����������� � ���������� �������
    /// </summary>
    Graph(const T vertex)
    {
        graphSize = 0;
        // ���������� ������
        std::fill(edge[0], edge[0] + MaxGraphSize * MaxGraphSize, 0);
        // ������� �������
        this->InsertVertex(vertex);
        //std::cout << "Constructor w/ 1 parameter";
    }

    // ����������
    ~Graph() {}

    /// <summary>
    /// ����������� �����������
    /// </summary>
    /// <param name="other"></param>
    Graph(const Graph<T>& graph)
    {
        // ����������� ������ ������
        vertexList = graph.vertexList;
        // ���������� ������� �����
        graphSize = graph.graphSize;
        // ����������� ������� ���������
        //std::memcpy(graph.edge, edge, graphSize * graphSize * sizeof(T));
        //
        for (int i = 0; i < MaxGraphSize; i++) /// memcpy
        {
            for (int j = 0; j < MaxGraphSize; j++)
            {
                edge[i][j] = graph.edge[i][j];
            }
        }
        //std::cout << "Copy constructor" << std::endl;
    }

    /// <summary>
    /// ����������� �����������
    /// </summary>
    /// <param name="other"></param>
    Graph(Graph<T>&& graph)
    {
        // ����������� ������ ������
        vertexList = graph.vertexList;
        graph.vertexList.clear();


        // ����������� ������� ���������
        for (int i = 0; i < MaxGraphSize; i++)
        {
            for (int j = 0; j < MaxGraphSize; j++)
            {
                edge[i][j] = graph.edge[i][j];
            }
        }
        std::fill(graph.edge[0], graph.edge[0] + MaxGraphSize * MaxGraphSize, 0);
        // ����������� ������� �����
        graphSize = graph.graphSize;
        graph.graphSize = 0;
        //std::cout << "Move constructor" << std::endl;
    }

    /// <summary>
    /// �������� ������������ ������������
    /// </summary>
    /// <param name="other"></param>
    /// <returns></returns>
    Graph<T>& operator=(const Graph<T>& graph)
    {
        // ����������� ������ ������
        vertexList = graph.vertexList;

        // ����������� ������� ���������
        for (int i = 0; i < MaxGraphSize; i++)
        {
            for (int j = 0; j < MaxGraphSize; j++)
            {
                edge[i][j] = graph.edge[i][j];
            }
        }

        // ����������� ������� �����
        graphSize = graph.graphSize;
        /*std::cout << "Assignment operator" << std::endl;*/
        return *this;
    }

    /// <summary>
    /// �������� ������������ ������������
    /// </summary>
    /// <param name="other"></param>
    /// <returns></returns>
    Graph<T>& operator=(Graph<T>&& graph)
    {
        // �������� �� ����������������
        if (this != &graph)
        {
            // ����������� ������ ������
            vertexList = std::move(graph.vertexList);

            // ����������� ������� ���������
            for (int i = 0; i < MaxGraphSize; ++i)
            {
                for (int j = 0; j < MaxGraphSize; ++j)
                {
                    edge[i][j] = std::move(graph.edge[i][j]);
                }
            }

            // ����������� ������� �����
            graphSize = graph.graphSize;
            graph.graphSize = 0;
            /*std::cout << "Move assignment operator" << std::endl;*/
            return *this;
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
        if (weight == 0) throw "��� �� ����� ���� �������!";
        int pos1 = GetVertexPos(vertex1);
        int pos2 = GetVertexPos(vertex2);
        if (pos1 != -1 && pos2 != -1)
        {
            edge[pos1][pos2] = weight;
            //if (weight >= 0)
            //    
            //if (weight <= 0)
            //    edge[pos2][pos1] = -weight;
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
            for (int i = pos; i < graphSize - 1; i++)
            {
                for (int j = 0; j < graphSize; j++)
                {
                    edge[i][j] = edge[i + 1][j];
                }
            }
            for (int i = 0; i < graphSize; i++)
            {
                for (int j = pos; j < graphSize - 1; j++)
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
    /// ������ ������� ��������� � ������� �������� ������
    /// </summary>
    void PrintAdjacencyMatrix() const
    {
        // ����� �������� ������ ��� ������������ ���
        std::cout << "     ";
        for (int i = 0; i < graphSize; i++)
        {
            std::cout << std::setw(5) << vertexList[i];
        }
        std::cout << std::endl;

        // ����� �������� ������ � �������� ������� ���������
        for (int i = 0; i < graphSize; i++)
        {
            std::cout << std::setw(5) << vertexList[i];
            for (int j = 0; j < graphSize; j++)
            {
                std::cout << std::setw(5) << edge[i][j];
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
    /// ������� ��� ����� ����� ��������� - ���� �������� 0, ������, ��� ����� �����������.
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
        for (int i = 0; i < graphSize; i++)
        {
            for (int j = 0; j < graphSize; j++)
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
    /// ������� ������� - ���� �� ����� ���� ������� ������ ����
    /// </summary>
    /// <param name="vertex"></param>
    /// <returns></returns>
    vector<T> GetNeighbors(const T& vertex)
    {
        vector<T> neighbors;
        int pos = GetVertexPos(vertex);
        if (pos != -1)
        {
            for (int i = 0; i < graphSize; i++)
            {
                // ������� ������� �� vertex
                if (edge[pos][i] != 0 && pos != i)
                {
                    neighbors.push_back(vertexList[i]);
                }
                // ������� ������ � vertex
                if (edge[i][pos] != 0 && pos != i)
                {
                    neighbors.push_back(vertexList[i]);
                }
            }
        }
        // ���������� ������� ��� ��������
        sort(neighbors.begin(), neighbors.end());
        return neighbors;
    }

    /// <summary>
    /// ����� � �������
    /// </summary>
    /// <param name="beginVertex"></param>
    /// <returns></returns>
    vector<T> DepthFirstSearch(const T& vertex)
    {
        vector<T> visited;// ���������� ������� - ��������
        vector<bool> marked(graphSize, false);// ���������� ������� - �������
        // ������� ��������� ������� � ������ ������
        int pos = GetVertexPos(vertex);
        // ���� ��������� ������� �������, ��������� ����� � �������
        if (pos != -1)
        {
            DepthFirstSearch_(pos, marked, visited);
        }
        return visited;
    }

    /// <summary>
    /// ����� � ������
    /// </summary>
    /// <typeparam name="T"></typeparam>
    vector<T> BreadthFirstSearch(const T& beginVertex)
    {
        vector<T> visited;                      // ������ ��� ���������� ������
        vector<bool> marked(graphSize, false);  // ������ ��� ������� ���������� ������
        int pos = GetVertexPos(beginVertex);    // ����� ������� ��������� ������� � ������ ������
        // ���� ������� �������
        if (pos != -1)
        {
            queue<int> queue;// ������� ��� �������� ������
            marked[pos] = true;// �������� ��������� ������� ��� ���������� � �������� � �������
            queue.push(pos);

            // ���� ������ � ������
            while (!queue.empty())
            {
                // ��������� ������� �� �������
                int currVertex = queue.front();
                queue.pop();
                // ��������� ���������� ������� � ������ visited
                visited.push_back(vertexList[currVertex]);

                // ������� ������� ������
                for (int i = 0; i < graphSize; i++)
                {
                    // ���� ���������� ����� ����� ������� �������� � ������� �������� i
                    // � ������� ������� i ��� �� ���� ��������, �� �������� �� ��� ���������� � ��������� � �������
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
    // ����� ��������� ��� Graph
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

    // ������ �������
    Iterator<T> begin() const
    {
        return Iterator<T>(*this, 0);
    }

    // ��������� �������
    Iterator<T> end() const
    {
        return Iterator<T>(*this, graphSize);
    }

    // ����� ����������� ���� ���������� �������� �� ��������� ������� �� ���� ��������� ������ � �����
    vector<int> Dijkstra(int vertex) {
        // �������������� ���������� ��������������
        vector<int> distances(graphSize, numeric_limits<int>::max());
        // ���������� �� ��������� ������� ����� 0
        distances[vertex - 1] = 0;

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

        // ��������� ��������� ������� � ������������ �������, make_pair - ������������ ��� �������� ���� (����������, �������)
        //  � ���������� ���� ���� � ������������ �������
        pq.push(make_pair(0, vertex));

        //��������� ������ ���������� ��������, ���� ������������ ������� �� �����
        while (!pq.empty()) {
            //top - ������������ ��� ��������� ������ �� ����� ������� ���� (����������, �������)
            int currentDistance = pq.top().first;
            int currentNode = pq.top().second;
            pq.pop();

            if (currentDistance > distances[currentNode]) {
                continue; // ���� ������� ���������� ������, ���������� �������
            }

            // �������� �� ������� ��������
            // ���������� ����, � ������� �������� �� ���� ��������, ������� � ������� �������� currentNode. 
            // numVertices ������������ ����� ���������� ������ � �����.
            for (int neighbor = 0; neighbor < graphSize; ++neighbor) {
                // �������� ��� ����� ����� ������� �������� currentNode � ������� �������� neighbor �� ������� ��������� adjMatrix. 
                // ���� ��� ����� ����� 0, ��� ��������, ��� ����� ��������� ��� ������� ����� � �� ���������� ��� ������� �������.
                int edgeWeight = edge[currentNode][neighbor];
                if (edgeWeight != 0) {
                    //��������� ����� ���������� distance �� ��������� ������� �� ������� ������� ����� ������� �������.
                    // ��������� �������
                    int distance = currentDistance + edgeWeight;
                    // ���������, �������� �� ����� ���������� distance ������, 
                    // ��� ��� ��������� ���������� distances[neighbor] �� ������� ������� neighbor.
                    if (distance < distances[neighbor]) {
                        distances[neighbor] = distance;
                        // ��������� ���� (distance, neighbor) � ������������ ������� 
                        pq.push(make_pair(distance, neighbor));
                    }
                }
            }
        }
        return distances;
    }

    /// <summary>
    ///  ������ ����� � ��������� ����
    /// </summary>
    /// <param name="filename"></param>
    void FillFile(const string& filename)
    {
        ofstream file(filename);
        // �������� �� ��������
        if (!file.is_open())
        {
            throw "������ �������� �����";
        }


        file << "<����������_������> " << NumberOfVertices() << endl;
        int i = 0;
        for (Graph<int>::Iterator<int> it = begin(); it != end(); ++it)
        {
            file << "�������" << i << " " << *it << endl;
            i++;
        }

        file << "<����������_�����> " << NumberOfEdges() << endl;
        int edgeCount = 0;// ���������� �����
        /// ������ �� �������� (�� �������)
        for (int i = 0; i < NumberOfVertices(); i++)
        {
            for (int j = 0; j < NumberOfVertices(); j++)
            {
                // ����� ��� �����
                int weight = GetWeight(vertexList[i], vertexList[j]);
                if (weight != 0)// ���� ��� �� �������, �� ������ ������ �����
                {
                    file << "�����" << edgeCount << " " << "���" << edgeCount << " " << vertexList[i] << " " << vertexList[j] << " " << weight << endl;
                    edgeCount++;
                }
            }
        }
        file.close();
    }

    /// <summary>
    /// ������ ����� �� �����
    /// </summary>
    /// <param name="filename"></param>
    /// <returns></returns>
    void ReadFile(const string& filename)
    {
        ifstream file(filename);
        // �������� �� ��������
        if (!file.is_open())
        {
            throw "������ �������� �����";
        }

        string line;        // ��� ����������� ����������
        int vertices = 0;   // ���������� ������
        int edges = 0;      // ���������� ����� (��� ������)

        // ��������� ���������� ������, ��������� � ������ ������
        if (getline(file, line))
        {
            istringstream iss(line); // ������ ������ �� ������ ����� ������
            string token;            // ������� "�����"
            iss >> token;            // ���������� ������ "�����" - "<����������_������>"
            iss >> vertices;         // vertices = ���-�� ������
        }

        // ��������� ������� � �����
        for (int i = 0; i < vertices; i++)
        {
            if (getline(file, line))
            {
                istringstream iss(line);
                string token;
                int vertex;
                iss >> token; // ���������� "�������<i>"
                iss >> vertex;
                InsertVertex(vertex);
            }
        }

        // ��������� ���������� �����, ��������� � ������ ����� ������ (vertices+1)
        if (getline(file, line))
        {
            istringstream iss(line); // ���������� ���-�� ������
            string token;
            iss >> token;            // ���������� "<����������_�����>"
            iss >> edges;
        }

        // ��������� ����� � �����
        for (int i = 0; i < edges; i++)
        {
            if (getline(file, line))
            {
                istringstream iss(line);
                string token;
                T weight;
                int vertex1;
                int vertex2;
                iss >> token; // ���������� "�����<i>"
                iss >> token; // ���������� "���<i>"
                iss >> vertex1;
                iss >> vertex2;
                iss >> weight;
                InsertEdge(vertex1, vertex2, weight);
            }
        }
        file.close();
    }
};
    
   











///// ���������� ������ Graph
///// @author ������ �.�.
//#pragma once
//
//using namespace std;
//
//#include <vector>
//#include <queue>
//#include <iomanip>
//const int MaxGraphSize = 25;
//
//
///// <summary>
///// ����� ���� � ������������� ������������ ��������.
///// > E��� �������� ��� ������������ ����� -> ��� �������������
///// > ��� ������� ������ ����� � ������� ��������� ����������� ������ ������������� ��������. ���� ������������� -> 
///// -> ����������� ��������������� �� ������, �� �������� �������� ����
///// </summary>
///// <typeparam name="T"></typeparam>
//template <class T>
//class Graph
//{
//private:
//    // �������� ������ �������� ������ ������, ������� ���������
//    // � ������� ������ (����� ������) �����
//    vector<T> vertexList;
//    T edge[MaxGraphSize][MaxGraphSize];
//    int graphSize;
//
//    /// <summary>
//    /// �������� ��������������� ������
//    /// ����� ������� � �������
//    /// </summary>
//    /// <param name="L"></param>
//    /// <param name="vertex"></param>
//    /// <returns></returns>
//    int FindVertex(const vector<T>& L, const T& vertex)
//    {
//        for (int i = 0; i < L.size(); i++)
//        {
//            if (L[i] == vertex)
//            {
//                return i;
//            }
//        }
//        return -1;
//    }
//
//    /// <summary>
//    /// �������� ��������������� ������
//    /// �������
//    /// </summary>
//    /// <param name="vertex"></param>
//    /// <returns></returns>
//    int GetVertexPos(const T& vertex)
//    {
//        return FindVertex(vertexList, vertex);
//    }
//
//
//    /// <summary>
//    /// ����������� ��������������� ����� ������ � ������� 
//    /// </summary>
//    /// <param name="vertex"></param>
//    /// <param name="marked"></param>
//    /// <param name="visited"></param>
//    void DepthFirstSearch_(int vertex, vector<bool>& marked, vector<T>& visited)
//    {
//        marked[vertex] = true;                  // ������� ������� �������, ��� ����������
//        visited.push_back(vertexList[vertex]);  // ��������� ������� ������� � ������ ����������
//        for (int i = 0; i < graphSize; i++)     // ������� ������� ������
//        {
//            // ���� ���������� ����� ����� ������� �������� � ������� �������� 
//            // � ������� ������� i ��� �� ���� ��������
//            if (edge[vertex][i] != 0 && !marked[i])
//            {
//                // ���������� �������� ����� DepthFirstSearchHelper ��� ������� ������� i
//                DepthFirstSearch_(i, marked, visited);
//            }
//        }
//    }
//
//public:
//
//    /// <summary>
//    /// ����������� ��� ����������
//    /// </summary>
//    Graph()
//    {
//        graphSize = 0;
//        // ���������� ������
//        std::fill(edge[0], edge[0] + MaxGraphSize * MaxGraphSize, 0);
//
//        //for (int i = 0; i < MaxGraphSize; i++) /// memfill
//        //{
//        //    for (int j = 0; j < MaxGraphSize; j++)
//        //    {
//        //        edge[i][j] = 0;
//        //    }
//        //}
//    }
//
//    /// <summary>
//    /// ����������� � ���������� �������
//    /// </summary>
//    Graph(const T vertex)
//    {
//        graphSize = 0;
//        // ���������� ������
//        std::fill(edge[0], edge[0] + MaxGraphSize * MaxGraphSize, 0);
//
//        this->InsertVertex(vertex);
//        //for (int i = 0; i < MaxGraphSize; i++) /// memfill
//        //{
//        //    for (int j = 0; j < MaxGraphSize; j++)
//        //    {
//        //        edge[i][j] = 0;
//        //    }
//        //}
//    }
//
//    // ����������
//    ~Graph() {}
//
//    /// <summary>
//    /// ����������� �����������
//    /// </summary>
//    /// <param name="other"></param>
//    Graph(const Graph<T>& graph)
//    {
//        // ����������� ������ ������
//        vertexList = graph.vertexList;
//        // ���������� ������� �����
//        graphSize = graph.graphSize;
//        // ����������� ������� ���������
//        //std::memcpy(graph.edge, edge, graphSize * graphSize * sizeof(T));
//        //
//        for (int i = 0; i < MaxGraphSize; i++) /// memcpy
//        {
//            for (int j = 0; j < MaxGraphSize; j++)
//            {
//                edge[i][j] = graph.edge[i][j];
//            }
//        }
//        std::cout << "Copy constructor" << std::endl;
//    }
//
//    /// <summary>
//    /// ����������� �����������
//    /// </summary>
//    /// <param name="other"></param>
//    Graph(Graph<T>&& graph)
//    {
//        // ����������� ������ ������
//        vertexList = graph.vertexList;
//        graph.vertexList.clear();
//
//
//        // ����������� ������� ���������
//        for (int i = 0; i < MaxGraphSize; i++)
//        {
//            for (int j = 0; j < MaxGraphSize; j++)
//            {
//                edge[i][j] = graph.edge[i][j];
//            }
//        }
//        std::fill(graph.edge[0], graph.edge[0] + MaxGraphSize * MaxGraphSize, 0);
//        // ����������� ������� �����
//        graphSize = graph.graphSize;
//        graph.graphSize = 0;
//        std::cout << "Move constructor" << std::endl;
//    }
//
//    /// <summary>
//    /// �������� ������������ ������������
//    /// </summary>
//    /// <param name="other"></param>
//    /// <returns></returns>
//    Graph<T>& operator=(const Graph<T>& graph)
//    {
//        // ����������� ������ ������
//        vertexList = graph.vertexList;
//
//        // ����������� ������� ���������
//        for (int i = 0; i < MaxGraphSize; i++)
//        {
//            for (int j = 0; j < MaxGraphSize; j++)
//            {
//                edge[i][j] = graph.edge[i][j];
//            }
//        }
//
//        // ����������� ������� �����
//        graphSize = graph.graphSize;
//
//        return *this;
//    }
//
//    /// <summary>
//    /// �������� ������������ ������������
//    /// </summary>
//    /// <param name="other"></param>
//    /// <returns></returns>
//    Graph<T>& operator=(Graph<T>&& graph)
//    {
//        // ����������� ������ ������
//        vertexList = std::move(graph.vertexList);
//
//        // ����������� ������� ���������
//        for (int i = 0; i < MaxGraphSize; ++i)
//        {
//            for (int j = 0; j < MaxGraphSize; ++j)
//            {
//                edge[i][j] = std::move(graph.edge[i][j]);
//            }
//        }
//
//        // ����������� ������� �����
//        graphSize = std::move(graph.graphSize);
//
//        return *this;
//    }
//
//    /// <summary>
//    /// ������� ����
//    /// </summary>
//    /// <param name="vertex"></param>
//    void InsertVertex(const T& vertex)
//    {
//        if (graphSize < MaxGraphSize)
//        {
//            vertexList.push_back(vertex);
//            graphSize++;
//        }
//    }
//
//    /// <summary>
//    /// ������� ����� (���������)
//    /// </summary>
//    /// <param name="vertex1"></param>
//    /// <param name="vertex2"></param>
//    /// <param name="weight"></param>
//    void InsertEdge(const T& vertex1, const T& vertex2, int weight)
//    {
//        if (weight == 0) throw "��� �� ����� ���� �������!";
//        int pos1 = GetVertexPos(vertex1);
//        int pos2 = GetVertexPos(vertex2);
//        if (pos1 != -1 && pos2 != -1)
//        {
//            if (weight >= 0)
//                edge[pos1][pos2] = weight;
//            if (weight <= 0)
//                edge[pos2][pos1] = -weight;
//        }
//        //else throw "��� ������� ����� �� ������ ���!";
//    }
//
//    /// <summary>
//    /// ������� �������
//    /// </summary>
//    /// <param name="vertex"></param>
//    void DeleteVertex(const T& vertex)
//    {
//        int pos = GetVertexPos(vertex);
//        if (pos != -1)
//        {
//            vertexList.erase(vertexList.begin() + pos);
//            for (int i = pos; i < graphSize - 1; i++)
//            {
//                for (int j = 0; j < graphSize; j++)
//                {
//                    edge[i][j] = edge[i + 1][j];
//                }
//            }
//            for (int i = 0; i < graphSize; i++)
//            {
//                for (int j = pos; j < graphSize - 1; j++)
//                {
//                    edge[i][j] = edge[i][j + 1];
//                }
//            }
//            graphSize--;
//        }
//    }
//
//    /// <summary>
//    /// ������� �����
//    /// </summary>
//    /// <typeparam name="T"></typeparam>
//    void DeleteEdge(const T& vertex1, const T& vertex2)
//    {
//        int pos1 = GetVertexPos(vertex1);
//        int pos2 = GetVertexPos(vertex2);
//        if (pos1 != -1 && pos2 != -1)
//        {
//            edge[pos1][pos2] = 0;
//            edge[pos2][pos1] = 0;
//        }
//    }
//
//    /// <summary>
//    /// ������ ������� ��������� � ������� �������� ������
//    /// </summary>
//    void PrintAdjacencyMatrix() const
//    {
//        // ����� �������� ������ ��� ������������ ���
//        std::cout << "   ";
//        for (int i = 0; i < graphSize; i++)
//        {
//            std::cout << std::setw(3) << vertexList[i];
//        }
//        std::cout << std::endl;
//
//        // ����� �������� ������ � �������� ������� ���������
//        for (int i = 0; i < graphSize; i++)
//        {
//            std::cout << std::setw(3) << vertexList[i];
//            for (int j = 0; j < graphSize; j++)
//            {
//                std::cout << std::setw(3) << edge[i][j];
//            }
//            std::cout << std::endl;
//        }
//    }
//
//    /// <summary>
//    /// ������ �� ����
//    /// </summary>
//    /// <returns></returns>
//    int isEmpty() const
//    {
//        return graphSize == 0;
//    }
//
//    /// <summary>
//    /// ������ �� ����
//    /// </summary>
//    /// <returns></returns>
//    int isFull() const
//    {
//        return graphSize == MaxGraphSize;
//    }
//
//    /// <summary>
//    /// ���������� ������
//    /// </summary>
//    /// <returns></returns>
//    int NumberOfVertices() const
//    {
//        return graphSize;
//    }
//
//
//    /// <summary>
//    /// ������� ��� ����� ����� ���������
//    /// </summary>
//    /// <param name="vertex1"></param>
//    /// <param name="vertex2"></param>
//    /// <returns></returns>
//    int GetWeight(const T& vertex1, const T& vertex2)
//    {
//        int pos1 = GetVertexPos(vertex1);
//        int pos2 = GetVertexPos(vertex2);
//        if (pos1 != -1 && pos2 != -1)
//        {
//            return edge[pos1][pos2];
//        }
//        throw "����� ����� ���";
//    }
//
//    /// <summary>
//    /// ����� �����
//    /// </summary>
//    /// <returns></returns>
//    int NumberOfEdges() const
//    {
//        int edgeCount = 0;
//        for (int i = 0; i < graphSize; i++)
//        {
//            for (int j = i; j < graphSize; j++)
//            {
//                if (edge[i][j] != 0)
//                {
//                    edgeCount++;
//                }
//            }
//        }
//        return edgeCount;
//    }
//
//    /// <summary>
//    /// ������� ������� - ���� �� ����� ���� ������� ������ ����
//    /// </summary>
//    /// <param name="vertex"></param>
//    /// <returns></returns>
//    vector<T> GetNeighbors(const T& vertex)
//    {
//        vector<T> neighbors;
//        int pos = GetVertexPos(vertex);
//        if (pos != -1)
//        {
//            for (int i = 0; i < graphSize; i++)
//            {
//                // ������� ������� �� vertex
//                if (edge[pos][i] != 0 && pos != i)
//                {
//                    neighbors.push_back(vertexList[i]);
//                }
//                // ������� ������ � vertex
//                if (edge[i][pos] != 0 && pos != i)
//                {
//                    neighbors.push_back(vertexList[i]);
//                }
//            }
//        }
//        // ���������� ������� ��� ��������
//        sort(neighbors.begin(), neighbors.end());
//        return neighbors;
//    }
//
//    /// <summary>
//    /// ����� � �������
//    /// </summary>
//    /// <param name="beginVertex"></param>
//    /// <returns></returns>
//    vector<T> DepthFirstSearch(const T& vertex)
//    {
//        vector<T> visited;// ���������� ������� - ��������
//        vector<bool> marked(graphSize, false);// ���������� ������� - �������
//        // ������� ��������� ������� � ������ ������
//        int pos = GetVertexPos(vertex);
//        // ���� ��������� ������� �������, ��������� ����� � �������
//        if (pos != -1)
//        {
//            DepthFirstSearch_(pos, marked, visited);
//        }
//        return visited;
//    }
//
//    /// <summary>
//    /// ����� � ������
//    /// </summary>
//    /// <typeparam name="T"></typeparam>
//    vector<T> BreadthFirstSearch(const T& beginVertex)
//    {
//        vector<T> visited;                      // ������ ��� ���������� ������
//        vector<bool> marked(graphSize, false);  // ������ ��� ������� ���������� ������
//        int pos = GetVertexPos(beginVertex);    // ����� ������� ��������� ������� � ������ ������
//        // ���� ������� �������
//        if (pos != -1)
//        {
//            queue<int> queue;// ������� ��� �������� ������
//            marked[pos] = true;// �������� ��������� ������� ��� ���������� � �������� � �������
//            queue.push(pos);
//
//            // ���� ������ � ������
//            while (!queue.empty())
//            {
//                // ��������� ������� �� �������
//                int currVertex = queue.front();
//                queue.pop();
//                // ��������� ���������� ������� � ������ visited
//                visited.push_back(vertexList[currVertex]);
//
//                // ������� ������� ������
//                for (int i = 0; i < graphSize; i++)
//                {
//                    // ���� ���������� ����� ����� ������� �������� � ������� �������� i
//                    // � ������� ������� i ��� �� ���� ��������, �� �������� �� ��� ���������� � ��������� � �������
//                    if (edge[currVertex][i] != 0 && !marked[i])
//                    {
//                        marked[i] = true;
//                        queue.push(i);
//                    }
//                }
//            }
//        }
//        return visited;
//    }
//
//    template <class F>
//    // ����� ��������� ��� Graph
//    class Iterator
//    {
//    private:
//        const Graph<F>& graph;
//        int currentIndex;
//
//    public:
//        Iterator(const Graph<F>& g, int index) : graph(g), currentIndex(index) {}
//
//        // ���������� ��������� ������������� *
//        F operator*() const
//        {
//            return graph.vertexList[currentIndex];
//        }
//
//        // ���������� ��������� ���������� ����������� ++
//        Iterator<F>& operator++()
//        {
//            ++currentIndex;
//            return *this;
//        }
//
//        // ���������� ��������� ���������� ������������ ++
//        Iterator<F> operator++(int)
//        {
//            Iterator<F> temp = *this;
//            ++(*this);
//            return temp;
//        }
//
//        // ���������� ��������� ��������� ==
//        bool operator==(const Iterator<F>& other) const
//        {
//            return currentIndex == other.currentIndex;
//        }
//
//        // ���������� ��������� ��������� !=
//        bool operator!=(const Iterator<F>& other) const
//        {
//            return !(*this == other);
//        }
//    };
//
//    // ������ �������
//    Iterator<T> begin() const
//    {
//        return Iterator<T>(*this, 0);
//    }
//
//    // ��������� �������
//    Iterator<T> end() const
//    {
//        return Iterator<T>(*this, graphSize);
//    }
//};



