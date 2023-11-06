/// ������������ ������ ������ Heap
/// @author ������ �.�.

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
        ///  �������� �� �����
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

            // ���� �� ������ ��������
            MaxHeap<int> heap2(1);
            heap2.insert(999);
            Assert::IsTrue(heap2.Size() == 1);
            heap2.insert(1);
            Assert::IsTrue(heap2.Size() == 2);

            // ���� ��� ��������� � ������� � ��
            MaxHeap<int> heap3(0);
            Assert::IsTrue(heap3.Size() == 0);
            heap3.insert(22);
            Assert::IsTrue(heap3.Size() == 1);


        }

        /// <summary>
        /// ������������ ������� � ����
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

            // ���� �� ������ ��������
            MaxHeap<int> heap2(1);
            heap2.insert(999);
            Assert::IsTrue(heap2.Size() == 1);
            Assert::IsTrue(heap2.Max() == 999);
            Assert::IsTrue(heap2.Size() == 0);
            

            // ���� ��� ���������
            MaxHeap<int> heap3(0);
            Assert::IsTrue(heap3.Size() == 0);
            
            // ���� ��� ���������
            MaxHeap<int> heap4(0);
            Assert::IsTrue(heap3.Size() == 0);
            heap4.insert(999);
            Assert::IsTrue(heap4.Max() == 999);
            Assert::IsTrue(heap4.Size() == 0);

            
        }

        /// <summary>
        /// �������� �� ����
        /// </summary>
        TEST_METHOD(TestRemove)
        {
            ///         30
            ///     7       10
            ///  5     6
            /// ������� ���� � ����������� ������ (���������������)
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

            // ������� ������� �� ����
            heap.remove(5);
            // ��������� �������� ����
            vector<int> vec3 = heap.toVector();
            Assert::IsTrue(is_heap(vec3.begin(), vec3.end()));

            // ��������� ����������� ���� � ������� Max()
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


            /// ������� ������ ����
            MaxHeap<int> heap2(0);
            Assert::IsTrue(heap2.Size() == 0);
            heap2.remove(5);
            Assert::IsTrue(heap2.Size() == 0);


            /// ������� �� ������ ����
            MaxHeap<int> heap3(1);
            heap3.insert(5);
            Assert::IsTrue(heap3.Size() == 1);
            heap2.remove(5);
            Assert::IsTrue(heap2.Size() == 0);
        }

        /// <summary>
        /// ���������� � ������� ����
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