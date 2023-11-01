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
        }

        /// <summary>
        /// Удаление из кучи
        /// </summary>
        TEST_METHOD(TestRemove)
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

            //vec.push_back(5);
            vec.push_back(10);
            vec.push_back(30);
            vec.push_back(7);
            vec.push_back(6);
            sort(vec.begin(), vec.end(), greater<>());

            heap.remove(5);
            Assert::IsTrue(heap.Size() == 4);

            vector<int> vec2 = heap.toVector();
            Assert::IsTrue(is_heap(vec2.begin(), vec2.end()));
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
        }

    };
}