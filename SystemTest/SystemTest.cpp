#include "stdafx.h"
#include "CppUnitTest.h"

#include "Logic.cpp"
#include "LogicUpdater.cpp"
#include "Executor.cpp"
#include "Command.cpp"
#include "Conversion.cpp"
#include "EventFacade.cpp"
#include "EventOrganiser.cpp"
#include "EventModifier.cpp"
#include "EventSearch.cpp"
#include "EventStorage.cpp"
#include "Parser.cpp"
#include "ParserProcessor.cpp"
#include "InputStringSplit.cpp"
#include "ParserLog.cpp"
#include "EventLog.cpp"
#include "ParserExceptions.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace SystemTest
{		
	TEST_CLASS(SystemTest1)
	{
	public:
		
		Logic l;

		TEST_METHOD(ADD_EVENT)
		{
			std::string textLine, testString;
			std::string expectedString;

			std::string expectedString;
			std::vector<std::string> tempVector;

			//Case 1: Add with no event name
			Assert::AreEqual(l.executeUserInput("add "),false);
			tempVector = l.getFeedbackStrings();
			expectedString = "Error: No event name found. Please type ';' after an event name.";
			Assert::AreEqual(tempVector[0],expectedString);

			//Case 1: Add floating
			Assert::AreEqual(l.executeUserInput("add cs1;"),true);
			expectedString = "Is Floating: 1\nName: cs1\nStart Year: 0\nStart Month: 0\nStart Day: 0\nStart Hour: 0\n";
			expectedString += "Start Min: 0\nEnd Year: 0\nEnd Month: 0\nEnd Day: 0\nEnd Hour: 0\nEnd Min: 0\n";
			expectedString += "Deadline: 0\nCompleted: 0\nImportance: 0\n";
			
			//Case 2: Add normal event
			Assert::AreEqual(l.executeUserInput("add cs1; 23-24apr 3-4pm"),true);

			//Case 3: Add normal event, 
		}

	};
}