#include "stdafx.h"
#include "CppUnitTest.h"

#include "Logic.cpp"
#include "LogicUpdater.cpp"
#include "Executor.cpp"
#include "Command.cpp"
#include "Conversion.cpp"
#include "EventFacade.cpp"
#include "EventOrganiser.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace SystemTest
{		
	TEST_CLASS(SystemTest1)
	{
	public:
		
		Logic l;

		TEST_METHOD(ADD_EVENT)
		{
			//Case 1: Add with no event name
			Assert::AreEqual(l.executeUserInput("add "),false);
			std::vector<std::string> tempVector = l.getFeedbackStrings();
			std::string expectedString = "Error: No event name found. Please type ';' after an event name.";
			Assert::AreEqual(tempVector[0],expectedString);

			//Case 1: Add floating
			Assert::AreEqual(l.executeUserInput("add cs1;"),true);
			
			//Case 2: Add normal event
			Assert::AreEqual(l.executeUserInput("add cs1; 23-24apr 3-4pm"),true);

			//Case 3: Add normal event, 
		}

	};
}