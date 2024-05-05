#include "pch.h"
#include "CppUnitTest.h"
#include "..//aois2/logicExpr.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace LogicExprTests
{
	TEST_CLASS(LogicExprTests)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			LogicExpr a("q|w&!e");
			calculation_method(a);
			calculation_table_method(a);
			Assert::AreEqual(42, a.get_index_form());
		}
		TEST_METHOD(TestMethod2)
		{
			LogicExpr a("a-!(w|e~!w)");
			calculation_method(a);
			calculation_table_method(a);
			Assert::AreEqual(251, a.get_index_form());
		}
		TEST_METHOD(TestMethod3)
		{
			LogicExpr a("(a&!b)|(c&d)");
			calculation_method(a);
			calculation_table_method(a);
			Assert::AreEqual(4593, a.get_index_form());
		}
		TEST_METHOD(TestMethod4)
		{
			LogicExpr a("a~!(!b-c)");
			calculation_method(a);
			calculation_table_method(a);
			Assert::AreEqual(120, a.get_index_form());
		}
		TEST_METHOD(TestMethod5)
		{
			LogicExpr a("a&b|c-!a~b");
			calculation_method(a);
			calculation_table_method(a);
			Assert::AreEqual(52, a.get_index_form());
		}
	};
}
