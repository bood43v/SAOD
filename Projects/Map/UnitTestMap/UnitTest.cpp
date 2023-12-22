/// Тестирование работы класса Map на основе AVL Дерева
/// @author Будаев Г.Б.
#include "pch.h"
#include "../Map/Map.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestMap
{
    /// <summary>
    /// тестирования словаря на основе AVL дерева
    /// </summary>
    TEST_CLASS(UnitTestMap)
    {
    public:
        // Тестирование "вставки"
        TEST_METHOD(TestMethod_Main)
        {
            Map<string, unsigned> Dictionary(0);
            Dictionary["Laptops"] = 4;
            Dictionary["PCs"] = 5;
            Dictionary["Smartphones"] = 20;
            Dictionary["Watch"] = 10;

            // размер
            Assert::IsTrue(Dictionary.Size() == 4);

            // проверка значений
            Assert::IsTrue(Dictionary["Laptops"] == 4);
            Assert::IsTrue(Dictionary["PCs"] == 5);
            Assert::IsTrue(Dictionary["Smartphones"] == 20);
            Assert::IsTrue(Dictionary["Watch"] == 10);
        }

        // Тестирование удаления
        TEST_METHOD(TestMethod_Delete)
        {
            Map<string, unsigned> Dictionary(0);
            Dictionary["Laptops"] = 3;
            Dictionary["PCs"];
            Dictionary["Smartphones"] = 20;
            Dictionary["Watch"] = 10;
            
            Dictionary.DeleteKey("Laptops");

            Assert::IsTrue(Dictionary.Size() == 3);

            Assert::IsTrue(Dictionary["PCs"] == 0);
            Assert::IsTrue(Dictionary["Smartphones"] == 20);
            Assert::IsTrue(Dictionary["Watch"] == 10);
        }

        // Тестирование наличия
        TEST_METHOD(TestMethod_InDictionary)
        {
            Map<string, unsigned> Dictionary(0);
            Dictionary["Laptops"] = 4;
            Dictionary["PCs"] = 5;
            Dictionary["Smartphones"] = 20;
            Dictionary["Watch"] = 10;

            Dictionary.DeleteKey("Laptops");
            Assert::IsTrue(Dictionary.InDictionary("Laptops") == false);
            Assert::IsTrue(Dictionary.InDictionary("PCs") == true);
            Assert::IsTrue(Dictionary.InDictionary("Smartphones") == true);
            Assert::IsTrue(Dictionary.InDictionary("Watch") == true);
        }

        // Тестирование размера
        TEST_METHOD(TestMethod_Size)
        {
            Map<string, unsigned> Dictionary(0);
            Assert::IsTrue(Dictionary.Size() == 0);
            Dictionary["Laptops"] = 4;
            Dictionary["PCs"] = 5;
            Dictionary["Smartphones"] = 20;
            Dictionary["Watch"] = 10;

            Assert::IsTrue(Dictionary.Size() == 4);
            Dictionary.DeleteKey("PCs");
            Assert::IsTrue(Dictionary.Size() == 3);

            Dictionary.Clear();

            Assert::IsTrue(Dictionary.Size() == 0);
        }

        // Тестирование наличия
        TEST_METHOD(TestMethod_Clear)
        {
            Map<string, unsigned> Dictionary(0);
            Dictionary["Laptops"] = 4;
            Dictionary["PCs"] = 5;
            Dictionary["Smartphones"] = 20;
            Dictionary["Watch"] = 10;

            Dictionary.Clear();
            Assert::IsTrue(Dictionary.InDictionary("Laptops") == false);
            Assert::IsTrue(Dictionary.InDictionary("PCs") == false);
            Assert::IsTrue(Dictionary.InDictionary("Smartphones") == false);
            Assert::IsTrue(Dictionary.InDictionary("Watch") == false);

            Assert::IsTrue(Dictionary.Size() == 0);
        }
    };
}