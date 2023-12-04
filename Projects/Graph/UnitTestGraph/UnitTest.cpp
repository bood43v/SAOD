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
            Graph<int> g1(1);
            g1.InsertVertex(2);
            g1.InsertVertex(3);
            g1.InsertVertex(4);
            g1.InsertVertex(5);
            g1.InsertEdge(1, 2, 5);
            g1.InsertEdge(1, 4, 2);
            g1.InsertEdge(2, 3, 7);

            Assert::IsTrue(g1.isEmpty() == false);
            Assert::IsTrue(g1.NumberOfEdges() == 3);
            Assert::IsTrue(g1.NumberOfVertices() == 5);

            g1.InsertEdge(1, 1, 10);
            Assert::IsTrue(g1.NumberOfEdges() == 4);
            Assert::IsTrue(g1.NumberOfVertices() == 5);
        }

        /// <summary>
        /// тестирование конструктора копирования
        /// </summary>
        TEST_METHOD(TestMethod_CopyConstructor)
        {
            Graph<int> g1(1);
            g1.InsertVertex(2);
            g1.InsertVertex(3);
            g1.InsertVertex(4);
            g1.InsertVertex(5);
            g1.InsertEdge(1, 2, 5);
            g1.InsertEdge(1, 4, 2);
            g1.InsertEdge(2, 3, 7);

            Graph<int> g2(g1);

            Assert::IsTrue(g1.NumberOfEdges() == 3);
            Assert::IsTrue(g2.NumberOfEdges() == 3);
            Assert::IsTrue(g1.NumberOfVertices() == 5);
            Assert::IsTrue(g2.NumberOfVertices() == 5);

            vector<int> a;
            vector<int> b;
            /// Проход итератором 
            for (Graph<int>::Iterator<int> it = g1.begin(); it != g1.end(); ++it) {
                a.push_back(*it);
            }
            /// Проход итератором 
            for (Graph<int>::Iterator<int> it2 = g2.begin(); it2 != g2.end(); ++it2) {
                b.push_back(*it2);
            }
            //a.push_back(1);
            Assert::IsTrue(a == b);
        }

        /// <summary>
        /// тестирование конструктора перемещения
        /// </summary>
        TEST_METHOD(TestMethod_MoveConstructor)
        {
            Graph<int> g1(1);
            g1.InsertVertex(2);
            g1.InsertVertex(3);
            g1.InsertVertex(4);
            g1.InsertVertex(5);
            g1.InsertEdge(1, 2, 5);
            g1.InsertEdge(1, 4, 2);
            g1.InsertEdge(2, 3, 7);

            vector<int> a;
            /// Проход итератором чтобы проверить второй граф после перемещения первого
            for (Graph<int>::Iterator<int> it = g1.begin(); it != g1.end(); ++it) {
                a.push_back(*it);
            }

            Graph<int> g2(move(g1));
            Assert::IsTrue(g1.isEmpty() == true);
            Assert::IsTrue(g1.NumberOfEdges() == 0);
            Assert::IsTrue(g1.NumberOfVertices() == 0);
            Assert::IsTrue(g2.NumberOfEdges() == 3);
            Assert::IsTrue(g2.NumberOfVertices() == 5);

            
            vector<int> b;
            /// Проход итератором 
            for (Graph<int>::Iterator<int> it2 = g2.begin(); it2 != g2.end(); ++it2) {
                b.push_back(*it2);
            }
            //a.push_back(1);
            Assert::IsTrue(a == b);
        }

        /// <summary>
        /// тестирование оператора присваивания копированием
        /// </summary>
        TEST_METHOD(TestMethod_AssingmentOperator)
        {
            Graph<int> g1(1);
            g1.InsertVertex(2);
            g1.InsertVertex(3);
            g1.InsertVertex(4);
            g1.InsertVertex(5);
            g1.InsertEdge(1, 2, 5);
            g1.InsertEdge(1, 4, 2);
            g1.InsertEdge(2, 3, 7);

            Graph<int> g2 = g1;

            Assert::IsTrue(g1.NumberOfEdges() == 3);
            Assert::IsTrue(g2.NumberOfEdges() == 3);
            Assert::IsTrue(g1.NumberOfVertices() == 5);
            Assert::IsTrue(g2.NumberOfVertices() == 5);

            vector<int> a;
            vector<int> b;
            /// Проход итератором 
            for (Graph<int>::Iterator<int> it = g1.begin(); it != g1.end(); ++it) {
                a.push_back(*it);
            }
            /// Проход итератором 
            for (Graph<int>::Iterator<int> it2 = g2.begin(); it2 != g2.end(); ++it2) {
                b.push_back(*it2);
            }
            //a.push_back(1);
            Assert::IsTrue(a == b);
        }


        /// <summary>
        /// тестирование оператора присваивания перемещением
        /// </summary>
        TEST_METHOD(TestMethod_MoveAssingmentOperator)
        {
            Graph<int> g1(1);
            g1.InsertVertex(2);
            g1.InsertVertex(3);
            g1.InsertVertex(4);
            g1.InsertVertex(5);
            g1.InsertEdge(1, 2, 5);
            g1.InsertEdge(1, 4, 2);
            g1.InsertEdge(2, 3, 7);

            vector<int> a;
            /// Проход итератором чтобы проверить второй граф после перемещения первого
            for (Graph<int>::Iterator<int> it = g1.begin(); it != g1.end(); ++it) {
                a.push_back(*it);
            }

            Graph<int> g2 = move(g1);

            Assert::IsTrue(g1.isEmpty() == true);
            Assert::IsTrue(g1.NumberOfEdges() == 0);
            Assert::IsTrue(g1.NumberOfVertices() == 0);
            Assert::IsTrue(g2.NumberOfEdges() == 3);
            Assert::IsTrue(g2.NumberOfVertices() == 5);


            vector<int> b;
            /// Проход итератором 
            for (Graph<int>::Iterator<int> it2 = g2.begin(); it2 != g2.end(); ++it2) {
                b.push_back(*it2);
            }
            //a.push_back(1);
            Assert::IsTrue(a == b);
        }
        /// <summary>
        /// тестирование удаления дуги
        /// </summary>
        TEST_METHOD(TestMethod_DeleteEdge)
        {
            Graph<int> g1(1);
            g1.InsertVertex(2);
            g1.InsertVertex(3);
            g1.InsertVertex(4);
            g1.InsertVertex(5);
            g1.InsertEdge(1, 2, 5);
            g1.InsertEdge(1, 4, 2);
            g1.InsertEdge(2, 3, 7);

            Assert::IsTrue(g1.NumberOfEdges() == 3);
            Assert::IsTrue(g1.NumberOfVertices() == 5);

            g1.InsertEdge(1, 1, 10);
            Assert::IsTrue(g1.NumberOfEdges() == 4);
            Assert::IsTrue(g1.NumberOfVertices() == 5);

            g1.DeleteEdge(1, 1);
            Assert::IsTrue(g1.NumberOfEdges() == 3);
            Assert::IsTrue(g1.NumberOfVertices() == 5);

            // удаление несуществующего ребра не приводит к изменениям
            g1.DeleteEdge(2, 2);
            Assert::IsTrue(g1.NumberOfEdges() == 3);
            Assert::IsTrue(g1.NumberOfVertices() == 5);

            g1.DeleteEdge(4, 1);
            Assert::IsTrue(g1.NumberOfEdges() == 2);
            Assert::IsTrue(g1.NumberOfVertices() == 5);
        }

        /// <summary>
        /// тестирование удаления вершины
        /// </summary>
        TEST_METHOD(TestMethod_DeleteVertex)
        {
            Graph<int> g1(1);
            g1.InsertVertex(2);
            g1.InsertVertex(3);
            g1.InsertVertex(4);
            g1.InsertVertex(5);
            g1.InsertEdge(1, 2, 5);
            g1.InsertEdge(1, 4, 2);
            g1.InsertEdge(2, 3, 7);

            Assert::IsTrue(g1.NumberOfEdges() == 3);
            Assert::IsTrue(g1.NumberOfVertices() == 5);

            g1.InsertEdge(1, 1, 10);
            Assert::IsTrue(g1.NumberOfEdges() == 4);

            g1.DeleteVertex(5);
            Assert::IsTrue(g1.NumberOfEdges() == 4);
            Assert::IsTrue(g1.NumberOfVertices() == 4);

            g1.DeleteVertex(1);
            Assert::IsTrue(g1.NumberOfEdges() == 1);
            Assert::IsTrue(g1.NumberOfVertices() == 3);

            g1.DeleteVertex(2);
            g1.DeleteVertex(3);
            g1.DeleteVertex(4);
            Assert::IsTrue(g1.isEmpty() == true);
        }
        /// <summary>
        /// тестирование веса дуги (изменяется при задании дуги заново)
        /// </summary>
        TEST_METHOD(TestMethod_GetWeight)
        {
            Graph<int> g1(1);
            g1.InsertVertex(2);
            g1.InsertVertex(3);
            g1.InsertVertex(4);
            g1.InsertVertex(5);
            g1.InsertEdge(1, 2, 5);
            g1.InsertEdge(1, 4, 2);
            g1.InsertEdge(2, 3, 7);

            Assert::IsTrue(g1.GetWeight(1, 2) == 5);
            g1.InsertEdge(1, 2, 3);
            Assert::IsTrue(g1.GetWeight(1, 2) == 3);
            g1.InsertEdge(1, 2, 7);
            Assert::IsTrue(g1.GetWeight(1, 2) == 7);
        }

        /// <summary>
        /// тестирование соседей, с которыми есть прямая связь
        /// </summary>
        TEST_METHOD(TestMethod_GetNeighbors)
        {
            Graph<int> g1(1);
           
            g1.InsertVertex(2);
            g1.InsertVertex(3);
            g1.InsertVertex(4);
            g1.InsertVertex(5);
            g1.InsertEdge(1, 2, 5);
            g1.InsertEdge(1, 4, 2);
            g1.InsertEdge(2, 3, 7);

            std::vector<int> res = g1.GetNeighbors(1);
            std::vector<int> fixed = { 2, 4 };
            int i = 0;
            Assert::IsTrue(res.size() == fixed.size());
            for (const auto& it : res) {
                Assert::IsTrue(it == fixed[i]);
                i++;
            }

            g1.InsertEdge(1, 3, 15);
            res = g1.GetNeighbors(1);
            fixed = { 2, 3, 4 };
            i = 0;
            Assert::IsTrue(res.size() == fixed.size());
            for (const auto& it : res) {
                Assert::IsTrue(it == fixed[i]);
                i++;
            }

            g1.InsertEdge(1, 5, -20);
            res = g1.GetNeighbors(1);
            fixed = { 2, 3, 4, 5 };
            i = 0;
            Assert::IsTrue(res.size() == fixed.size());
            for (const auto& it : res) {
                Assert::IsTrue(it == fixed[i]);
                i++;
            }

        }

        /// <summary>
        /// тестирование обхода в ширину
        /// </summary>
        TEST_METHOD(TestMethod_Breadth)
        {
            Graph<int> g2(1);
            g2.InsertVertex(2);
            g2.InsertVertex(3);
            g2.InsertVertex(4);
            g2.InsertVertex(5);
            g2.InsertVertex(6);
            g2.InsertEdge(1, 2, 5);
            g2.InsertEdge(1, 1, 5);
            g2.InsertEdge(1, 4, 2);
            g2.InsertEdge(2, 3, 7);
            g2.InsertEdge(1, 5, -20);

            vector<int> fixed1 = { 1, 2, 4, 3 };
            int i = 0;
            vector<int> res1 = g2.BreadthFirstSearch(1);
            for (const auto& it : res1) {
                Assert::IsTrue(it == fixed1[i]);
                i++;
            }

            vector<int> fixed2 = { 2, 3 };
            i = 0;
            vector<int> res2 = g2.BreadthFirstSearch(2);
            for (const auto& it : res2) {
                Assert::IsTrue(it == fixed2[i]);
                i++;
            }

            vector<int> fixed3 = { 3 };
            i = 0;
            vector<int> res3 = g2.BreadthFirstSearch(3);
            for (const auto& it : res3) {
                Assert::IsTrue(it == fixed3[i]);
                i++;
            }

            vector<int> fixed4 = { 4 };
            i = 0;
            vector<int> res4 = g2.BreadthFirstSearch(4);
            for (const auto& it : res4) {
                Assert::IsTrue(it == fixed4[i]);
                i++;
            }

            vector<int> fixed5 = { 5, 1, 2, 4, 3 };
            i = 0;
            vector<int> res5 = g2.BreadthFirstSearch(5);
            for (const auto& it : res5) {
                Assert::IsTrue(it == fixed5[i]);
                i++;
            }

            //другой граф

            Graph<int> g3(1);
            g3.InsertVertex(2);
            g3.InsertVertex(3);
            g3.InsertVertex(4);
            g3.InsertVertex(5);
            g3.InsertVertex(6);
            g3.InsertVertex(7);
            g3.InsertVertex(8);
            g3.InsertEdge(1, 2, 1);
            g3.InsertEdge(1, 3, 1);
            g3.InsertEdge(2, 4, 1);
            g3.InsertEdge(3, 5, 1);
            g3.InsertEdge(4, 6, 1);
            g3.InsertEdge(4, 7, 1);
            g3.InsertEdge(7, 8, 1);

            vector<int> vec1 = { 1, 2, 3, 4, 5, 6, 7, 8 };
            i = 0;
            vector<int> result = g3.BreadthFirstSearch(1);
            for (const auto& it : result) {
                Assert::IsTrue(it == vec1[i]);
                i++;
            }

        }

        /// <summary>
        /// тестирование обхода в ширину
        /// </summary>
        TEST_METHOD(TestMethod_Depth)
        {
            Graph<int> g2(1);
            g2.InsertVertex(2);
            g2.InsertVertex(3);
            g2.InsertVertex(4);
            g2.InsertVertex(5);
            g2.InsertVertex(6);
            g2.InsertEdge(1, 2, 5);
            g2.InsertEdge(1, 1, 5);
            g2.InsertEdge(1, 4, 2);
            g2.InsertEdge(2, 3, 7);
            g2.InsertEdge(1, 5, -20);

            vector<int> fixed1 = { 1, 2, 3, 4 };
            int i = 0;
            vector<int> res1 = g2.DepthFirstSearch(1);
            for (const auto& it : res1) {
                Assert::IsTrue(it == fixed1[i]);
                i++;
            }

            vector<int> fixed2 = { 2, 3 };
            i = 0;
            vector<int> res2 = g2.DepthFirstSearch(2);
            for (const auto& it : res2) {
                Assert::IsTrue(it == fixed2[i]);
                i++;
            }

            vector<int> fixed3 = { 3 };
            i = 0;
            vector<int> res3 = g2.DepthFirstSearch(3);
            for (const auto& it : res3) {
                Assert::IsTrue(it == fixed3[i]);
                i++;
            }

            vector<int> fixed4 = { 4 };
            i = 0;
            vector<int> res4 = g2.DepthFirstSearch(4);
            for (const auto& it : res4) {
                Assert::IsTrue(it == fixed4[i]);
                i++;
            }

            vector<int> fixed5 = { 5, 1, 2, 3, 4 };
            i = 0;
            vector<int> res5 = g2.DepthFirstSearch(5);
            for (const auto& it : res5) {
                Assert::IsTrue(it == fixed5[i]);
                i++;
            }

            //другой граф

            Graph<int> g3(1);
            g3.InsertVertex(2);
            g3.InsertVertex(3);
            g3.InsertVertex(4);
            g3.InsertVertex(5);
            g3.InsertVertex(6);
            g3.InsertVertex(7);
            g3.InsertVertex(8);
            g3.InsertEdge(1, 2, 1);
            g3.InsertEdge(1, 3, 1);
            g3.InsertEdge(2, 4, 1);
            g3.InsertEdge(3, 5, 1);
            g3.InsertEdge(4, 6, 1);
            g3.InsertEdge(4, 7, 1);
            g3.InsertEdge(7, 8, 1);

            vector<int> vec1 = { 1, 2, 4, 6, 7, 8, 3, 5 };
            i = 0;
            vector<int> result = g3.DepthFirstSearch(1);
            for (const auto& it : result) {
                Assert::IsTrue(it == vec1[i]);
                i++;
            }

        }

        /// <summary>
        /// тестирование обхода в ширину
        /// </summary>
        TEST_METHOD(TestMethod_Iterator)
        {
            Graph<int> g2(1);
            g2.InsertVertex(2);
            g2.InsertVertex(3);
            g2.InsertVertex(4);
            g2.InsertVertex(5);
            g2.InsertVertex(6);
            g2.InsertEdge(1, 2, 5);
            g2.InsertEdge(1, 1, 5);
            g2.InsertEdge(1, 4, 2);
            g2.InsertEdge(2, 3, 7);
            g2.InsertEdge(1, 5, -20);

            vector<int> fixed = { 1, 2, 3, 4, 5, 6 };
            int i = 0;
            for (Graph<int>::Iterator<int> it = g2.begin(); it != g2.end(); ++it) {
                Assert::IsTrue(*it == fixed[i]);
                i++;
            }



            Graph<int> g3(1);
            g3.InsertVertex(2);
            g3.InsertVertex(6);
            g3.InsertVertex(4);
            g3.InsertVertex(3);
            g3.InsertVertex(5);

            vector<int> fixed2 = { 1, 2, 6, 4, 3, 5 };
            i = 0;
            for (Graph<int>::Iterator<int> it = g3.begin(); it != g3.end(); ++it) {
                Assert::IsTrue(*it == fixed2[i]);
                i++;
            }
        }

    };
}








///// Тестирование методов класса Graph
///// @author Будаев Г.Б.
//#include "pch.h"
//#include "CppUnitTest.h"
//#include "../Graph.h"
//#include <vector>
//
//using namespace Microsoft::VisualStudio::CppUnitTestFramework;
//
//namespace UnitTestGraph
//{
//    TEST_CLASS(UnitTest1)
//    {
//    public:
//        /// <summary>
//        /// тестирование вставки, количества вершин, дуг, на пустоту.
//        /// </summary>
//        TEST_METHOD(TestMethod_Main)
//        {
//            Graph<int>* g1 =  Graph<int>();
//            Assert::IsTrue(g1->isEmpty() == true);
//            g1->InsertVertex(1);
//            g1->InsertVertex(2);
//            g1->InsertVertex(3);
//            g1->InsertVertex(4);
//            g1->InsertVertex(5);
//            g1->InsertEdge(1, 2, 5);
//            g1->InsertEdge(1, 4, 2);
//            g1->InsertEdge(2, 3, 7);
//
//            Assert::IsTrue(g1->isEmpty() == false);
//            Assert::IsTrue(g1->NumberOfEdges() == 3);
//            Assert::IsTrue(g1->NumberOfVertices() == 5);
//
//            g1->InsertEdge(1, 1, 10);
//            Assert::IsTrue(g1->NumberOfEdges() == 4);
//            Assert::IsTrue(g1->NumberOfVertices() == 5);
//        }
//        /// <summary>
//        /// тестирование удаления дуги
//        /// </summary>
//        TEST_METHOD(TestMethod_DeleteEdge)
//        {
//            Graph<int>* g1 =  Graph<int>();
//            g1->InsertVertex(1);
//            g1->InsertVertex(2);
//            g1->InsertVertex(3);
//            g1->InsertVertex(4);
//            g1->InsertVertex(5);
//            g1->InsertEdge(1, 2, 5);
//            g1->InsertEdge(1, 4, 2);
//            g1->InsertEdge(2, 3, 7);
//
//            Assert::IsTrue(g1->NumberOfEdges() == 3);
//            Assert::IsTrue(g1->NumberOfVertices() == 5);
//
//            g1->InsertEdge(1, 1, 10);
//            Assert::IsTrue(g1->NumberOfEdges() == 4);
//            Assert::IsTrue(g1->NumberOfVertices() == 5);
//
//            g1->DeleteEdge(1, 1);
//            Assert::IsTrue(g1->NumberOfEdges() == 3);
//            Assert::IsTrue(g1->NumberOfVertices() == 5);
//
//            // удаление несуществующего ребра не приводит к изменениям
//            g1->DeleteEdge(2, 2);
//            Assert::IsTrue(g1->NumberOfEdges() == 3);
//            Assert::IsTrue(g1->NumberOfVertices() == 5);
//
//            g1->DeleteEdge(4, 1);
//            Assert::IsTrue(g1->NumberOfEdges() == 2);
//            Assert::IsTrue(g1->NumberOfVertices() == 5);
//        }
//
//        /// <summary>
//        /// тестирование удаления вершины
//        /// </summary>
//        TEST_METHOD(TestMethod_DeleteVertex)
//        {
//            Graph<int>* g1 =  Graph<int>();
//            g1->InsertVertex(1);
//            g1->InsertVertex(2);
//            g1->InsertVertex(3);
//            g1->InsertVertex(4);
//            g1->InsertVertex(5);
//            g1->InsertEdge(1, 2, 5);
//            g1->InsertEdge(1, 4, 2);
//            g1->InsertEdge(2, 3, 7);
//
//            Assert::IsTrue(g1->NumberOfEdges() == 3);
//            Assert::IsTrue(g1->NumberOfVertices() == 5);
//
//            g1->InsertEdge(1, 1, 10);
//            Assert::IsTrue(g1->NumberOfEdges() == 4);
//
//            g1->DeleteVertex(5);
//            Assert::IsTrue(g1->NumberOfEdges() == 4);
//            Assert::IsTrue(g1->NumberOfVertices() == 4);
//
//            g1->DeleteVertex(1);
//            Assert::IsTrue(g1->NumberOfEdges() == 1);
//            Assert::IsTrue(g1->NumberOfVertices() == 3);
//
//            g1->DeleteVertex(2);
//            g1->DeleteVertex(3);
//            g1->DeleteVertex(4);
//            Assert::IsTrue(g1->isEmpty() == true);
//        }
//        /// <summary>
//        /// тестирование веса дуги (изменяется при задании дуги заново)
//        /// </summary>
//        TEST_METHOD(TestMethod_GetWeight)
//        {
//            Graph<int>* g1 =  Graph<int>();
//            Assert::IsTrue(g1->isEmpty() == true);
//            g1->InsertVertex(1);
//            g1->InsertVertex(2);
//            g1->InsertVertex(3);
//            g1->InsertVertex(4);
//            g1->InsertVertex(5);
//            g1->InsertEdge(1, 2, 5);
//            g1->InsertEdge(1, 4, 2);
//            g1->InsertEdge(2, 3, 7);
//
//            Assert::IsTrue(g1->GetWeight(1, 2) == 5);
//            g1->InsertEdge(1, 2, 3);
//            Assert::IsTrue(g1->GetWeight(1, 2) == 3);
//            g1->InsertEdge(1, 2, 7);
//            Assert::IsTrue(g1->GetWeight(1, 2) == 7);
//        }
//
//        /// <summary>
//        /// тестирование соседей, с которыми есть прямая связь
//        /// </summary>
//        TEST_METHOD(TestMethod_GetNeighbors)
//        {
//            Graph<int>* g1 =  Graph<int>();
//            Assert::IsTrue(g1->isEmpty() == true);
//            g1->InsertVertex(1);
//            g1->InsertVertex(2);
//            g1->InsertVertex(3);
//            g1->InsertVertex(4);
//            g1->InsertVertex(5);
//            g1->InsertEdge(1, 2, 5);
//            g1->InsertEdge(1, 4, 2);
//            g1->InsertEdge(2, 3, 7);
//
//            std::vector<int> res = g1->GetNeighbors(1);
//            std::vector<int> fixed = { 2, 4 };
//            int i = 0;
//            Assert::IsTrue(res.size() == fixed.size());
//            for (const auto& it : res) {
//                Assert::IsTrue(it == fixed[i]);
//                i++;
//            }
//
//            g1->InsertEdge(1, 3, 15);
//            res = g1->GetNeighbors(1);
//            fixed = { 2, 3, 4 };
//            i = 0;
//            Assert::IsTrue(res.size() == fixed.size());
//            for (const auto& it : res) {
//                Assert::IsTrue(it == fixed[i]);
//                i++;
//            }
//
//            g1->InsertEdge(1, 5, -20);
//            res = g1->GetNeighbors(1);
//            fixed = { 2, 3, 4, 5 };
//            i = 0;
//            Assert::IsTrue(res.size() == fixed.size());
//            for (const auto& it : res) {
//                Assert::IsTrue(it == fixed[i]);
//                i++;
//            }
//
//        }
//
//        /// <summary>
//        /// тестирование обхода в ширину
//        /// </summary>
//        TEST_METHOD(TestMethod_Breadth)
//        {
//            Graph<int>* g2 =  Graph<int>();
//            g2->InsertVertex(1);
//            g2->InsertVertex(2);
//            g2->InsertVertex(3);
//            g2->InsertVertex(4);
//            g2->InsertVertex(5);
//            g2->InsertVertex(6);
//            g2->InsertEdge(1, 2, 5);
//            g2->InsertEdge(1, 1, 5);
//            g2->InsertEdge(1, 4, 2);
//            g2->InsertEdge(2, 3, 7);
//            g2->InsertEdge(1, 5, -20);
//
//            vector<int> fixed1 = { 1, 2, 4, 3 };
//            int i = 0;
//            vector<int> res1 = g2->BreadthFirstSearch(1);
//            for (const auto& it : res1) {
//                Assert::IsTrue(it == fixed1[i]);
//                i++;
//            }
//
//            vector<int> fixed2 = { 2, 3 };
//            i = 0;
//            vector<int> res2 = g2->BreadthFirstSearch(2);
//            for (const auto& it : res2) {
//                Assert::IsTrue(it == fixed2[i]);
//                i++;
//            }
//
//            vector<int> fixed3 = { 3 };
//            i = 0;
//            vector<int> res3 = g2->BreadthFirstSearch(3);
//            for (const auto& it : res3) {
//                Assert::IsTrue(it == fixed3[i]);
//                i++;
//            }
//
//            vector<int> fixed4 = { 4 };
//            i = 0;
//            vector<int> res4 = g2->BreadthFirstSearch(4);
//            for (const auto& it : res4) {
//                Assert::IsTrue(it == fixed4[i]);
//                i++;
//            }
//
//            vector<int> fixed5 = { 5, 1, 2, 4, 3 };
//            i = 0;
//            vector<int> res5 = g2->BreadthFirstSearch(5);
//            for (const auto& it : res5) {
//                Assert::IsTrue(it == fixed5[i]);
//                i++;
//            }
//
//            //другой граф
//
//            Graph<int>* g3 =  Graph<int>();
//            g3->InsertVertex(1);
//            g3->InsertVertex(2);
//            g3->InsertVertex(3);
//            g3->InsertVertex(4);
//            g3->InsertVertex(5);
//            g3->InsertVertex(6);
//            g3->InsertVertex(7);
//            g3->InsertVertex(8);
//            g3->InsertEdge(1, 2, 1);
//            g3->InsertEdge(1, 3, 1);
//            g3->InsertEdge(2, 4, 1);
//            g3->InsertEdge(3, 5, 1);
//            g3->InsertEdge(4, 6, 1);
//            g3->InsertEdge(4, 7, 1);
//            g3->InsertEdge(7, 8, 1);
//
//            vector<int> vec1 = { 1, 2, 3, 4, 5, 6, 7, 8 };
//            i = 0;
//            vector<int> result = g3->BreadthFirstSearch(1);
//            for (const auto& it : result) {
//                Assert::IsTrue(it == vec1[i]);
//                i++;
//            }
//
//        }
//
//        /// <summary>
//        /// тестирование обхода в ширину
//        /// </summary>
//        TEST_METHOD(TestMethod_Depth)
//        {
//            Graph<int>* g2 =  Graph<int>();
//            g2->InsertVertex(1);
//            g2->InsertVertex(2);
//            g2->InsertVertex(3);
//            g2->InsertVertex(4);
//            g2->InsertVertex(5);
//            g2->InsertVertex(6);
//            g2->InsertEdge(1, 2, 5);
//            g2->InsertEdge(1, 1, 5);
//            g2->InsertEdge(1, 4, 2);
//            g2->InsertEdge(2, 3, 7);
//            g2->InsertEdge(1, 5, -20);
//
//            vector<int> fixed1 = { 1, 2, 3, 4 };
//            int i = 0;
//            vector<int> res1 = g2->DepthFirstSearch(1);
//            for (const auto& it : res1) {
//                Assert::IsTrue(it == fixed1[i]);
//                i++;
//            }
//
//            vector<int> fixed2 = { 2, 3 };
//            i = 0;
//            vector<int> res2 = g2->DepthFirstSearch(2);
//            for (const auto& it : res2) {
//                Assert::IsTrue(it == fixed2[i]);
//                i++;
//            }
//
//            vector<int> fixed3 = { 3 };
//            i = 0;
//            vector<int> res3 = g2->DepthFirstSearch(3);
//            for (const auto& it : res3) {
//                Assert::IsTrue(it == fixed3[i]);
//                i++;
//            }
//
//            vector<int> fixed4 = { 4 };
//            i = 0;
//            vector<int> res4 = g2->DepthFirstSearch(4);
//            for (const auto& it : res4) {
//                Assert::IsTrue(it == fixed4[i]);
//                i++;
//            }
//
//            vector<int> fixed5 = { 5, 1, 2, 3, 4 };
//            i = 0;
//            vector<int> res5 = g2->DepthFirstSearch(5);
//            for (const auto& it : res5) {
//                Assert::IsTrue(it == fixed5[i]);
//                i++;
//            }
//
//            //другой граф
//
//            Graph<int>* g3 =  Graph<int>();
//            g3->InsertVertex(1);
//            g3->InsertVertex(2);
//            g3->InsertVertex(3);
//            g3->InsertVertex(4);
//            g3->InsertVertex(5);
//            g3->InsertVertex(6);
//            g3->InsertVertex(7);
//            g3->InsertVertex(8);
//            g3->InsertEdge(1, 2, 1);
//            g3->InsertEdge(1, 3, 1);
//            g3->InsertEdge(2, 4, 1);
//            g3->InsertEdge(3, 5, 1);
//            g3->InsertEdge(4, 6, 1);
//            g3->InsertEdge(4, 7, 1);
//            g3->InsertEdge(7, 8, 1);
//
//            vector<int> vec1 = { 1, 2, 4, 6, 7, 8, 3, 5 };
//            i = 0;
//            vector<int> result = g3->DepthFirstSearch(1);
//            for (const auto& it : result) {
//                Assert::IsTrue(it == vec1[i]);
//                i++;
//            }
//
//        }
//
//        /// <summary>
//        /// тестирование обхода в ширину
//        /// </summary>
//        TEST_METHOD(TestMethod_Iterator)
//        {
//            Graph<int>* g2 =  Graph<int>();
//            g2->InsertVertex(1);
//            g2->InsertVertex(2);
//            g2->InsertVertex(3);
//            g2->InsertVertex(4);
//            g2->InsertVertex(5);
//            g2->InsertVertex(6);
//            g2->InsertEdge(1, 2, 5);
//            g2->InsertEdge(1, 1, 5);
//            g2->InsertEdge(1, 4, 2);
//            g2->InsertEdge(2, 3, 7);
//            g2->InsertEdge(1, 5, -20);
//
//            vector<int> fixed = { 1, 2, 3, 4, 5, 6 };
//            int i = 0;
//            for (Graph<int>::Iterator<int> it = g2->begin(); it != g2->end(); ++it) {
//                Assert::IsTrue(*it == fixed[i]);
//                i++;
//            }
//
//
//
//            Graph<int>* g3 =  Graph<int>();
//            g3->InsertVertex(1);
//            g3->InsertVertex(2);
//            g3->InsertVertex(6);
//            g3->InsertVertex(4);
//            g3->InsertVertex(3);
//            g3->InsertVertex(5);
//
//            vector<int> fixed2 = { 1, 2, 6, 4, 3, 5 };
//            i = 0;
//            for (Graph<int>::Iterator<int> it = g3->begin(); it != g3->end(); ++it) {
//                Assert::IsTrue(*it == fixed2[i]);
//                i++;
//            }
//        }
//    };
//}