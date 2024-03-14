#include "pch.h"
#include "CppUnitTest.h"
#include "..//aois_1/BinCode.cpp"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Aois1tests
{
	TEST_CLASS(Aois1tests)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			BinCode a(5);
			a.showStraightCode();
			a.showReverseCode();
			a.showAddCode();
			a.showNumber();
			BinCode b(7);
			b.showStraightCode();
			b.showReverseCode();
			b.showAddCode();
			b.showNumber();
			BinCode c = a + b;
			c.showStraightCode();
			c.showReverseCode();
			c.showAddCode();
			c.showNumber();
			Assert::AreEqual(12., c.getNumber());
		}

		TEST_METHOD(TestMethod2)
		{
			BinCode a(-5);
			a.showStraightCode();
			a.showReverseCode();
			a.showAddCode();
			a.showNumber();
			BinCode b(7);
			b.showStraightCode();
			b.showReverseCode();
			b.showAddCode();
			b.showNumber();
			BinCode c = a + b;
			c.showStraightCode();
			c.showReverseCode();
			c.showAddCode();
			c.showNumber();
			Assert::AreEqual(2., c.getNumber());
		}
		TEST_METHOD(TestMethod3)
		{
			BinCode a(5);
			a.showStraightCode();
			a.showReverseCode();
			a.showAddCode();
			a.showNumber();
			BinCode b(-7);
			b.showStraightCode();
			b.showReverseCode();
			b.showAddCode();
			b.showNumber();
			BinCode c = a + b;
			c.showStraightCode();
			c.showReverseCode();
			c.showAddCode();
			c.showNumber();
			Assert::AreEqual(-2., c.getNumber());
		}
		TEST_METHOD(TestMethod4)
		{
			BinCode a(5);
			a.showStraightCode();
			a.showReverseCode();
			a.showAddCode();
			a.showNumber();
			BinCode b(7);
			b.showStraightCode();
			b.showReverseCode();
			b.showAddCode();
			b.showNumber();
			BinCode c = a - b;
			c.showStraightCode();
			c.showReverseCode();
			c.showAddCode();
			c.showNumber();
			Assert::AreEqual(-2., c.getNumber());
		}
		TEST_METHOD(TestMethod5)
		{
			BinCode a(7.5);
			a.showFixedPointCode();
			a.showFloatPointCode();
			a.showNumber();
			BinCode b(5.125);
			b.showFixedPointCode();
			b.showFloatPointCode();
			b.showNumber();
			BinCode c = a % b;
			c.showFixedPointCode();
			c.showFloatPointCode();
			c.showNumber();
			Assert::AreEqual(12.625, c.getNumber());
		}
		TEST_METHOD(TestMethod6)
		{
			BinCode j(5.);
			BinCode h(-5.1234);
			BinCode p;
			BinCode f(-120);
			BinCode g(111);
			f + g;
			j.getNumber();
			f + p;
			BinCode a(-5);
			a.showStraightCode();
			a.showReverseCode();
			a.showAddCode();
			a.showNumber();
			BinCode b(-7);
			b.showStraightCode();
			b.showReverseCode();
			b.showAddCode();
			b.showNumber();
			BinCode c = a + b;
			c.showStraightCode();
			c.showReverseCode();
			c.showAddCode();
			c.showNumber();
			Assert::AreEqual(-12., c.getNumber());
		}
	};
}
