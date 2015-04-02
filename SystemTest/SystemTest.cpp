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
#include "Event.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace SystemTest
{		
	TEST_CLASS(SystemTest1)
	{
	public:
		
		Logic l;

		TEST_METHOD(ADD_EVENT)
		{
			std::string expectedFeedback;
			std::vector<std::string> tempFeedbackVector;

			//Case 1: Add with no event name
			Assert::AreEqual(l.executeUserInput("add "),false);
			tempFeedbackVector = l.getFeedbackStrings();
			expectedFeedback = "Error: Missing input.";
			Assert::AreEqual(tempFeedbackVector.back(),expectedFeedback);

			//Case 1: Add floating
			Assert::AreEqual(l.executeUserInput("add cs1;"),true);
			tempFeedbackVector = l.getFeedbackStrings();
			expectedFeedback = "cs1 added";
			Assert::AreEqual(tempFeedbackVector.back(),expectedFeedback);
			
			//Case 2: Add normal event
			Assert::AreEqual(l.executeUserInput("add cs2; 23-24apr 3-4pm"),true);
			tempFeedbackVector = l.getFeedbackStrings();
			expectedFeedback = "cs2 added: 23 April - 24 April 2015";
			Assert::AreEqual(tempFeedbackVector.back(),expectedFeedback);

			//Case 3: Add normal event, 
		}

	};
}