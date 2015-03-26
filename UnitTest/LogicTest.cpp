#include "stdafx.h"
#include "CppUnitTest.h"
#include "Logic.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	TEST_CLASS(LogicTest)
	{
	public:
		
		TEST_METHOD(ExecuteUserInput)
		{
			Logic logic;
			Assert::AreEqual(logic.executeUserInput("add float;"), true);
			Assert::AreEqual(logic.executeUserInput("add float"), false);
		}

	};
}