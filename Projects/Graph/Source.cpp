//template <class T>
//class Graph
//{
//private:
//    vector<T> vertexList;
//    T edge[MaxGraphSize][MaxGraphSize];
//    int graphSize;
//
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
//    int GetVertexPos(const T& vertex)
//    {
//        return FindVertex(vertexList, vertex);
//    }
//
//    void DepthFirstSearch_(int vertex, vector<bool>& marked, vector<T>& visited)
//    {
//        marked[vertex] = true;                  // ������� ������� �������, ��� ����������
//        visited.push_back(vertexList[vertex]);  // ��������� ������� ������� � ������ ����������
//        for (int i = 0; i < graphSize; i++)     // ������� ������� ������
//        {
//
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
//    Graph()
//    {
//        graphSize = 0;
//        // ���������� ������
//        std::fill(edge[0], edge[0] + MaxGraphSize * MaxGraphSize, 0);
//    }
//    Graph(const T vertex)
//    {
//        graphSize = 0;
//        // ���������� ������
//        std::fill(edge[0], edge[0] + MaxGraphSize * MaxGraphSize, 0);
//        // ������� �������
//        this->InsertVertex(vertex);
//        //std::cout << "Constructor w/ 1 parameter";
//    }
//    template <class T>
//    class Graph
//    {
//    private:
//
//        vector<T> vertexList;
//        T edge[MaxGraphSize][MaxGraphSize];
//        int graphSize;
//
//        int FindVertex(const vector<T>& L, const T& vertex)
//        {
//            for (int i = 0; i < L.size(); i++)
//            {
//                if (L[i] == vertex)
//                {
//                    return i;
//                }
//            }
//            return -1;
//        }
//
//        int GetVertexPos(const T& vertex)
//        {
//            return FindVertex(vertexList, vertex);
//        }
//
//        void DepthFirstSearch_(int vertex, vector<bool>& marked, vector<T>& visited)
//        {
//            marked[vertex] = true;                  // ������� ������� �������, ��� ����������
//            visited.push_back(vertexList[vertex]);  // ��������� ������� ������� � ������ ����������
//            for (int i = 0; i < graphSize; i++)     // ������� ������� ������
//            {
//                // ���� ���������� ����� ����� ������� �������� � ������� �������� 
//                // � ������� ������� i ��� �� ���� ��������
//                if (edge[vertex][i] != 0 && !marked[i])
//                {
//                    // ���������� �������� ����� DepthFirstSearchHelper ��� ������� ������� i
//                    DepthFirstSearch_(i, marked, visited);
//                }
//            }
//        }
//
//    public:
//
//        Graph()
//        {
//            graphSize = 0;
//            // ���������� ������
//            std::fill(edge[0], edge[0] + MaxGraphSize * MaxGraphSize, 0);
//
//            //std::cout << "Constructor w/o parameters";
//        }
//
//        Graph(const T vertex)
//        {
//            graphSize = 0;
//            // ���������� ������
//            std::fill(edge[0], edge[0] + MaxGraphSize * MaxGraphSize, 0);
//            // ������� �������
//            this->InsertVertex(vertex);
//            //std::cout << "Constructor w/ 1 parameter";
//        }
//
//        int NumberOfVertices() const
//        {
//            return graphSize;
//        }
//
//        int GetWeight(const T& vertex1, const T& vertex2)
//        {
//            int pos1 = GetVertexPos(vertex1);
//            int pos2 = GetVertexPos(vertex2);
//            if (pos1 != -1 && pos2 != -1)
//            {
//                return edge[pos1][pos2];
//            }
//            throw "����� ����� ���";
//        }
//
//        int NumberOfEdges() const
//        {
//            int edgeCount = 0;
//            for (int i = 0; i < graphSize; i++)
//            {
//                for (int j = i; j < graphSize; j++)
//                {
//                    if (edge[i][j] != 0)
//                    {
//                        edgeCount++;
//                    }
//                }
//            }
//            return edgeCount;
//        }
//
//
//        vector<T> GetNeighbors(const T& vertex)
//        {
//            vector<T> neighbors;
//            int pos = GetVertexPos(vertex);
//            if (pos != -1)
//            {
//                for (int i = 0; i < graphSize; i++)
//                {
//                    // ������� ������� �� vertex
//                    if (edge[pos][i] != 0 && pos != i)
//                    {
//                        neighbors.push_back(vertexList[i]);
//                    }
//                    // ������� ������ � vertex
//                    if (edge[i][pos] != 0 && pos != i)
//                    {
//                        neighbors.push_back(vertexList[i]);
//                    }
//                }
//            }
//            // ���������� ������� ��� ��������
//            sort(neighbors.begin(), neighbors.end());
//            return neighbors;
//        }