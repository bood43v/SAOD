/// Тестирование класса хеш-таблица
/// @author Будаев Г.Б.
#include "pch.h"
#include "CppUnitTest.h"
#include "../HashTable.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestHash
{
	// Пример простой хеш-функции для целых чисел
	unsigned long HashFunc(int key) {
		return key % 10;
	}
	TEST_CLASS(UnitTestHash)
	{
	public:

		/// <summary>
		/// тест вставки
		/// </summary>
		TEST_METHOD(TestMethod_Insert)
		{
			HashTable<int> h1(10, HashFunc);
			h1.Insert(1);
			h1.Insert(2);
			h1.Insert(3);
			h1.Insert(4);
			h1.Insert(5);
			
			Assert::IsTrue(h1.Size() == 10);

			// вставка для одинакового хеша
			Assert::IsTrue(h1.CountElements() == 5);
			h1.Insert(25);
			h1.Insert(15);
			Assert::IsTrue(h1.CountElements() == 7);

			// повторяющийся элемент
			h1.Insert(15);
			Assert::IsTrue(h1.CountElements() == 7);

			Assert::IsTrue(h1.Find(1) == true);
			Assert::IsTrue(h1.Find(2) == true);
			Assert::IsTrue(h1.Find(3) == true);
			Assert::IsTrue(h1.Find(4) == true);
			Assert::IsTrue(h1.Find(5) == true);
			Assert::IsTrue(h1.Find(15) == true);
			Assert::IsTrue(h1.Find(25) == true);
		}
	
		/// <summary>
		/// тест поиска
		/// </summary>
		TEST_METHOD(TestMethod_Search)
		{
			HashTable<int> h1(10, HashFunc);
			h1.Insert(1);
			h1.Insert(2);
			h1.Insert(3);
			h1.Insert(4);
			h1.Insert(5);
			Assert::IsTrue(h1.Size() == 10);
						
			Assert::IsTrue(h1.Find(1) == true);
			Assert::IsTrue(h1.Find(2) == true);
			Assert::IsTrue(h1.Find(3) == true);
			Assert::IsTrue(h1.Find(4) == true);
			Assert::IsTrue(h1.Find(5) == true);

			// проверка после удаления
			h1.Delete(1);
			h1.Delete(2);
			h1.Delete(3);
			h1.Delete(4);
			h1.Delete(5);

			Assert::IsTrue(h1.Find(1) == false);
			Assert::IsTrue(h1.Find(2) == false);
			Assert::IsTrue(h1.Find(3) == false);
			Assert::IsTrue(h1.Find(4) == false);
			Assert::IsTrue(h1.Find(5) == false);
		}

		/// <summary>
		/// тест удаления
		/// </summary>
		TEST_METHOD(TestMethod_Delete)
		{
			HashTable<int> h1(10, HashFunc);
			h1.Insert(1);
			h1.Insert(2);
			h1.Insert(3);
			h1.Insert(4);
			h1.Insert(5);
			h1.Insert(25);
			h1.Insert(15);
			h1.Insert(15);
			Assert::IsTrue(h1.Size() == 10);
			Assert::IsTrue(h1.CountElements() == 7);

			Assert::IsTrue(h1.Find(1) == true);
			Assert::IsTrue(h1.Find(5) == true);
			Assert::IsTrue(h1.Find(5) == true);

			h1.Delete(1);
			h1.Delete(5);
			h1.Delete(15);

			Assert::IsTrue(h1.Find(1) == false);
			Assert::IsTrue(h1.Find(5) == false);
			Assert::IsTrue(h1.Find(5) == false);
			Assert::IsTrue(h1.CountElements() == 4);
		}

		/// <summary>
		/// тест изменения
		/// </summary>
		TEST_METHOD(TestMethod_Update)
		{
			HashTable<int> h1(10, HashFunc);
			h1.Insert(1);
			h1.Insert(2);
			h1.Insert(3);
			h1.Insert(4);
			h1.Insert(5);
			h1.Insert(25);
			h1.Insert(15);
			h1.Insert(15);
			Assert::IsTrue(h1.Size() == 10);
			Assert::IsTrue(h1.CountElements() == 7);
				
			Assert::IsTrue(h1.Find(5) == true);
			h1.Update(5, 555);
			// изменение элемента, которого нет -> добавление 100, без удаления 444, т.к. его не было.
			h1.Update(444, 100);

			Assert::IsTrue(h1.Find(5) == false);
			Assert::IsTrue(h1.Find(555) == true);
			Assert::IsTrue(h1.CountElements() == 8);
		}

		/// <summary>
		/// тест очистки таблицы
		/// </summary>
		TEST_METHOD(TestMethod_Clear)
		{
			HashTable<int> h1(10, HashFunc);
			h1.Insert(1);
			h1.Insert(2);
			h1.Insert(3);
			h1.Insert(4);
			h1.Insert(5);
			h1.Insert(25);
			h1.Insert(15);
			h1.Insert(15);
			Assert::IsTrue(h1.Size() == 10);
			Assert::IsTrue(h1.CountElements() == 7);

			h1.ClearList();
			Assert::IsTrue(h1.CountElements() == 0);
		}
	};
}
