#include "pch.h"
#include "CppUnitTest.h"
#include"..//aois7/Table.cpp"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Microsoft {
	namespace VisualStudio {
		namespace CppUnitTestFramework {
			template<>
			std::wstring ToString<std::vector<bool>>(const std::vector<bool>& vec) {
				std::wstringstream wss;
				wss << L"{ ";
				for (size_t i = 0; i < vec.size(); ++i) {
					wss << (vec[i] ? L"true" : L"false");
					if (i < vec.size() - 1) {
						wss << L", ";
					}
				}
				wss << L" }";
				return wss.str();
			}
		}
	}
}

namespace TableTests
{
	TEST_CLASS(TableTests)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			vector<vector<bool>> table1 = {
	   {0, 1, 0, 1, 0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0},
	   {1, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0},	
	   {0, 1, 1, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 1, 0},
	   {1, 0, 0, 0, 1, 0, 1, 1, 1, 0, 0, 1, 0, 1, 0, 1},
	   {1, 1, 0, 1, 0, 1, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0},
	   {0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 1, 1, 0, 1, 0, 1},
	   {1, 0, 1, 0, 1, 0, 0, 0, 1, 1, 0, 1, 1, 1, 0, 1},
	   {0, 1, 1, 0, 1, 1, 0, 1, 0, 0, 0, 0, 1, 0, 1, 1},
	   {0, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 0, 1},
	   {1, 1, 0, 0, 1, 1, 0, 1, 0, 1, 0, 0, 1, 1, 1, 0},
	   {0, 0, 1, 1, 0, 0, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1},
	   {0, 1, 0, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0},
	   {1, 1, 1, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0},
	   {0, 1, 0, 1, 1, 0, 1, 0, 0, 1, 0, 0, 1, 1, 1, 0},
	   {1, 0, 0, 1, 0, 1, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1},
	   {0, 1, 1, 0, 0, 1, 0, 0, 1, 1, 0, 1, 0, 1, 1, 0}
			};
			Table tb1(table1);
			vector<bool> row;
			tb1.do_function_4(0, 1, 5);
			Assert::AreEqual(vector<bool>({ 0,0,0,0,0,0,0,0,1,0,1,1,0,0,0,1 }) , tb1.get_word(5));
			tb1.do_function_6(2, 3, 7);
			Assert::AreEqual(vector<bool>({ 1,1,1,1,1,0,1,1,1,0,0,1,0,0,0,0 }), tb1.get_word(7));
			tb1.do_function_9(3, 12, 15);
			Assert::AreEqual(vector<bool>({ 1,1,0,1,0,1,1,0,1,1,1,1,0,1,0,1 }), tb1.get_word(15));
			tb1.do_function_11(5, 8, 11);
			Assert::AreEqual(vector<bool>({ 0,1,1,0,1,1,0,0,1,0,1,1,0,1,0,1 }), tb1.get_word(11));
			tb1.show_table();
			Assert::AreEqual(vector<bool>({0, 0, 0, 1, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0}), tb1.get_address_column(7));
		}

		TEST_METHOD(TestMethod2)
		{
			vector<vector<bool>> table2 = {
	{1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0},
	{0, 1, 1, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 1, 1},
	{1, 0, 0, 1, 1, 0, 1, 0, 0, 1, 1, 1, 0, 0, 0, 1},
	{0, 0, 1, 1, 0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1},
	{1, 1, 1, 0, 0, 1, 1, 0, 1, 0, 1, 0, 1, 1, 0, 0},
	{0, 1, 0, 0, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 0, 0},
	{1, 0, 0, 1, 1, 0, 1, 0, 1, 1, 0, 0, 1, 0, 0, 1},
	{0, 0, 1, 0, 1, 0, 0, 1, 1, 1, 1, 0, 1, 1, 0, 0},
	{1, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0},
	{0, 1, 1, 0, 1, 1, 0, 1, 0, 1, 0, 0, 0, 1, 1, 0},
	{1, 0, 1, 1, 0, 0, 0, 1, 1, 1, 0, 1, 0, 1, 0, 0},
	{0, 0, 1, 0, 1, 1, 1, 1, 0, 1, 0, 1, 1, 0, 1, 0},
	{1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 0},
	{0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 0, 1, 0},
	{1, 0, 1, 1, 0, 0, 1, 0, 1, 0, 1, 0, 0, 1, 1, 0},
	{0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 1}
			};
			Table tb2(table2);
			tb2.sum_words({ 1, 0, 0 });
			Assert::AreEqual(vector<bool>({ 1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,0 }), tb2.get_word(1));
			tb2.update_address_column({ 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0 }, 4);
			tb2.show_vec(tb2.get_address_column(4));
			tb2.show_vec(tb2.get_word(1));
			Assert::AreEqual(vector<bool>({ 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0 }), tb2.get_address_column(4));
		}

		TEST_METHOD(TestMethod3)
		{
			vector<vector<bool>> table3 = {
	{0, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 0},
	{1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 0, 1, 1, 1, 0},
	{0, 1, 1, 0, 1, 1, 0, 0, 1, 0, 0, 1, 1, 0, 0, 1},
	{1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1, 0, 1},
	{0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 1, 1, 1, 0, 1, 0},
	{1, 0, 0, 1, 1, 0, 1, 0, 1, 0, 0, 1, 1, 0, 1, 1},
	{0, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0},
	{1, 0, 0, 1, 1, 0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0},
	{0, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 0, 1, 0, 0, 1},
	{1, 0, 0, 1, 1, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1},
	{0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 1, 0, 1, 0},
	{1, 0, 0, 1, 0, 1, 1, 0, 1, 1, 0, 0, 1, 0, 1, 0},
	{0, 1, 1, 0, 1, 0, 0, 1, 0, 1, 1, 0, 1, 1, 0, 1},
	{1, 0, 0, 1, 1, 0, 1, 1, 0, 1, 0, 1, 0, 0, 1, 1},
	{0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 1, 0, 1, 0},
	{1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1, 0, 0}
			};
			Table tb3(table3);
			tb3.sort_table();
			Assert::AreEqual(vector<bool>({ 1, 0, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 1 }), tb3.get_address_column(4));
			tb3.update_address_column({ 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1, 0, 0 }, 4);
			tb3.update_word({ 1, 0, 0, 1, 0, 1, 1, 0, 1, 1, 0, 0, 1, 0, 1, 0 }, 7);
			Assert::AreEqual(vector<bool>({0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0}), tb3.get_word(1));
		}

	};
}
