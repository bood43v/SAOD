/// Тестирования класса Graph
/// @author Будаев Г.Б.
#pragma once
#include <iostream>
#include "Graph.h"
#include <cassert>

/// <summary>
/// Тестирование поиска кратчайшего пути
/// </summary>
void testFindShortest() {
    Graph<int> graph;  // Создаем граф с 6 вершинами

    graph.InsertVertex(0);
    graph.InsertVertex(1);
    graph.InsertVertex(2);
    graph.InsertVertex(3);

    graph.InsertEdge(0, 1, 4);
    graph.InsertEdge(0, 0, 100);
    graph.InsertEdge(0, 2, 1);
    graph.InsertEdge(2, 1, 2);
    graph.InsertEdge(1, 3, 5);

    vector<int> way0 = graph.FindShortestDistances(0);

    // Проверяем расстояния от начальной вершины до остальных вершин
    assert(way0[0] == 0);
    assert(way0[1] == 3);
    assert(way0[2] == 1);
    assert(way0[3] == 8);
    //assert(way[3] == 999);

    vector<int> way1 = graph.FindShortestDistances(1);

    // Проверяем расстояния от начальной вершины до остальных вершин
    assert(way1[0] == 0);
    assert(way1[1] == 0);
    assert(way1[2] == 0);
    assert(way1[3] == 5);

    vector<int> way2 = graph.FindShortestDistances(2);

    // Проверяем расстояния от начальной вершины до остальных вершин
    assert(way2[0] == 0);
    assert(way2[1] == 2);
    assert(way2[2] == 0);
    assert(way2[3] == 7);

    vector<int> way3 = graph.FindShortestDistances(3);

    // Проверяем расстояния от начальной вершины до остальных вершин
    assert(way3[0] == 0);
    assert(way3[1] == 0);
    assert(way3[2] == 0);
    assert(way3[3] == 0);
   
}