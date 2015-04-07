#include "stdafx.h"
#include "CppUnitTest.h"
#include "Logic.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	TEST_CLASS(LogicTest)
	{
	public:
		Logic logic;

		TEST_METHOD(Logic_isProperCommand_Test)
		{
			//test partition of valid parser command
			Assert::AreEqual(logic.isProperCommand(Parser::ADD), true);
		}


		TEST_METHOD(Logic_isNumber_Test)
		{
			//test partition of string with only nondigits
			string s = "ab!@";
			Assert::AreEqual(logic.isNumber(s), false);


			//test partition of string with only digits
			s = "1234";
			Assert::AreEqual(logic.isNumber(s), true);


			//test partition of string with both digits and nondigits
			s = "1234ab!@";
			Assert::AreEqual(logic.isNumber(s), false);
		}


		TEST_METHOD(Logic_isSameDate_Test)
		{
			//test partition of both dates same
			tm first, second;
			first.tm_mday = 1;
			first.tm_mon = 1;
			first.tm_year = 115;
			second.tm_mday = 1;
			second.tm_mon = 1;
			second.tm_year = 115;
			Assert::AreEqual(logic.isSameDate(first, second), true);


			//test partition of only day different


			//test partition of only month different


			//test partition of only year different


			//test partition of day and month different


			//test partition of day and year different


			//test partition of month and year different


			//test partition of day and month and year different

		}

	};

/**
* @author A0111089L
*/
}