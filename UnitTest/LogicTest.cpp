#include "stdafx.h"
#include "CppUnitTest.h"
#include "Logic.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	TEST_CLASS(LogicTest)
	{
	public:
		
		TEST_METHOD(Logic_isNumber_Test)
		{
			Logic logic;
			Assert::AreEqual(logic.isNumber("3"), true);
			Assert::AreEqual(logic.isNumber("3a"), false);
		}

	};
}