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
			first.tm_mday = 2;
			first.tm_mon = 1;
			first.tm_year = 115;
			second.tm_mday = 1;
			second.tm_mon = 1;
			second.tm_year = 115;
			Assert::AreEqual(logic.isSameDate(first, second), false);


			//test partition of only month different
			first.tm_mday = 1;
			first.tm_mon = 2;
			first.tm_year = 115;
			second.tm_mday = 1;
			second.tm_mon = 1;
			second.tm_year = 115;
			Assert::AreEqual(logic.isSameDate(first, second), false);


			//test partition of only year different
			first.tm_mday = 1;
			first.tm_mon = 1;
			first.tm_year = 116;
			second.tm_mday = 1;
			second.tm_mon = 1;
			second.tm_year = 115;
			Assert::AreEqual(logic.isSameDate(first, second), false);


			//test partition of day and month different
			first.tm_mday = 2;
			first.tm_mon = 2;
			first.tm_year = 115;
			second.tm_mday = 1;
			second.tm_mon = 1;
			second.tm_year = 115;
			Assert::AreEqual(logic.isSameDate(first, second), false);


			//test partition of day and year different
			first.tm_mday = 2;
			first.tm_mon = 1;
			first.tm_year = 116;
			second.tm_mday = 1;
			second.tm_mon = 1;
			second.tm_year = 115;
			Assert::AreEqual(logic.isSameDate(first, second), false);


			//test partition of month and year different
			first.tm_mday = 1;
			first.tm_mon = 2;
			first.tm_year = 116;
			second.tm_mday = 1;
			second.tm_mon = 1;
			second.tm_year = 115;
			Assert::AreEqual(logic.isSameDate(first, second), false);


			//test partition of day and month and year different
			first.tm_mday = 2;
			first.tm_mon = 2;
			first.tm_year = 116;
			second.tm_mday = 1;
			second.tm_mon = 1;
			second.tm_year = 115;
			Assert::AreEqual(logic.isSameDate(first, second), false);
		}


		TEST_METHOD(Logic_removeLabel_Test)
		{
			//test partition of label in front of desired string
			string input = "[DAY] 8 April", expected = "8 April";
			logic.removeLabel(input);
			Assert::AreEqual(input, expected);

			//test partition of no label in front of desired string
			input = "8 April", expected = "8 April";
			logic.removeLabel(input);
			Assert::AreEqual(input, expected);
		}
	};

/**
* @author A0111089L
*/
}