#include "pch.h"
#include "CppUnitTest.h"
#include "..//aois6/HashTable.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace HashTableTests
{
	TEST_CLASS(HashTableTests)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			HashTable ht(20, 0);
			ht.insert_cell("Абаев", "Тимур");
			ht.insert_cell("Бобков", "Андрей");
			ht.insert_cell("Видерт", "Руслан");
			ht.insert_cell("Гракова", "Наталья");

			ht.print_table();
			ht.delete_cell("Абаев");
			ht.insert_cell("Бобков", "Ибрагим");
			ht.print_table();
			Assert::AreEqual(string("Ибрагим"), ht.get_cell_data("Бобков"));
		}

		TEST_METHOD(TestMethod2)
		{
			HashTable ht(20, 0);

			ht.insert_cell("Ковалев", "Сергей");
			ht.insert_cell("Крикунов", "Евгений");
			ht.insert_cell("Кот", "Иван");
			ht.insert_cell("Давыденко", "Ирина");
			ht.insert_cell("Горбань", "Петр");
			ht.insert_cell("Данилов", "Павел");
			ht.insert_cell("Козлов", "Максим");
			ht.insert_cell("Азимов", "Александр");

			ht.print_table();

			ht.delete_cell("Ковалев");
			ht.insert_cell("Бобков", "Ибрагим");
			ht.print_table();
			Assert::AreEqual(string(""), ht.get_cell_data("Ковалев"));
		}

		TEST_METHOD(TestMethod3)
		{
			HashTable ht(20, 0);

			ht.insert_cell("Бобков", "Андрей");
			ht.insert_cell("Видерт", "Руслан");
			ht.insert_cell("Кожевников", "Константин");
			ht.insert_cell("Ковалев", "Сергей");
			ht.insert_cell("Кот", "Иван");
			ht.insert_cell("Давыденко", "Ирина");
			ht.insert_cell("Горбань", "Петр");
			ht.insert_cell("Азимов", "Александр");

			ht.print_table();

			ht.delete_cell("Абаев");
			ht.insert_cell("Бобков", "Ибрагим");
			Assert::AreEqual(string("Руслан"), ht.get_cell_data("Видерт"));

		}
	};
}
