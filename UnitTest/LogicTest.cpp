#include "stdafx.h"
#include "CppUnitTest.h"
#include "Logic.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	TEST_CLASS(LogicTest)
	{
	public:
		
		//equivalence partitions: empty string, string comprising only digits, string comprising digits and nondigits
		TEST_METHOD(Logic_isNumber_Test)
		{
			Logic logic;
			//only digits partition
			Assert::AreEqual(logic.isNumber("3"), true);
			//both digits and nondigits partition
			Assert::AreEqual(logic.isNumber("3a"), false);
		}

	};

	TEST_CLASS(CommandTest)
	{
	public:
		
		TEST_METHOD(ICommand_getIsFloating_Test)
		{
			/*Parser parser("add float;");
			EventStorage eventStore;
			Event addedEvent = parser.getEvent();
			
			ICommand* addCommand = new AddCommand(&eventStore, addedEvent);
			Executor executor;
			executor.execute(addCommand);

			Assert::AreEqual(addCommand->getIsFloating(), true);*/
		}

	};
}