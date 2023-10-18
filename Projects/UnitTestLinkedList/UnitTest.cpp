#include "pch.h"
#include "CppUnitTest.h"
#include "../List/LinkedList.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestLinkedList
{
    TEST_CLASS(UnitTest1)
    {
    public:
        void Generate(LinkedList <int>* root_1, LinkedList<int>* root_2, LinkedList<int>* root_3, LinkedList<int>* root_4) {

            root_1->InsertAtTail(5);///  5 10 20 30 40
            root_1->InsertAtTail(10);
            root_1->InsertAtTail(20);                
            root_1->InsertAtTail(30);                       
            root_1->InsertAtTail(40);              

            root_2->InsertAtHead(1);/// 1

            root_3->InsertAtHead(7);/// 11 10 9 8 7
            root_3->InsertAtHead(8);
            root_3->InsertAtHead(9);
            root_3->InsertAtHead(10);
            root_3->InsertAtHead(11);

            root_4->InsertAtHead(1);/// 1 2 3 4
            root_4->InsertAfter(1,2);
            root_4->InsertAfter(2,3);
            root_4->InsertAfter(3,4);
        }

        /// <summary>
        /// Тест вставок в список и добавления в массив
        /// </summary>
        TEST_METHOD(Test_Insert_ToArray)
        {
            LinkedList<int>* L1 = new LinkedList<int>();
            LinkedList<int>* L2 = new LinkedList<int>();
            LinkedList<int>* L3 = new LinkedList<int>();
            LinkedList<int>* L4 = new LinkedList<int>();

            Generate(L1, L2, L3, L4);

            int* arr1 = new int[L1->Size()];
            arr1 = L1->ToListArray();
            Assert::IsTrue(L1->Size() == 5);
            Assert::IsTrue(arr1[0] == 5);
            Assert::IsTrue(arr1[1] == 10);
            Assert::IsTrue(arr1[2] == 20);
            Assert::IsTrue(arr1[3] == 30);
            Assert::IsTrue(arr1[4] == 40);

            int* arr2 = new int[L2->Size()];
            arr2 = L2->ToListArray();
            Assert::IsTrue(L2->Size() == 1);
            Assert::IsTrue(arr2[0] == 1);

            int* arr3 = new int[L3->Size()];
            arr3 = L3->ToListArray();
            Assert::IsTrue(L3->Size() == 5);
            Assert::IsTrue(arr3[0] == 11);
            Assert::IsTrue(arr3[1] == 10);
            Assert::IsTrue(arr3[2] == 9);
            Assert::IsTrue(arr3[3] == 8);
            Assert::IsTrue(arr3[4] == 7);

            int* arr4 = new int[L4->Size()];
            arr4 = L4->ToListArray();
            Assert::IsTrue(L4->Size() == 4);
            Assert::IsTrue(arr4[0] == 1);
            Assert::IsTrue(arr4[1] == 2);
            Assert::IsTrue(arr4[2] == 3);
            Assert::IsTrue(arr4[3] == 4);

        }
        TEST_METHOD(Test_Search)
        {
            LinkedList<int>* L1 = new LinkedList<int>();
            LinkedList<int>* L2 = new LinkedList<int>();
            LinkedList<int>* L3 = new LinkedList<int>();
            LinkedList<int>* L4 = new LinkedList<int>();

            Generate(L1, L2, L3, L4);

            Assert::IsTrue(L1->Search(5)->Data() == 5);
            Assert::IsTrue(L1->Search(20)->Data() == 20);
            Assert::IsTrue(L1->Search(40)->Data() == 40);

            Assert::IsTrue(L2->Search(1)->Data() == 1);
            Assert::IsTrue(L2->Search(222) == nullptr);
        }

        TEST_METHOD(Test_Remove)
        {
            LinkedList<int>* L1 = new LinkedList<int>();
            LinkedList<int>* L2 = new LinkedList<int>();
            LinkedList<int>* L3 = new LinkedList<int>();
            LinkedList<int>* L4 = new LinkedList<int>();

            Generate(L1, L2, L3, L4);

            L1->Remove(5);
            L1->Remove(20);
            L1->Remove(40);
            Assert::IsTrue(L1->Search(5) == nullptr);
            Assert::IsTrue(L1->Search(20) == nullptr);
            Assert::IsTrue(L1->Search(40) == nullptr);

            L2->Remove(1);
            Assert::IsTrue(L2->Search(1) == nullptr);
            Assert::IsTrue(L2->Search(222) == nullptr);
        }

    };
}