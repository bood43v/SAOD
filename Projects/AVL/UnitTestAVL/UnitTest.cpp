#include "pch.h"
#include "CppUnitTest.h"
#include "../AVLTree/AVLTreeNode.h"
#include "../AVLTree/AVLTree.h"
//#include <iostream>
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestAVL
{
    TEST_CLASS(UnitTestAVLTreeNode)
    {
    public:
        void Generate(AVLTreeNode <int>* &root_1, AVLTreeNode <int>* &root_2, AVLTreeNode <int>* &root_3, AVLTreeNode <int>* &root_4, AVLTreeNode <int>* &root_5) {

            //root_1 = root_1->Insert(5);///          10 
            root_1 = root_1->Insert(10);///      5         30
            root_1 = root_1->Insert(20);///            20       40
            root_1 = root_1->Insert(30);///                           
            root_1 = root_1->Insert(40);///                          

            //root_2 = root_2->Insert(1); /// 1 узел 

            //root_3 = root_3->Insert(10);          10  
            root_3 = root_3->Insert(5);//       5        15
            root_3 = root_3->Insert(2);///  2     6   12
            root_3 = root_3->Insert(6);///
            root_3 = root_3->Insert(15);///           
            root_3 = root_3->Insert(12);///  

            //root_4 = root_4->Insert(10);///      5 
            root_4 = root_4->Insert(5);///     2      15
            root_4 = root_4->Insert(2);///         10    20  
            root_4 = root_4->Insert(15);///           
            root_4 = root_4->Insert(20);///  

            //root_5 = root_5->Insert(1);         1
            root_5 = root_5->Insert(0);///      0
        }

        /// <summary>
        /// тест вставки узла (без дублирования) и вывода дерева в массив
        /// </summary>
        TEST_METHOD(Test_Insert)
        {
            AVLTreeNode <int>* t1 = new AVLTreeNode<int>(5);
            AVLTreeNode <int>* t2 = new AVLTreeNode<int>(1);
            AVLTreeNode <int>* t3 = new AVLTreeNode<int>(10);
            AVLTreeNode <int>* t4 = new AVLTreeNode<int>(10);
            AVLTreeNode <int>* t5 = new AVLTreeNode<int>(1);
            Generate(t1, t2, t3, t4, t5);

            int i = 0;
            int* arr1 = new int[t1->Size()];
            t1->AddToArrayLNR(arr1, i);
            Assert::IsTrue(t1->Size() == 5);
            Assert::IsTrue(arr1[0] == 5);
            Assert::IsTrue(arr1[1] == 10);
            Assert::IsTrue(arr1[2] == 20);
            Assert::IsTrue(arr1[3] == 30);
            Assert::IsTrue(arr1[4] == 40);

            i = 0;
            int* arr2 = new int[t2->Size()];
            t2->AddToArrayLNR(arr2, i);
            Assert::IsTrue(arr2[0] == 1);

            i = 0;
            int* arr3 = new int[t3->Size()];
            t3->AddToArrayLNR(arr3, i);
            Assert::IsTrue(arr3[0] == 2);
            Assert::IsTrue(arr3[2] == 6);
            Assert::IsTrue(arr3[4] == 12);

            i = 0;
            int* arr4 = new int[t4->Size()];
            t4->AddToArrayLNR(arr4, i);
            Assert::IsTrue(arr4[0] == 2);
            Assert::IsTrue(arr4[1] == 5);
            Assert::IsTrue(arr4[2] == 10);
            Assert::IsTrue(arr4[3] == 15);
            Assert::IsTrue(arr4[4] == 20);

            i = 0;
            int* arr5 = new int[t5->Size()];
            t5->AddToArrayLNR(arr5, i);
            Assert::IsTrue(arr5[0] == 0);
            Assert::IsTrue(arr5[1] == 1);
        }

        TEST_METHOD(Test_Remove)
        {
            AVLTreeNode <int>* t1 = new AVLTreeNode<int>(5);
            AVLTreeNode <int>* t2 = new AVLTreeNode<int>(1);
            AVLTreeNode <int>* t3 = new AVLTreeNode<int>(10);
            AVLTreeNode <int>* t4 = new AVLTreeNode<int>(10);
            AVLTreeNode <int>* t5 = new AVLTreeNode<int>(1);
            Generate(t1, t2, t3, t4, t5);

            t1 = t1->Remove(5);
            int i = 0;
            int* arr1 = new int[t1->Size()];
            t1->AddToArrayLNR(arr1, i);
            Assert::IsTrue(arr1[0] == 10);
            Assert::IsTrue(arr1[1] == 20);
            Assert::IsTrue(arr1[2] == 30);
            Assert::IsTrue(arr1[3] == 40);

            t3 = t3->Remove(5);
            t3 = t3->Remove(15);
            i = 0;
            int* arr3 = new int[t3->Size()];
            t3->AddToArrayLNR(arr3, i);
            Assert::IsTrue(arr3[0] == 2);
            Assert::IsTrue(arr3[1] == 6);
            Assert::IsTrue(arr3[2] == 10);
            Assert::IsTrue(arr3[3] == 12);

            t4 = t4->Remove(2);
            t4 = t4->Remove(5);
            i = 0;
            int* arr4 = new int[t4->Size()];
            t4->AddToArrayLNR(arr4, i);
            Assert::IsTrue(arr4[0] == 10);
            Assert::IsTrue(arr4[1] == 15);
            Assert::IsTrue(arr4[2] == 20);

            t5 = t5->Remove(0);
            i = 0;
            int* arr5 = new int[t5->Size()];
            t5->AddToArrayLNR(arr5, i);
            Assert::IsTrue(arr5[0] == 1);


        }


        /// <summary>
        /// тест поиска по дереву
        /// </summary>
        TEST_METHOD(Test_Search)
        {
            AVLTreeNode <int>* t1 = new AVLTreeNode<int>(5);
            AVLTreeNode <int>* t2 = new AVLTreeNode<int>(1);
            AVLTreeNode <int>* t3 = new AVLTreeNode<int>(10);
            AVLTreeNode <int>* t4 = new AVLTreeNode<int>(10);
            AVLTreeNode <int>* t5 = new AVLTreeNode<int>(1);
            Generate(t1, t2, t3, t4, t5);

            // искомое значение
            int x = 5;
            Assert::IsTrue(t1->Search(x)->Data() == 5);
            x = 40;
            Assert::IsTrue(t1->Search(x)->Data() == 40);
            x = 7;
            Assert::IsTrue(t1->Search(x) == nullptr);

            x = 1;
            Assert::IsTrue(t2->Search(x)->Data() == 1);
            x = -2;
            Assert::IsTrue(t2->Search(x) == nullptr);

            x = 2;
            Assert::IsTrue((t3->Search(x))->Data() == 2);
            x = 15;
            Assert::IsTrue((t3->Search(x))->Data() == 15);
            x = 6;
            Assert::IsTrue((t3->Search(x))->Data() == 6);
            x = 116;
            Assert::IsTrue(t3->Search(x) == nullptr);

            x = 2;
            Assert::IsTrue((t4->Search(x))->Data() == 2);
            x = 20;
            Assert::IsTrue((t4->Search(x))->Data() == 20);

            x = 0;
            Assert::IsTrue((t5->Search(x))->Data() == 0);
            x = 1;
            Assert::IsTrue((t5->Search(x))->Data() == 1);
            x = 3;
            Assert::IsTrue(t5->Search(x) == nullptr);
        }
        
        /// <summary>
        /// тест количества узлов
        /// </summary>
        TEST_METHOD(Test_Size)
        {
            AVLTreeNode <int>* t1 = new AVLTreeNode<int>(5);
            AVLTreeNode <int>* t2 = new AVLTreeNode<int>(1);
            AVLTreeNode <int>* t3 = new AVLTreeNode<int>(10);
            AVLTreeNode <int>* t4 = new AVLTreeNode<int>(10);
            AVLTreeNode <int>* t5 = new AVLTreeNode<int>(1);
            Generate(t1, t2, t3, t4, t5);


            Assert::IsTrue(t1->Size() == 5);
            Assert::IsTrue(t2->Size() == 1);
            Assert::IsTrue(t3->Size() == 6);
            Assert::IsTrue(t4->Size() == 5);
            Assert::IsTrue(t5->Size() == 2);
        }

        /// <summary>
        /// тест глубины дерева
        /// </summary>
        TEST_METHOD(Test_Depth)
        {
            AVLTreeNode <int>* t1 = new AVLTreeNode<int>(5);
            AVLTreeNode <int>* t2 = new AVLTreeNode<int>(1);
            AVLTreeNode <int>* t3 = new AVLTreeNode<int>(10);
            AVLTreeNode <int>* t4 = new AVLTreeNode<int>(10);
            AVLTreeNode <int>* t5 = new AVLTreeNode<int>(1);
            Generate(t1, t2, t3, t4, t5);
            Assert::IsTrue(t1->Depth() == 2);
            Assert::IsTrue(t2->Depth() == 0);
            Assert::IsTrue(t3->Depth() == 2);
            Assert::IsTrue(t4->Depth() == 2);
            Assert::IsTrue(t5->Depth() == 1);
        }

        /// <summary>
        /// тест вывода дерева в массив
        /// </summary>
        TEST_METHOD(Test_AddToArray)
        {
            AVLTreeNode <int>* t1 = new AVLTreeNode<int>(5);
            AVLTreeNode <int>* t2 = new AVLTreeNode<int>(1);
            AVLTreeNode <int>* t3 = new AVLTreeNode<int>(10);
            AVLTreeNode <int>* t4 = new AVLTreeNode<int>(10);
            AVLTreeNode <int>* t5 = new AVLTreeNode<int>(1);
            Generate(t1, t2, t3, t4, t5);

            int* arr1 = new int[t1->Size()];
            int i = 0;
            t1->AddToArrayLNR(arr1, i);
            Assert::IsTrue(arr1[0] == 5);
            Assert::IsTrue(t1->Size() == 5);
            Assert::IsTrue(t1->Depth() == 2);

            i = 0;
            int* arr2 = new int[t2->Size()];
            t2->AddToArrayLNR(arr2, i);
            Assert::IsTrue(arr2[0] == 1);
            Assert::IsTrue(t2->Size() == 1);
            Assert::IsTrue(t2->Depth() == 0);

            i = 0;
            int* arr3 = new int[t3->Size()];
            t3->AddToArrayLNR(arr3, i);
            Assert::IsTrue(arr3[0] == 2);
            Assert::IsTrue(t3->Size() == 6);
            Assert::IsTrue(t3->Depth() == 2);

            i = 0;
            int* arr4 = new int[t4->Size()];
            t4->AddToArrayLNR(arr4, i);
            Assert::IsTrue(arr4[0] == 2);
            Assert::IsTrue(t4->Size() == 5);
            Assert::IsTrue(t4->Depth() == 2);

            i = 0;
            int* arr5 = new int[t5->Size()];
            t5->AddToArrayLNR(arr5, i);
            Assert::IsTrue(arr5[0] == 0);
            Assert::IsTrue(t5->Size() == 2);
            Assert::IsTrue(t5->Depth() == 1);
        }



        /// <summary>
        /// тест поиска родителя
        /// </summary>
        TEST_METHOD(Test_SearchParent)
        {
            AVLTreeNode <int>* t1 = new AVLTreeNode<int>(5);
            AVLTreeNode <int>* t2 = new AVLTreeNode<int>(1);
            AVLTreeNode <int>* t3 = new AVLTreeNode<int>(10);
            AVLTreeNode <int>* t4 = new AVLTreeNode<int>(10);
            AVLTreeNode <int>* t5 = new AVLTreeNode<int>(1);
            Generate(t1, t2, t3, t4, t5);

            // искомое значение
            int x = 5;
            Assert::IsTrue(t1->SearchParent(x)->Data() == 10);
            x = 40;
            Assert::IsTrue(t1->SearchParent(x)->Data() == 30);
            x = 7;
            Assert::IsTrue(t1->SearchParent(x) == nullptr);
            x = 10;
            Assert::IsTrue(t1->SearchParent(x) == nullptr);

            x = 1;
            Assert::IsTrue(t2->SearchParent(x) == nullptr);
            x = -2;
            Assert::IsTrue(t2->SearchParent(x) == nullptr);

            x = 2;
            Assert::IsTrue((t3->SearchParent(x))->Data() == 5);
            x = 15;
            Assert::IsTrue((t3->SearchParent(x))->Data() == 10);
            x = 6;
            Assert::IsTrue((t3->SearchParent(x))->Data() == 5);
            x = 116;
            Assert::IsTrue(t3->SearchParent(x) == nullptr);

            x = 2;
            Assert::IsTrue((t4->SearchParent(x))->Data() == 5);
            x = 20;
            Assert::IsTrue((t4->SearchParent(x))->Data() == 15);

            x = 0;
            Assert::IsTrue((t5->SearchParent(x))->Data() == 1);
            x = 1;
            Assert::IsTrue(t5->SearchParent(x) == nullptr);
            x = 3;
            Assert::IsTrue(t5->SearchParent(x) == nullptr);
        }

        /// <summary>
        /// Тест следующего наибольшего для узла
        /// </summary>
        TEST_METHOD(Test_Successor)
        {
            AVLTreeNode <int>* t1 = new AVLTreeNode<int>(5);
            AVLTreeNode <int>* t2 = new AVLTreeNode<int>(1);
            AVLTreeNode <int>* t3 = new AVLTreeNode<int>(10);
            AVLTreeNode <int>* t4 = new AVLTreeNode<int>(10);
            AVLTreeNode <int>* t5 = new AVLTreeNode<int>(1);
            Generate(t1, t2, t3, t4, t5);

            int y = 5;
            Assert::IsTrue((t1->Successor(y))->Data() == 10);
            y = 30;
            Assert::IsTrue((t1->Successor(y))->Data() == 40);
            y = 40;
            Assert::IsTrue((t1->Successor(y)) == nullptr);
            y = 999;
            Assert::IsTrue((t1->Successor(y)) == nullptr);

            y = 1;
            Assert::IsTrue((t2->Successor(y)) == nullptr);

            y = 5;
            Assert::IsTrue((t3->Successor(y))->Data() == 6);
            y = 6;
            Assert::IsTrue((t3->Successor(y))->Data() == 10);
            y = 10;
            Assert::IsTrue((t3->Successor(y))->Data() == 12);
            y = 12;
            Assert::IsTrue((t3->Successor(y))->Data() == 15);

            y = 5;
            Assert::IsTrue((t4->Successor(y))->Data() == 10);
            y = 10;
            Assert::IsTrue((t4->Successor(y))->Data() == 15);

        }

        
    };


    TEST_CLASS(UnitTestAVLTree)
    {
    public:
        void GenerateTrees(AVLTree <int>*& root_1, AVLTree <int>*& root_2, AVLTree <int>*& root_3, AVLTree <int>*& root_4, AVLTree <int>*& root_5) {

            root_1->Insert(5);///           10 
            root_1->Insert(10);///      5         30
            root_1->Insert(20);///            20       40
            root_1->Insert(30);///                           
            root_1->Insert(40);///                          

            root_2->Insert(1); /// 1 узел 

            root_3->Insert(10);//         10  
            root_3->Insert(5);//       5        15
            root_3->Insert(2);///  2     6   12
            root_3->Insert(6);///
            root_3->Insert(15);///           
            root_3->Insert(12);///  

            root_4->Insert(10);///      5 
            root_4->Insert(5);///     2      15
            root_4->Insert(2);///         10    20  
            root_4->Insert(15);///           
            root_4->Insert(20);///  

            root_5->Insert(1);//          1
            root_5->Insert(0);///      0
        }
        

        /// <summary>
        /// Тест поиска
        /// </summary>
        TEST_METHOD(Test_AVLTreeInsert)
        {
            AVLTree <int>* t1 = new AVLTree<int>();
            AVLTree <int>* t2 = new AVLTree<int>();
            AVLTree <int>* t3 = new AVLTree<int>();
            AVLTree <int>* t4 = new AVLTree<int>();
            AVLTree <int>* t5 = new AVLTree<int>();
            GenerateTrees(t1, t2, t3, t4, t5);

            Assert::IsTrue(t1->Search(5)->Data() == 5);
            Assert::IsTrue(t1->Search(10)->Data() == 10);
            Assert::IsTrue(t1->Search(20)->Data() == 20);
            Assert::IsTrue(t1->Search(30)->Data() == 30);
            Assert::IsTrue(t1->Search(40)->Data() == 40);

            Assert::IsTrue(t2->Search(1)->Data() == 1);

            Assert::IsTrue(t3->Search(2)->Data() == 2);
            Assert::IsTrue(t3->Search(5)->Data() == 5);
            Assert::IsTrue(t3->Search(6)->Data() == 6);
            Assert::IsTrue(t3->Search(10)->Data() == 10);
            Assert::IsTrue(t3->Search(12)->Data() == 12);
            Assert::IsTrue(t3->Search(15)->Data() == 15);


            int i = 0;
            int* arr1 = new int[t1->Size()];
            t1->AddToArrayLNR(arr1);
            Assert::IsTrue(t1->Size() == 5);
            Assert::IsTrue(arr1[0] == 5);
            Assert::IsTrue(arr1[1] == 10);
            Assert::IsTrue(arr1[2] == 20);
            Assert::IsTrue(arr1[3] == 30);
            Assert::IsTrue(arr1[4] == 40);

            i = 0;
            int* arr2 = new int[t2->Size()];
            t2->AddToArrayLNR(arr2);
            Assert::IsTrue(arr2[0] == 1);

            i = 0;
            int* arr3 = new int[t3->Size()];
            t3->AddToArrayLNR(arr3);
            Assert::IsTrue(arr3[0] == 2);
            Assert::IsTrue(arr3[2] == 6);
            Assert::IsTrue(arr3[4] == 12);

            i = 0;
            int* arr4 = new int[t4->Size()];
            t4->AddToArrayLNR(arr4);
            Assert::IsTrue(arr4[0] == 2);
            Assert::IsTrue(arr4[1] == 5);
            Assert::IsTrue(arr4[2] == 10);
            Assert::IsTrue(arr4[3] == 15);
            Assert::IsTrue(arr4[4] == 20);

            i = 0;
            int* arr5 = new int[t5->Size()];
            t5->AddToArrayLNR(arr5);
            Assert::IsTrue(arr5[0] == 0);
            Assert::IsTrue(arr5[1] == 1);
        }

        /// <summary>
        /// Тест размера
        /// </summary>
        TEST_METHOD(Test_TreeSize)
        {
            AVLTree <int>* t1 = new AVLTree<int>();
            AVLTree <int>* t2 = new AVLTree<int>();
            AVLTree <int>* t3 = new AVLTree<int>();
            AVLTree <int>* t4 = new AVLTree<int>();
            AVLTree <int>* t5 = new AVLTree<int>();
            GenerateTrees(t1, t2, t3, t4, t5);

            Assert::IsTrue(t1->Size() == 5);
            Assert::IsTrue(t2->Size() == 1);
            Assert::IsTrue(t3->Size() == 6);
            Assert::IsTrue(t4->Size() == 5);
            Assert::IsTrue(t5->Size() == 2);
        }

        /// <summary>
        /// Тест размера
        /// </summary>
        TEST_METHOD(Test_TreeDepth)
        {
            AVLTree <int>* t1 = new AVLTree<int>();
            AVLTree <int>* t2 = new AVLTree<int>();
            AVLTree <int>* t3 = new AVLTree<int>();
            AVLTree <int>* t4 = new AVLTree<int>();
            AVLTree <int>* t5 = new AVLTree<int>();
            GenerateTrees(t1, t2, t3, t4, t5);

            Assert::IsTrue(t1->Depth() == 2);
            Assert::IsTrue(t2->Depth() == 0);
            Assert::IsTrue(t3->Depth() == 2);
            Assert::IsTrue(t4->Depth() == 2);
            Assert::IsTrue(t5->Depth() == 1);
        }

        /// <summary>
        /// Тест max/min
        /// </summary>
        TEST_METHOD(Test_TreeMinMax)
        {
            AVLTree <int>* t1 = new AVLTree<int>();
            AVLTree <int>* t2 = new AVLTree<int>();
            AVLTree <int>* t3 = new AVLTree<int>();
            AVLTree <int>* t4 = new AVLTree<int>();
            AVLTree <int>* t5 = new AVLTree<int>();
            GenerateTrees(t1, t2, t3, t4, t5);

            Assert::IsTrue(t1->FindMax()->Data() == 40);
            Assert::IsTrue(t2->FindMax()->Data() == 1);
            Assert::IsTrue(t3->FindMax()->Data() == 15);
            Assert::IsTrue(t4->FindMax()->Data() == 20);
            Assert::IsTrue(t5->FindMax()->Data() == 1);

            Assert::IsTrue(t1->FindMin()->Data() == 5);
            Assert::IsTrue(t2->FindMin()->Data() == 1);
            Assert::IsTrue(t3->FindMin()->Data() == 2);
            Assert::IsTrue(t4->FindMin()->Data() == 2);
            Assert::IsTrue(t5->FindMin()->Data() == 0);
        }

        /// <summary>
        /// Тест max/min
        /// </summary>
        TEST_METHOD(Test_TreeSearch)
        {
            AVLTree <int>* t1 = new AVLTree<int>();
            AVLTree <int>* t2 = new AVLTree<int>();
            AVLTree <int>* t3 = new AVLTree<int>();
            AVLTree <int>* t4 = new AVLTree<int>();
            AVLTree <int>* t5 = new AVLTree<int>();
            GenerateTrees(t1, t2, t3, t4, t5);

            // искомое значение
            int x = 5;
            Assert::IsTrue(t1->Search(x)->Data() == 5);
            x = 40;
            Assert::IsTrue(t1->Search(x)->Data() == 40);
            x = 7;
            Assert::IsTrue(t1->Search(x) == nullptr);

            x = 1;
            Assert::IsTrue(t2->Search(x)->Data() == 1);
            x = -2;
            Assert::IsTrue(t2->Search(x) == nullptr);

            x = 2;
            Assert::IsTrue((t3->Search(x))->Data() == 2);
            x = 15;
            Assert::IsTrue((t3->Search(x))->Data() == 15);
            x = 6;
            Assert::IsTrue((t3->Search(x))->Data() == 6);
            x = 116;
            Assert::IsTrue(t3->Search(x) == nullptr);

            x = 2;
            Assert::IsTrue((t4->Search(x))->Data() == 2);
            x = 20;
            Assert::IsTrue((t4->Search(x))->Data() == 20);

            x = 0;
            Assert::IsTrue((t5->Search(x))->Data() == 0);
            x = 1;
            Assert::IsTrue((t5->Search(x))->Data() == 1);
            x = 3;
            Assert::IsTrue(t5->Search(x) == nullptr);
        }

        /// <summary>
        /// Тест max/min
        /// </summary>
        TEST_METHOD(Test_TreeSuccessor)
        {
            AVLTree <int>* t1 = new AVLTree<int>();
            AVLTree <int>* t2 = new AVLTree<int>();
            AVLTree <int>* t3 = new AVLTree<int>();
            AVLTree <int>* t4 = new AVLTree<int>();
            AVLTree <int>* t5 = new AVLTree<int>();
            GenerateTrees(t1, t2, t3, t4, t5);

            int y = 5;
            Assert::IsTrue((t1->Successor(y))->Data() == 10);
            y = 30;
            Assert::IsTrue((t1->Successor(y))->Data() == 40);
            y = 40;
            Assert::IsTrue((t1->Successor(y)) == nullptr);
            y = 999;
            Assert::IsTrue((t1->Successor(y)) == nullptr);

            y = 1;
            Assert::IsTrue((t2->Successor(y)) == nullptr);

            y = 5;
            Assert::IsTrue((t3->Successor(y))->Data() == 6);
            y = 6;
            Assert::IsTrue((t3->Successor(y))->Data() == 10);   // почему-то не проходит, successor у 6 = nullptr
            y = 10;
            Assert::IsTrue((t3->Successor(y))->Data() == 12);
            y = 12;
            Assert::IsTrue((t3->Successor(y))->Data() == 15);

            y = 5;
            Assert::IsTrue((t4->Successor(y))->Data() == 10);
            y = 10;
            Assert::IsTrue((t4->Successor(y))->Data() == 15);
        }


        /// <summary>
        /// тест вывода дерева в массив
        /// </summary>
        TEST_METHOD(Test_TreeAddToArray)
        {
            AVLTree <int>* t1 = new AVLTree<int>();
            AVLTree <int>* t2 = new AVLTree<int>();
            AVLTree <int>* t3 = new AVLTree<int>();
            AVLTree <int>* t4 = new AVLTree<int>();
            AVLTree <int>* t5 = new AVLTree<int>();
            GenerateTrees(t1, t2, t3, t4, t5);

            int* arr1 = new int[t1->Size()];
            int i = 0;
            t1->AddToArrayLNR(arr1);
            Assert::IsTrue(arr1[0] == 5);
            Assert::IsTrue(t1->Size() == 5);
            Assert::IsTrue(t1->Depth() == 2);

            i = 0;
            int* arr2 = new int[t2->Size()];
            t2->AddToArrayLNR(arr2);
            Assert::IsTrue(arr2[0] == 1);
            Assert::IsTrue(t2->Size() == 1);
            Assert::IsTrue(t2->Depth() == 0);

            i = 0;
            int* arr3 = new int[t3->Size()];
            t3->AddToArrayLNR(arr3);
            Assert::IsTrue(arr3[0] == 2);
            Assert::IsTrue(t3->Size() == 6);
            Assert::IsTrue(t3->Depth() == 2);

            i = 0;
            int* arr4 = new int[t4->Size()];
            t4->AddToArrayLNR(arr4);
            Assert::IsTrue(arr4[0] == 2);
            Assert::IsTrue(t4->Size() == 5);
            Assert::IsTrue(t4->Depth() == 2);

            i = 0;
            int* arr5 = new int[t5->Size()];
            t5->AddToArrayLNR(arr5);
            Assert::IsTrue(arr5[0] == 0);
            Assert::IsTrue(t5->Size() == 2);
            Assert::IsTrue(t5->Depth() == 1);
        }

        /// <summary>
        /// Тест копирование дерева
        /// </summary>
        TEST_METHOD(Test_TreeRemove)
        {
            AVLTree <int>* t1 = new AVLTree<int>();
            AVLTree <int>* t2 = new AVLTree<int>();
            AVLTree <int>* t3 = new AVLTree<int>();
            AVLTree <int>* t4 = new AVLTree<int>();
            AVLTree <int>* t5 = new AVLTree<int>();
            GenerateTrees(t1, t2, t3, t4, t5);

            int i = 0;

            t1->Remove(5);
            int* arr1 = new int[t1->Size()];
            t1->AddToArrayLNR(arr1);
            Assert::IsTrue(arr1[0] == 10);
            Assert::IsTrue(arr1[1] == 20);
            Assert::IsTrue(arr1[2] == 30);
            Assert::IsTrue(arr1[3] == 40);

            t3->Remove(5);
            t3->Remove(15);
            i = 0;
            int* arr3 = new int[t3->Size()];
            t3->AddToArrayLNR(arr3);
            Assert::IsTrue(arr3[0] == 2);
            Assert::IsTrue(arr3[1] == 6);
            Assert::IsTrue(arr3[2] == 10);
            Assert::IsTrue(arr3[3] == 12);

            t4->Remove(2);
            t4->Remove(5);
            i = 0;
            int* arr4 = new int[t4->Size()];
            t4->AddToArrayLNR(arr4);
            Assert::IsTrue(arr4[0] == 10);
            Assert::IsTrue(arr4[1] == 15);
            Assert::IsTrue(arr4[2] == 20);

            t5->Remove(0);
            i = 0;
            int* arr5 = new int[t5->Size()];
            t5->AddToArrayLNR(arr5);
            Assert::IsTrue(arr5[0] == 1);
        }

        /// <summary>
        /// Тест копирование дерева
        /// </summary>
        TEST_METHOD(Test_TreeApply)
        {
            AVLTree <int>* t1 = new AVLTree<int>();
            AVLTree <int>* t2 = new AVLTree<int>();
            AVLTree <int>* t3 = new AVLTree<int>();
            AVLTree <int>* t4 = new AVLTree<int>();
            AVLTree <int>* t5 = new AVLTree<int>();
            GenerateTrees(t1, t2, t3, t4, t5);

            // Для первого дерева
            apply(t1->Root(), double_);
            int i = 0;
            int* arr1 = new int[t1->Size()];
            t1->AddToArrayLNR(arr1);
            for (int i = 0; i < t1->Size(); i++)
            {
                Assert::IsTrue(arr1[0] == 10);
                Assert::IsTrue(arr1[1] == 20);
                Assert::IsTrue(arr1[2] == 40);
                Assert::IsTrue(arr1[3] == 60);
                Assert::IsTrue(arr1[4] == 80);
            }

            // Для второго дерева
            apply(t2->Root(), double_);
            i = 0;
            int* arr2 = new int[t2->Size()];
            t2->AddToArrayLNR(arr2);
            for (int i = 0; i < t2->Size(); i++)
            {
                Assert::IsTrue(arr2[0] == 2);
            }

            // Для третьего дерева
            apply(t3->Root(), double_);
            i = 0;
            int* arr3 = new int[t3->Size()];
            t3->AddToArrayLNR(arr3);
            for (int i = 0; i < t3->Size(); i++)
            {
                Assert::IsTrue(arr3[0] == 4);
                Assert::IsTrue(arr3[1] == 10);
                Assert::IsTrue(arr3[2] == 12);
                Assert::IsTrue(arr3[3] == 20);
                Assert::IsTrue(arr3[4] == 24);
                Assert::IsTrue(arr3[5] == 30);
            }

            // Для четвертого дерева
            apply(t4->Root(), double_);
            i = 0;
            int* arr4 = new int[t4->Size()];
            t4->AddToArrayLNR(arr4);
            for (int i = 0; i < t4->Size(); i++)
            {
                Assert::IsTrue(arr4[0] == 4);
                Assert::IsTrue(arr4[1] == 10);
                Assert::IsTrue(arr4[2] == 20);
                Assert::IsTrue(arr4[3] == 30);
                Assert::IsTrue(arr4[4] == 40);
            }

            // Для пятого дерева
            apply(t5->Root(), double_);
            i = 0;
            int* arr5 = new int[t5->Size()];
            t5->AddToArrayLNR(arr5);
            for (int i = 0; i < t5->Size(); i++)
            {
                Assert::IsTrue(arr5[0] == 0);
                Assert::IsTrue(arr5[1] == 2);
            }
        }

        /// <summary>
         /// Тест работы итератора дерева
        /// </summary>
        TEST_METHOD(Test_Iterator)
        {
            AVLTree <int>* t1 = new AVLTree<int>();
            AVLTree <int>* t2 = new AVLTree<int>();
            AVLTree <int>* t3 = new AVLTree<int>();
            AVLTree <int>* t4 = new AVLTree<int>();
            AVLTree <int>* t5 = new AVLTree<int>();
            GenerateTrees(t1, t2, t3, t4, t5);

            /// Первое дерево
            /// Создание массива
            int* arr = new int[t1->Size()]{ 5, 10, 20, 30, 40 };
            /// Сравнение результата работы итератора с выводом из массива
            int i = 0;
            for (AVLTree<int>::Iterator<int> it = t1->begin(); it != t1->end(); ++it) {
                Assert::IsTrue(*it == arr[i]);
                i++;
            }
            //for (int x : *t1) {
            //    cout << x;
            //}

            /// Итератор второго дерева
            int* arr2 = new int[t2->Size()]{ 1 };
            i = 0;
            for (AVLTree<int>::Iterator<int> it = t2->begin(); it != t2->end(); ++it) {
                Assert::IsTrue(*it == arr2[i]);
                i++;
            }

            /// Итератор третьего дерева
            int* arr3 = new int[t3->Size()]{ 2, 5, 6, 10, 12, 15 };
            i = 0;
            for (AVLTree<int>::Iterator<int> it = t3->begin(); it != t3->end(); ++it) {
                Assert::IsTrue(*it == arr3[i]);
                i++;
            }

            /// Итератор четвертого дерева
            int* arr4 = new int[t4->Size()]{ 2, 5, 10, 15, 20 };
            i = 0;
            for (AVLTree<int>::Iterator<int> it = t4->begin(); it != t4->end(); ++it) {
                Assert::IsTrue(*it == arr4[i]);
                i++;
            }

            /// Итератор пятого дерева
            int* arr5 = new int[t5->Size()]{ 0, 1 };
            i = 0;
            for (AVLTree<int>::Iterator<int> it = t5->begin(); it != t5->end(); ++it) {
                Assert::IsTrue(*it == arr5[i]);
                i++;
            }
        }
    };

}