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
			Assert::AreEqual(42, a.get_index_form());
		}
		TEST_METHOD(TestMethod2)
		{
			LogicExpr a("a-!(w|e~!w)");
			Assert::AreEqual(251, a.get_index_form());
		}
		TEST_METHOD(TestMethod3)
		{
			LogicExpr a("(a&!b)|(c&d)");
			Assert::AreEqual(4593, a.get_index_form());
		}
		TEST_METHOD(TestMethod4)
		{
			LogicExpr a("a~!(!b-c)");
			Assert::AreEqual(120, a.get_index_form());
		}
		TEST_METHOD(TestMethod5)
		{
			LogicExpr a("a&b|c-!a~b");
			Assert::AreEqual(52, a.get_index_form());
		}
	};
}
