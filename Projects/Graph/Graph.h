/// Реализация класса Graph
/// @author Будаев Г.Б.
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
/// класс граф с фиксированным максимальным размером.
/// > Eсли вставить уже существующее ребро -> Оно перезапишется
/// > При вставке нового ребра в матрицу смежности вставляется только положительное значение. Если отрицательное -> 
/// -> вставляется противоположное по модулю, но меняется источник ребра. 
/// Если вес ребра 0 - значит оно отсутсвует.
/// </summary>
/// <typeparam name="T"></typeparam>
template <class T>
class Graph
{
private:
    // Основные данные включают список вершин, матрицу смежности
    // и текущий размер (число вершин) графа
    vector<T> vertexList;
    T edge[MaxGraphSize][MaxGraphSize];
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
    void DepthFirstSearch_(int vertex, vector<bool>& marked, vector<T>& visited)
    {
        marked[vertex] = true;                  // пометка текущей вершины, как посещенной
        visited.push_back(vertexList[vertex]);  // добавляем текущую вершину в вектор посещенных
        for (int i = 0; i < graphSize; i++)     // перебор смежных вершин
        {
            // если существует ребро между текущей вершиной и смежной вершиной 
            // и смежная вершина i еще не была посещена
            if (edge[vertex][i] != 0 && !marked[i])
            {
                // рекурсивно вызываем метод DepthFirstSearchHelper для смежной вершины i
                DepthFirstSearch_(i, marked, visited);
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
        // заполнение нулями
        std::fill(edge[0], edge[0] + MaxGraphSize * MaxGraphSize, 0);

        //std::cout << "Constructor w/o parameters";
    }

    /// <summary>
    /// конструктор с параметром вершина
    /// </summary>
    Graph(const T vertex)
    {
        graphSize = 0;
        // заполнение нулями
        std::fill(edge[0], edge[0] + MaxGraphSize * MaxGraphSize, 0);
        // вставка вектора
        this->InsertVertex(vertex);
        //std::cout << "Constructor w/ 1 parameter";
    }

    // деструктор
    ~Graph() {}

    /// <summary>
    /// Конструктор копирования
    /// </summary>
    /// <param name="other"></param>
    Graph(const Graph<T>& graph)
    {
        // копирование списка вершин
        vertexList = graph.vertexList;
        // опирование размера графа
        graphSize = graph.graphSize;
        // копирование матрицы смежности
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
    /// конструктор перемещения
    /// </summary>
    /// <param name="other"></param>
    Graph(Graph<T>&& graph)
    {
        // перемещение списка вершин
        vertexList = graph.vertexList;
        graph.vertexList.clear();


        // перемещение матрицы смежности
        for (int i = 0; i < MaxGraphSize; i++)
        {
            for (int j = 0; j < MaxGraphSize; j++)
            {
                edge[i][j] = graph.edge[i][j];
            }
        }
        std::fill(graph.edge[0], graph.edge[0] + MaxGraphSize * MaxGraphSize, 0);
        // перемещение размера графа
        graphSize = graph.graphSize;
        graph.graphSize = 0;
        //std::cout << "Move constructor" << std::endl;
    }

    /// <summary>
    /// оператор присваивания копированием
    /// </summary>
    /// <param name="other"></param>
    /// <returns></returns>
    Graph<T>& operator=(const Graph<T>& graph)
    {
        // копирование списка вершин
        vertexList = graph.vertexList;

        // копирование матрицы смежности
        for (int i = 0; i < MaxGraphSize; i++)
        {
            for (int j = 0; j < MaxGraphSize; j++)
            {
                edge[i][j] = graph.edge[i][j];
            }
        }

        // копирование размера графа
        graphSize = graph.graphSize;
        /*std::cout << "Assignment operator" << std::endl;*/
        return *this;
    }

    /// <summary>
    /// оператор присваивания перемещением
    /// </summary>
    /// <param name="other"></param>
    /// <returns></returns>
    Graph<T>& operator=(Graph<T>&& graph)
    {
        // проверка на самоприсваивание
        if (this != &graph)
        {
            // перемещение списка вершин
            vertexList = std::move(graph.vertexList);

            // перемещение матрицы смежности
            for (int i = 0; i < MaxGraphSize; ++i)
            {
                for (int j = 0; j < MaxGraphSize; ++j)
                {
                    edge[i][j] = std::move(graph.edge[i][j]);
                }
            }

            // перемещение размера графа
            graphSize = graph.graphSize;
            graph.graphSize = 0;
            /*std::cout << "Move assignment operator" << std::endl;*/
            return *this;
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
            edge[pos1][pos2] = weight;
            //if (weight >= 0)
            //    
            //if (weight <= 0)
            //    edge[pos2][pos1] = -weight;
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
        std::cout << "     ";
        for (int i = 0; i < graphSize; i++)
        {
            std::cout << std::setw(5) << vertexList[i];
        }
        std::cout << std::endl;

        // Вывод значений вершин и значений матрицы смежности
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
    /// вернуть вес ребра между вершинами - если вернулся 0, значит, что ребро отсутствует.
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
            for (int i = 0; i < graphSize; i++)
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
            DepthFirstSearch_(pos, marked, visited);
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
                for (int i = 0; i < graphSize; i++)
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
    // Класс итератора для Graph
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

    // поиск кратчайшего пути алгоритмом Дейкстры от начальной вершины до всех остальных вершин в графе
    vector<int> Dijkstra(int vertex) {
        // Инициализируем расстояния бесконечностью
        vector<int> distances(graphSize, numeric_limits<int>::max());
        // Расстояние до начальной вершины равно 0
        distances[vertex - 1] = 0;

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

        // Добавляем начальную вершину в приоритетную очередь, make_pair - используется для создания пары (расстояние, вершина)
        //  и добавления этой пары в приоритетную очередь
        pq.push(make_pair(0, vertex));

        //выполняем нужное количество итераций, пока приоритетную очередь не пуста
        while (!pq.empty()) {
            //top - используется для получения ссылки на самую верхнюю пару (расстояние, вершина)
            int currentDistance = pq.top().first;
            int currentNode = pq.top().second;
            pq.pop();

            if (currentDistance > distances[currentNode]) {
                continue; // Если текущее расстояние больше, игнорируем вершину
            }

            // Проходим по смежным вершинам
            // начинается цикл, в котором проходим по всем вершинам, смежным с текущей вершиной currentNode. 
            // numVertices представляет общее количество вершин в графе.
            for (int neighbor = 0; neighbor < graphSize; ++neighbor) {
                // получаем вес ребра между текущей вершиной currentNode и смежной вершиной neighbor из матрицы смежности adjMatrix. 
                // Если вес ребра равен 0, это означает, что между вершинами нет прямого ребра и мы пропускаем эту смежную вершину.
                int edgeWeight = edge[currentNode][neighbor];
                if (edgeWeight != 0) {
                    //вычисляем новое расстояние distance от начальной вершины до смежной вершины через текущую вершину.
                    // Суммируем текущее
                    int distance = currentDistance + edgeWeight;
                    // проверяем, является ли новое расстояние distance меньше, 
                    // чем уже известное расстояние distances[neighbor] до смежной вершины neighbor.
                    if (distance < distances[neighbor]) {
                        distances[neighbor] = distance;
                        // добавляем пару (distance, neighbor) в приоритетную очередь 
                        pq.push(make_pair(distance, neighbor));
                    }
                }
            }
        }
        return distances;
    }

    /// <summary>
    ///  Печать графа в текстовый файл
    /// </summary>
    /// <param name="filename"></param>
    void FillFile(const string& filename)
    {
        ofstream file(filename);
        // проверка на открытие
        if (!file.is_open())
        {
            throw "Ошибка открытия файла";
        }


        file << "<Количество_вершин> " << NumberOfVertices() << endl;
        int i = 0;
        for (Graph<int>::Iterator<int> it = begin(); it != end(); ++it)
        {
            file << "Вершина" << i << " " << *it << endl;
            i++;
        }

        file << "<Количество_ребер> " << NumberOfEdges() << endl;
        int edgeCount = 0;// количество ребер
        /// проход по вершинам (по матрице)
        for (int i = 0; i < NumberOfVertices(); i++)
        {
            for (int j = 0; j < NumberOfVertices(); j++)
            {
                // найти вес ребра
                int weight = GetWeight(vertexList[i], vertexList[j]);
                if (weight != 0)// если вес не нулевой, то печать данных ребра
                {
                    file << "Ребро" << edgeCount << " " << "Вес" << edgeCount << " " << vertexList[i] << " " << vertexList[j] << " " << weight << endl;
                    edgeCount++;
                }
            }
        }
        file.close();
    }

    /// <summary>
    /// Чтение графа из файла
    /// </summary>
    /// <param name="filename"></param>
    /// <returns></returns>
    void ReadFile(const string& filename)
    {
        ifstream file(filename);
        // проверка на открытие
        if (!file.is_open())
        {
            throw "Ошибка открытия файла";
        }

        string line;        // для построчного считывания
        int vertices = 0;   // количество вершин
        int edges = 0;      // количество ребер (для циклов)

        // Считываем количество вершин, указанное в первой строке
        if (getline(file, line))
        {
            istringstream iss(line); // чтение данных из строки через пробел
            string token;            // текущее "слово"
            iss >> token;            // Пропускаем первое "слово" - "<Количество_вершин>"
            iss >> vertices;         // vertices = кол-во вершин
        }

        // Считываем вершины в цикле
        for (int i = 0; i < vertices; i++)
        {
            if (getline(file, line))
            {
                istringstream iss(line);
                string token;
                int vertex;
                iss >> token; // Пропускаем "Вершина<i>"
                iss >> vertex;
                InsertVertex(vertex);
            }
        }

        // Считываем количество ребер, указанное в строке после вершин (vertices+1)
        if (getline(file, line))
        {
            istringstream iss(line); // аналогично кол-ву вершин
            string token;
            iss >> token;            // Пропускаем "<Количество_ребер>"
            iss >> edges;
        }

        // Считываем ребра в цикле
        for (int i = 0; i < edges; i++)
        {
            if (getline(file, line))
            {
                istringstream iss(line);
                string token;
                T weight;
                int vertex1;
                int vertex2;
                iss >> token; // Пропускаем "Ребро<i>"
                iss >> token; // Пропускаем "Вес<i>"
                iss >> vertex1;
                iss >> vertex2;
                iss >> weight;
                InsertEdge(vertex1, vertex2, weight);
            }
        }
        file.close();
    }
};
    
   











///// Реализация класса Graph
///// @author Будаев Г.Б.
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
///// класс граф с фиксированным максимальным размером.
///// > Eсли вставить уже существующее ребро -> Оно перезапишется
///// > При вставке нового ребра в матрицу смежности вставляется только положительное значение. Если отрицательное -> 
///// -> вставляется противоположное по модулю, но меняется источник дуги
///// </summary>
///// <typeparam name="T"></typeparam>
//template <class T>
//class Graph
//{
//private:
//    // Основные данные включают список вершин, матрицу смежности
//    // и текущий размер (число вершин) графа
//    vector<T> vertexList;
//    T edge[MaxGraphSize][MaxGraphSize];
//    int graphSize;
//
//    /// <summary>
//    /// закрытые вспомогательные методы
//    /// поиск вершины в массиве
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
//    /// закрытые вспомогательные методы
//    /// позиция
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
//    /// рекурсивный вспомогательный метод обхода в глубину 
//    /// </summary>
//    /// <param name="vertex"></param>
//    /// <param name="marked"></param>
//    /// <param name="visited"></param>
//    void DepthFirstSearch_(int vertex, vector<bool>& marked, vector<T>& visited)
//    {
//        marked[vertex] = true;                  // пометка текущей вершины, как посещенной
//        visited.push_back(vertexList[vertex]);  // добавляем текущую вершину в вектор посещенных
//        for (int i = 0; i < graphSize; i++)     // перебор смежных вершин
//        {
//            // если существует ребро между текущей вершиной и смежной вершиной 
//            // и смежная вершина i еще не была посещена
//            if (edge[vertex][i] != 0 && !marked[i])
//            {
//                // рекурсивно вызываем метод DepthFirstSearchHelper для смежной вершины i
//                DepthFirstSearch_(i, marked, visited);
//            }
//        }
//    }
//
//public:
//
//    /// <summary>
//    /// конструктор без параметров
//    /// </summary>
//    Graph()
//    {
//        graphSize = 0;
//        // заполнение нулями
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
//    /// конструктор с параметром вершина
//    /// </summary>
//    Graph(const T vertex)
//    {
//        graphSize = 0;
//        // заполнение нулями
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
//    // деструктор
//    ~Graph() {}
//
//    /// <summary>
//    /// Конструктор копирования
//    /// </summary>
//    /// <param name="other"></param>
//    Graph(const Graph<T>& graph)
//    {
//        // копирование списка вершин
//        vertexList = graph.vertexList;
//        // опирование размера графа
//        graphSize = graph.graphSize;
//        // копирование матрицы смежности
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
//    /// конструктор перемещения
//    /// </summary>
//    /// <param name="other"></param>
//    Graph(Graph<T>&& graph)
//    {
//        // перемещение списка вершин
//        vertexList = graph.vertexList;
//        graph.vertexList.clear();
//
//
//        // перемещение матрицы смежности
//        for (int i = 0; i < MaxGraphSize; i++)
//        {
//            for (int j = 0; j < MaxGraphSize; j++)
//            {
//                edge[i][j] = graph.edge[i][j];
//            }
//        }
//        std::fill(graph.edge[0], graph.edge[0] + MaxGraphSize * MaxGraphSize, 0);
//        // перемещение размера графа
//        graphSize = graph.graphSize;
//        graph.graphSize = 0;
//        std::cout << "Move constructor" << std::endl;
//    }
//
//    /// <summary>
//    /// оператор присваивания копированием
//    /// </summary>
//    /// <param name="other"></param>
//    /// <returns></returns>
//    Graph<T>& operator=(const Graph<T>& graph)
//    {
//        // копирование списка вершин
//        vertexList = graph.vertexList;
//
//        // копирование матрицы смежности
//        for (int i = 0; i < MaxGraphSize; i++)
//        {
//            for (int j = 0; j < MaxGraphSize; j++)
//            {
//                edge[i][j] = graph.edge[i][j];
//            }
//        }
//
//        // копирование размера графа
//        graphSize = graph.graphSize;
//
//        return *this;
//    }
//
//    /// <summary>
//    /// оператор присваивания перемещением
//    /// </summary>
//    /// <param name="other"></param>
//    /// <returns></returns>
//    Graph<T>& operator=(Graph<T>&& graph)
//    {
//        // перемещение списка вершин
//        vertexList = std::move(graph.vertexList);
//
//        // перемещение матрицы смежности
//        for (int i = 0; i < MaxGraphSize; ++i)
//        {
//            for (int j = 0; j < MaxGraphSize; ++j)
//            {
//                edge[i][j] = std::move(graph.edge[i][j]);
//            }
//        }
//
//        // перемещение размера графа
//        graphSize = std::move(graph.graphSize);
//
//        return *this;
//    }
//
//    /// <summary>
//    /// вставка узла
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
//    /// вставка ребра (установка)
//    /// </summary>
//    /// <param name="vertex1"></param>
//    /// <param name="vertex2"></param>
//    /// <param name="weight"></param>
//    void InsertEdge(const T& vertex1, const T& vertex2, int weight)
//    {
//        if (weight == 0) throw "Вес не может быть нулевым!";
//        int pos1 = GetVertexPos(vertex1);
//        int pos2 = GetVertexPos(vertex2);
//        if (pos1 != -1 && pos2 != -1)
//        {
//            if (weight >= 0)
//                edge[pos1][pos2] = weight;
//            if (weight <= 0)
//                edge[pos2][pos1] = -weight;
//        }
//        //else throw "Как минимум одной из вершин нет!";
//    }
//
//    /// <summary>
//    /// удалить вершину
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
//    /// удалить ребро
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
//    /// печать матрицы смежности с выводом значений вершин
//    /// </summary>
//    void PrintAdjacencyMatrix() const
//    {
//        // Вывод значений вершин для вертикальной оси
//        std::cout << "   ";
//        for (int i = 0; i < graphSize; i++)
//        {
//            std::cout << std::setw(3) << vertexList[i];
//        }
//        std::cout << std::endl;
//
//        // Вывод значений вершин и значений матрицы смежности
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
//    /// пустой ли граф
//    /// </summary>
//    /// <returns></returns>
//    int isEmpty() const
//    {
//        return graphSize == 0;
//    }
//
//    /// <summary>
//    /// полный ли граф
//    /// </summary>
//    /// <returns></returns>
//    int isFull() const
//    {
//        return graphSize == MaxGraphSize;
//    }
//
//    /// <summary>
//    /// количество вершин
//    /// </summary>
//    /// <returns></returns>
//    int NumberOfVertices() const
//    {
//        return graphSize;
//    }
//
//
//    /// <summary>
//    /// вернуть вес ребра между вершинами
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
//        throw "Такой связи нет";
//    }
//
//    /// <summary>
//    /// число ребер
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
//    /// вернуть соседей - узел не может быть соседом самому себе
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
//                // которые выходят из vertex
//                if (edge[pos][i] != 0 && pos != i)
//                {
//                    neighbors.push_back(vertexList[i]);
//                }
//                // которые входят в vertex
//                if (edge[i][pos] != 0 && pos != i)
//                {
//                    neighbors.push_back(vertexList[i]);
//                }
//            }
//        }
//        // сортировка вектора для удобства
//        sort(neighbors.begin(), neighbors.end());
//        return neighbors;
//    }
//
//    /// <summary>
//    /// обход в глубину
//    /// </summary>
//    /// <param name="beginVertex"></param>
//    /// <returns></returns>
//    vector<T> DepthFirstSearch(const T& vertex)
//    {
//        vector<T> visited;// посещенные вершины - значения
//        vector<bool> marked(graphSize, false);// посещенные вершины - отметки
//        // позиция начальной вершины в списке вершин
//        int pos = GetVertexPos(vertex);
//        // если начальная вершина найдена, выполняем обход в глубину
//        if (pos != -1)
//        {
//            DepthFirstSearch_(pos, marked, visited);
//        }
//        return visited;
//    }
//
//    /// <summary>
//    /// обход в ширину
//    /// </summary>
//    /// <typeparam name="T"></typeparam>
//    vector<T> BreadthFirstSearch(const T& beginVertex)
//    {
//        vector<T> visited;                      // вектор для посещенных вершин
//        vector<bool> marked(graphSize, false);  // вектор для отметки посещенных вершин
//        int pos = GetVertexPos(beginVertex);    // Поиск позиции начальной вершины в списке вершин
//        // если вершина найдена
//        if (pos != -1)
//        {
//            queue<int> queue;// очередь для хранения вершин
//            marked[pos] = true;// отмечаем начальную вершину как посещенную и помещаем в очередь
//            queue.push(pos);
//
//            // цикл обхода в ширину
//            while (!queue.empty())
//            {
//                // извлекаем вершину из очереди
//                int currVertex = queue.front();
//                queue.pop();
//                // добавляем посещенную вершину в вектор visited
//                visited.push_back(vertexList[currVertex]);
//
//                // перебор смежных вершин
//                for (int i = 0; i < graphSize; i++)
//                {
//                    // если существует ребро между текущей вершиной и смежной вершиной i
//                    // и смежная вершина i еще не была посещена, то отмечаем ее как посещенную и добавляем в очередь
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
//    // Класс итератора для Graph
//    class Iterator
//    {
//    private:
//        const Graph<F>& graph;
//        int currentIndex;
//
//    public:
//        Iterator(const Graph<F>& g, int index) : graph(g), currentIndex(index) {}
//
//        // Перегрузка оператора разыменования *
//        F operator*() const
//        {
//            return graph.vertexList[currentIndex];
//        }
//
//        // Перегрузка оператора инкремента префиксного ++
//        Iterator<F>& operator++()
//        {
//            ++currentIndex;
//            return *this;
//        }
//
//        // Перегрузка оператора инкремента постфиксного ++
//        Iterator<F> operator++(int)
//        {
//            Iterator<F> temp = *this;
//            ++(*this);
//            return temp;
//        }
//
//        // Перегрузка оператора сравнения ==
//        bool operator==(const Iterator<F>& other) const
//        {
//            return currentIndex == other.currentIndex;
//        }
//
//        // Перегрузка оператора сравнения !=
//        bool operator!=(const Iterator<F>& other) const
//        {
//            return !(*this == other);
//        }
//    };
//
//    // первый элемент
//    Iterator<T> begin() const
//    {
//        return Iterator<T>(*this, 0);
//    }
//
//    // последний элемент
//    Iterator<T> end() const
//    {
//        return Iterator<T>(*this, graphSize);
//    }
//};



