/// ������������ ������ ���-�������
/// @author ������ �.�.
#include "pch.h"
#include "CppUnitTest.h"
#include "../HashTable.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestHash
{
	// ������ ������� ���-������� ��� ����� �����
	unsigned long HashFunc(int key) {
		return key % 10;
	}
	TEST_CLASS(UnitTestHash)
	{
	public:

		/// <summary>
		/// ���� �������
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

			// ������� ��� ����������� ����
			Assert::IsTrue(h1.CountElements() == 5);
			h1.Insert(25);
			h1.Insert(15);
			Assert::IsTrue(h1.CountElements() == 7);

			// ������������� �������
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
		/// ���� ������
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

			// �������� ����� ��������
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
		/// ���� ��������
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
		/// ���� ���������
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
			// ��������� ��������, �������� ��� -> ���������� 100, ��� �������� 444, �.�. ��� �� ����.
			h1.Update(444, 100);

			Assert::IsTrue(h1.Find(5) == false);
			Assert::IsTrue(h1.Find(555) == true);
			Assert::IsTrue(h1.CountElements() == 8);
		}

		/// <summary>
		/// ���� ������� �������
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
