/// Тестирование методов класса Graph
/// @author Будаев Г.Б.
#include "pch.h"
#include "CppUnitTest.h"
#include "../Graph.h"
#include <vector>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestGraph
{
    TEST_CLASS(UnitTest1)
    {
    public:
        /// <summary>
        /// тестирование вставки, количества вершин, дуг, на пустоту.
        /// </summary>
        TEST_METHOD(TestMethod_Main)
        {
            Graph<int>* g1 = new Graph<int>();
            Assert::IsTrue(g1->isEmpty() == true);
            g1->InsertVertex(1);
            g1->InsertVertex(2);
            g1->InsertVertex(3);
            g1->InsertVertex(4);
            g1->InsertVertex(5);
            g1->InsertEdge(1, 2, 5);
            g1->InsertEdge(1, 4, 2);
            g1->InsertEdge(2, 3, 7);

            Assert::IsTrue(g1->isEmpty() == false);
            Assert::IsTrue(g1->NumberOfEdges() == 3);
            Assert::IsTrue(g1->NumberOfVertices() == 5);

            g1->InsertEdge(1, 1, 10);
            Assert::IsTrue(g1->NumberOfEdges() == 4);
            Assert::IsTrue(g1->NumberOfVertices() == 5);
        }
        /// <summary>
        /// тестирование удаления дуги
        /// </summary>
        TEST_METHOD(TestMethod_DeleteEdge)
        {
            Graph<int>* g1 = new Graph<int>();
            g1->InsertVertex(1);
            g1->InsertVertex(2);
            g1->InsertVertex(3);
            g1->InsertVertex(4);
            g1->InsertVertex(5);
            g1->InsertEdge(1, 2, 5);
            g1->InsertEdge(1, 4, 2);
            g1->InsertEdge(2, 3, 7);

            Assert::IsTrue(g1->NumberOfEdges() == 3);
            Assert::IsTrue(g1->NumberOfVertices() == 5);

            g1->InsertEdge(1, 1, 10);
            Assert::IsTrue(g1->NumberOfEdges() == 4);
            Assert::IsTrue(g1->NumberOfVertices() == 5);

            g1->DeleteEdge(1, 1);
            Assert::IsTrue(g1->NumberOfEdges() == 3);
            Assert::IsTrue(g1->NumberOfVertices() == 5);

            // удаление несуществующего ребра не приводит к изменениям
            g1->DeleteEdge(2, 2);
            Assert::IsTrue(g1->NumberOfEdges() == 3);
            Assert::IsTrue(g1->NumberOfVertices() == 5);

            g1->DeleteEdge(4, 1);
            Assert::IsTrue(g1->NumberOfEdges() == 2);
            Assert::IsTrue(g1->NumberOfVertices() == 5);
        }

        /// <summary>
        /// тестирование удаления вершины
        /// </summary>
        TEST_METHOD(TestMethod_DeleteVertex)
        {
            Graph<int>* g1 = new Graph<int>();
            g1->InsertVertex(1);
            g1->InsertVertex(2);
            g1->InsertVertex(3);
            g1->InsertVertex(4);
            g1->InsertVertex(5);
            g1->InsertEdge(1, 2, 5);
            g1->InsertEdge(1, 4, 2);
            g1->InsertEdge(2, 3, 7);

            Assert::IsTrue(g1->NumberOfEdges() == 3);
            Assert::IsTrue(g1->NumberOfVertices() == 5);

            g1->InsertEdge(1, 1, 10);
            Assert::IsTrue(g1->NumberOfEdges() == 4);

            g1->DeleteVertex(5);
            Assert::IsTrue(g1->NumberOfEdges() == 4);
            Assert::IsTrue(g1->NumberOfVertices() == 4);

            g1->DeleteVertex(1);
            Assert::IsTrue(g1->NumberOfEdges() == 1);
            Assert::IsTrue(g1->NumberOfVertices() == 3);

            g1->DeleteVertex(2);
            g1->DeleteVertex(3);
            g1->DeleteVertex(4);
            Assert::IsTrue(g1->isEmpty() == true);
        }
        /// <summary>
        /// тестирование веса дуги (изменяется при задании дуги заново)
        /// </summary>
        TEST_METHOD(TestMethod_GetWeight)
        {
            Graph<int>* g1 = new Graph<int>();
            Assert::IsTrue(g1->isEmpty() == true);
            g1->InsertVertex(1);
            g1->InsertVertex(2);
            g1->InsertVertex(3);
            g1->InsertVertex(4);
            g1->InsertVertex(5);
            g1->InsertEdge(1, 2, 5);
            g1->InsertEdge(1, 4, 2);
            g1->InsertEdge(2, 3, 7);

            Assert::IsTrue(g1->GetWeight(1, 2) == 5);
            g1->InsertEdge(1, 2, 3);
            Assert::IsTrue(g1->GetWeight(1, 2) == 3);
            g1->InsertEdge(1, 2, 7);
            Assert::IsTrue(g1->GetWeight(1, 2) == 7);
        }

        /// <summary>
        /// тестирование соседей, с которыми есть прямая связь
        /// </summary>
        TEST_METHOD(TestMethod_GetNeighbors)
        {
            Graph<int>* g1 = new Graph<int>();
            Assert::IsTrue(g1->isEmpty() == true);
            g1->InsertVertex(1);
            g1->InsertVertex(2);
            g1->InsertVertex(3);
            g1->InsertVertex(4);
            g1->InsertVertex(5);
            g1->InsertEdge(1, 2, 5);
            g1->InsertEdge(1, 4, 2);
            g1->InsertEdge(2, 3, 7);

            std::vector<int> res = g1->GetNeighbors(1);
            std::vector<int> fixed = { 2,4 };
            int i = 0;
            for (const auto& it : res) {
                Assert::IsTrue(it == fixed[i]);
                i++;
            }

        }
    };
}