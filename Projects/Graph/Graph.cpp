﻿/// Работа с классом Graph
/// @author Будаев Г.Б.
#include <iostream>
#include "Graph.h"
#include "Test.h"

using namespace std;

int main()
{
    setlocale(LC_ALL, "ru");
    try {
        // Создание графа
        Graph<int> graph;

        // Добавление вершин и ребер в граф
        graph.InsertVertex(0);
        graph.InsertVertex(1);
        graph.InsertVertex(2);
        graph.InsertVertex(3);

        graph.InsertEdge(0, 1, 4);
        graph.InsertEdge(0, 0, 100);
        graph.InsertEdge(0, 2, 1);
        graph.InsertEdge(2, 1, 2);
        graph.InsertEdge(1, 3, 5);



        graph.PrintAdjacencyMatrix();

        

        vector<int> way = graph.FindShortestDistances(1);


        for (const auto& it : way) {
            cout << it << endl;
        }

        testFindShortest();
    }

    catch (const char* error_message) {
        cout << endl << error_message << endl;
    }
}

///// Работа с классом Graph
///// @author Будаев Г.Б.
//#include <iostream>
//#include "Graph.h"
//
//using namespace std;
//
//
//int main()
//{
//    setlocale(LC_ALL, "ru");
//    try {
//        //Graph<int>* g1 = new Graph<int>();
//
//        //g1->InsertVertex(2);
//        //g1->InsertVertex(4);
//        ////g1->InsertVertex(7);
//        ////g1->InsertVertex(9);
//        ////g1->InsertVertex(10);
//        ////g1->InsertEdge(2, 4, 1);
//        ////g1->InsertEdge(4, 7, 15);
//        ////g1->InsertEdge(2, 7, 10);
//        ////g1->InsertEdge(7, 10, 1);
//        ////g1->InsertEdge(2, 9, 9);
//        //g1->InsertEdge(2, 4, 2);
//
//
//
//        //// вывод матрицы смежности
//        //vector<vector<int>> matr;
//        //g1->PrintAdjacencyMatrix();
//
//        //Graph<int>* g2 = new Graph<int>();
//        //g2->InsertVertex(1);
//        //g2->InsertVertex(2);
//        //g2->InsertVertex(4);
//        //g2->InsertVertex(5);
//        //g2->InsertVertex(3);
//        //g2->InsertVertex(6);
//        //g2->InsertEdge(1, 2, 5);
//        ////g2->InsertEdge(1, 1, 5);
//        //g2->InsertEdge(1, 4, 2);
//        //g2->InsertEdge(2, 3, 7);
//        //g2->InsertEdge(1, 5, -20);
//
//        //cout << g2->NumberOfVertices() << endl;
//        //cout << g2->NumberOfEdges() << endl;
//
//        //// вывод матрицы смежности
//        //g2->PrintAdjacencyMatrix();
//
//        //std::vector<int> res3= g2->GetNeighbors(1);
//
//        //cout << "Соседи 1: ";
//        //for (const auto& it : res3) {
//        //    cout << it << " ";
//        //}
//
//        ///// Проход в глубину
//        //cout << endl << "Проход в глубину: ";
//        //vector<int> res = g2->DepthFirstSearch(1);
//        //for (const auto& it : res) {
//        //    cout << it << " ";
//        //}
//
//
//        ///// Проход в ширину
//        //cout << endl << "Проход в ширину: ";
//        //vector<int> res2 = g2->BreadthFirstSearch(5);
//        //for (const auto& it : res2) {
//        //    cout << it << " ";
//        //}
//
//        ///// Проход итератором 
//        //cout << endl << "Итератором: ";
//        //for (Graph<int>::Iterator<int> it = g2->begin(); it != g2->end(); ++it) {
//        //    cout << *it << " ";
//        //}
//        //cout << endl;
//
//        ///*Graph<int>* g3(move(g2));*/
//
//        Graph<int>* g1 = new Graph<int>();
//
//        g1->InsertVertex(1);
//        g1->InsertVertex(2);
//        g1->InsertVertex(3);
//        g1->InsertEdge(1, 2, 1);
//        g1->InsertEdge(2, 3, 1);
//        g1->InsertEdge(1, 3, 1);
//
//        g1->PrintAdjacencyMatrix();
//
//        /// Проход в глубину
//        cout << endl << "Проход в глубину: ";
//        vector<int> res = g1->DepthFirstSearch(3);
//        for (const auto& it : res) {
//            cout << it << " ";
//        }
//        cout << endl;
//
//
//        //// конструктор копирования
//        //Graph<int>* g2(g1);
//
//
//        // конструктор перемещения
//        Graph<int>* g2(move(g1));
//
//        /// Проход итератором 
//        cout << endl << "Итератором до: ";
//        for (Graph<int>::Iterator<int> it = g1->begin(); it != g1->end(); ++it) {
//            cout << *it << " ";
//        }
//        cout << endl;
//
//        /// Проход итератором 
//        cout << endl << "Итератором после: ";
//        for (Graph<int>::Iterator<int> it = g2->begin(); it != g2->end(); ++it) {
//            cout << *it << " ";
//        }
//        cout << endl;
//    }
//
//    catch (const char* error_message) {
//        cout << endl << error_message << endl;
//    }
//}

