/// Тестирование работы класса Heap
/// @author Будаев Г.Б.

#include "pch.h"
#include "CppUnitTest.h"
#include "../Heap.h"
#include <algorithm>
#include <vector>

using namespace std;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestHeap
{
    TEST_CLASS(UnitTest1)
    {
    public:
        /// <summary>
        /// Тестирование конструктора с вектором
        /// </summary>
        TEST_METHOD(TestVecConstructor)
        {
            // Несколько элементов
            vector<int> vec{ 1, 5, 3, 4 };
            MaxHeap<int> heap(vec);
            sort(vec.begin(), vec.end(), greater<>());

            Assert::IsTrue(heap.Size() == vec.size());
            for (const int& item : vec) {
                Assert::IsTrue(item == heap.Max());
            }

            // 0 элементов
            vector<int> vec2;
            MaxHeap<int> heap2(vec2);
            sort(vec2.begin(), vec2.end(), greater<>());

            Assert::IsTrue(heap2.Size() == vec2.size());
            for (const int& item : vec2) {
                Assert::IsTrue(item == heap2.Max());
            }
        }

        /// <summary>
        /// Тестирование конструктора копирования
        /// </summary>
        TEST_METHOD(TestCopyConstructor)
        {
            // Несколько элементов
            vector<int> vec{ 1, 5, 3, 4 };
            MaxHeap<int> heap1(vec);

            /// Конструктор копирования
            MaxHeap<int> heap2(heap1);       
            sort(vec.begin(), vec.end(), greater<>());

            /// Проверяем, одинаковые ли кучи 
            Assert::IsTrue(vec.size() == 4);
            Assert::IsTrue(heap1.Size() == vec.size());
            Assert::IsTrue(heap2.Size() == vec.size());
            for (const int& item : vec) {
                Assert::IsTrue(heap1.Max() == heap2.Max());
                //Assert::IsTrue(item == heap1.Max());
                //Assert::IsTrue(item == heap2.Max());
            }

            // 0 элементов
            vector<int> vec2;
            MaxHeap<int> heap3(vec2);

            /// Конструктор копирования
            MaxHeap<int> heap4(heap3);
            sort(vec2.begin(), vec2.end(), greater<>());

            /// Проверяем, одинаковые ли кучи 
            Assert::IsTrue(heap3.Size() == vec2.size());
            Assert::IsTrue(heap4.Size() == vec2.size());
            Assert::IsTrue(vec2.size() == 0);
            for (const int& item : vec2) {
                Assert::IsTrue(heap3.Max() == heap4.Max());
                //Assert::IsTrue(item == heap1.Max());
                //Assert::IsTrue(item == heap2.Max());
            }
        }

        /// <summary>
        /// Тестирование оператора присваивания копированием
        /// </summary>
        TEST_METHOD(TestAssignmentOperator)
        {
            // Несколько элементов
            vector<int> vec{ 1, 5, 3, 4 };
            MaxHeap<int> heap1(vec);
            sort(vec.begin(), vec.end(), greater<>());

            MaxHeap<int> heap2;

            /// Оператор присваивания копированием
            heap2 = heap1;     

            /// Проверяем, одинаковые ли кучи 
            Assert::IsTrue(vec.size() == 4);
            Assert::IsTrue(heap1.Size() == vec.size());
            Assert::IsTrue(heap2.Size() == vec.size());

            for (const int& item : vec) {
                Assert::IsTrue(heap1.Max() == heap2.Max());
                //Assert::IsTrue(item == heap1.Max());
                //Assert::IsTrue(item == heap2.Max());
            }

            // 0 элементов
            vector<int> vec2;
            MaxHeap<int> heap3(vec2);
            sort(vec2.begin(), vec2.end(), greater<>());

            MaxHeap<int> heap4;

            /// Оператор присваивания копированием
            heap4 = heap3;

            /// Проверяем, одинаковые ли кучи 
            Assert::IsTrue(heap3.Size() == vec2.size());
            Assert::IsTrue(heap4.Size() == vec2.size());
            Assert::IsTrue(vec2.size() == 0);
            for (const int& item : vec2) {
                Assert::IsTrue(heap3.Max() == heap4.Max());
                //Assert::IsTrue(item == heap1.Max());
                //Assert::IsTrue(item == heap2.Max());
            }
        }

        /// <summary>
        /// Тестирование оператора присваивания перемещением
        /// </summary>
        TEST_METHOD(TestMoveAssignmentOperator)
        {
            // Несколько элементов
            vector<int> vec{ 1, 5, 3, 4 };
            MaxHeap<int> heap1(vec);
            sort(vec.begin(), vec.end(), greater<>());

            MaxHeap<int> heap2;

            /// Оператор присваивания перемещением
            heap2 = move(heap1);

            /// Проверяем, одинаковые ли кучи 
            Assert::IsTrue(vec.size() == 4);
            Assert::IsTrue(heap1.Size() == 0);
            Assert::IsTrue(heap2.Size() == vec.size());

            for (const int& item : vec) {
                Assert::IsTrue(heap2.Max() == item);
                //Assert::IsTrue(item == heap1.Max());
                //Assert::IsTrue(item == heap2.Max());
            }

            // 0 элементов
            vector<int> vec2;
            MaxHeap<int> heap3(vec2);
            sort(vec2.begin(), vec2.end(), greater<>());

            MaxHeap<int> heap4;

            /// Оператор присваивания копированием
            heap4 = move(heap3);

            /// Проверяем, одинаковые ли кучи 
            Assert::IsTrue(heap3.Size() == 0);
            Assert::IsTrue(heap4.Size() == vec2.size());
            Assert::IsTrue(vec2.size() == 0);
            for (const int& item : vec2) {
                Assert::IsTrue(heap4.Max() == item);
                //Assert::IsTrue(item == heap1.Max());
                //Assert::IsTrue(item == heap2.Max());
            }
        }

        /// <summary>
        ///  Является ли кучей
        /// </summary>
        TEST_METHOD(TestInsert)
        {
            ///         30
            ///     7       10
            ///  5     6
            MaxHeap<int> heap(5);
            heap.insert(5);
            heap.insert(10);
            heap.insert(30);
            heap.insert(7);
            heap.insert(6);
            heap.insert(1111);
            //heap.insert(1111);
            vector<int> vec = heap.toVector();

            Assert::IsTrue(is_heap(vec.begin(), vec.end()));
            Assert::IsTrue(heap.Size() == 6);

            // куча из одного элемента
            MaxHeap<int> heap2(1);
            heap2.insert(999);
            Assert::IsTrue(heap2.Size() == 1);
            heap2.insert(1);
            Assert::IsTrue(heap2.Size() == 2);

            // куча без элементов и вставка в неё
            MaxHeap<int> heap3(0);
            Assert::IsTrue(heap3.Size() == 0);
            heap3.insert(22);
            Assert::IsTrue(heap3.Size() == 1);


        }

        /// <summary>
        /// Максимальный элемент в куче
        /// </summary>
        TEST_METHOD(TestMax)
        {
            ///         30
            ///     7       10
            ///  5     6
            MaxHeap<int> heap(5); 
            heap.insert(5);       
            heap.insert(10);
            heap.insert(30);
            heap.insert(7);
            heap.insert(6);

            vector<int> vec;
            vec.push_back(5);
            vec.push_back(10);
            vec.push_back(30);
            vec.push_back(7);
            vec.push_back(6);

            sort(vec.begin(), vec.end(), greater<>());
            for (int i = 0; i < vec.size(); i++)
            {
                Assert::IsTrue(vec[i] == heap.Max());
            }

            // куча из одного элемента
            MaxHeap<int> heap2(1);
            heap2.insert(999);
            Assert::IsTrue(heap2.Size() == 1);
            Assert::IsTrue(heap2.Max() == 999);
            Assert::IsTrue(heap2.Size() == 0);
            

            // куча без элементов
            MaxHeap<int> heap3(0);
            Assert::IsTrue(heap3.Size() == 0);
            
            // куча без элементов
            MaxHeap<int> heap4(0);
            Assert::IsTrue(heap3.Size() == 0);
            heap4.insert(999);
            Assert::IsTrue(heap4.Max() == 999);
            Assert::IsTrue(heap4.Size() == 0);

            
        }

        /// <summary>
        /// Удаление из кучи
        /// </summary>
        TEST_METHOD(TestRemove)
        {
            ///         30
            ///     7       10
            ///  5     6
            /// Создаем кучу и аналогичный вектор (отсортированный)
            MaxHeap<int> heap(5);
            heap.insert(5);
            heap.insert(10);
            heap.insert(30);
            heap.insert(7);
            heap.insert(6);


            vector<int> vec;
            vec.push_back(5);
            vec.push_back(10);
            vec.push_back(30);
            vec.push_back(7);
            vec.push_back(6);
            sort(vec.begin(), vec.end(), greater<>());

            // удаляем элемент из кучи
            heap.remove(5);
            // проверяем свойства кучи
            vector<int> vec3 = heap.toVector();
            Assert::IsTrue(is_heap(vec3.begin(), vec3.end()));

            // проверяем поэлементно кучу с помощью Max()
            vector<int> vec2;

            /*vec2.push_back(5);*/
            vec2.push_back(10);
            vec2.push_back(30);
            vec2.push_back(7);
            vec2.push_back(6);
            sort(vec2.begin(), vec2.end(), greater<>());

            Assert::IsTrue(heap.Size() == 4);

            for (int i = 0; i < vec2.size(); i++)
            {
                Assert::IsTrue(vec2[i] == heap.Max());
            }


            /// Создаем пустую кучу
            MaxHeap<int> heap2(0);
            Assert::IsTrue(heap2.Size() == 0);
            heap2.remove(5);
            Assert::IsTrue(heap2.Size() == 0);


            /// Создаем не пустую кучу
            MaxHeap<int> heap3(1);
            heap3.insert(5);
            Assert::IsTrue(heap3.Size() == 1);
            heap2.remove(5);
            Assert::IsTrue(heap2.Size() == 0);
        }

        /// <summary>
        /// Сортировка с помощью кучи
        /// </summary>
        TEST_METHOD(TestSort)
        {
            vector<int> vec;
            vec.push_back(5);
            vec.push_back(10);
            vec.push_back(30);
            vec.push_back(7);
            vec.push_back(6);

            sort(vec.begin(), vec.end(), greater<>());


            ///         30
            ///     7       10
            ///  5     6
            MaxHeap<int> heap(5);
            heap.insert(5);
            heap.insert(10);
            heap.insert(30);
            heap.insert(7);
            heap.insert(6);

            vector<int> vec2;
            vec2 = heap.heapSort();

            for (int i = 0; i < vec.size(); i++)
            {
                Assert::IsTrue(vec[i] == vec2[i]);
            }

            // 2 
            MaxHeap<int> heap2(0);
            vector<int> vec3;
            vec3 = heap2.heapSort();
            Assert::IsTrue(vec3.size() == 0);

            // 3
            MaxHeap<int> heap3(1);
            heap3.insert(80);
            vector<int> vec4;   
            vec4 = heap3.heapSort();
            Assert::IsTrue(vec4.size() == 1);
            Assert::IsTrue(vec4[0] == 80);


        }

    };
}