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

		TEST_METHOD(System_Add_Event)
		{
			std::string expectedFeedback;
			std::vector<std::string> tempFeedbackVector;

			//Normal events
			//Case 1: Add with no event name
			Assert::AreEqual(l.executeUserInput("add "),false);
			tempFeedbackVector = l.getFeedbackStrings();
			expectedFeedback = "Error: Missing input.";
			Assert::AreEqual(tempFeedbackVector.back(),expectedFeedback);

			//Case 2: Add floating
			Assert::AreEqual(l.executeUserInput("add cs1;"),true);
			tempFeedbackVector = l.getFeedbackStrings();
			expectedFeedback = "cs1 added";
			Assert::AreEqual(tempFeedbackVector.back(),expectedFeedback);
			
			//Case 3: Add normal event
			Assert::AreEqual(l.executeUserInput("add cs2; 23-24apr 3-4pm"),true);
			tempFeedbackVector = l.getFeedbackStrings();
			expectedFeedback = "cs2 added: 23 April - 24 April 2015";
			Assert::AreEqual(tempFeedbackVector.back(),expectedFeedback);

			//Case 4: Add normal event with invalid dates
			Assert::AreEqual(l.executeUserInput("add cs2; 31apr"),false);
			tempFeedbackVector = l.getFeedbackStrings();
			expectedFeedback = "Error: Unknown date input.";
			Assert::AreEqual(tempFeedbackVector.back(),expectedFeedback);

			//Case 5: Add normal event with invalid hour input
			Assert::AreEqual(l.executeUserInput("add cs2; 23apr 11-13pm"),false);
			tempFeedbackVector = l.getFeedbackStrings();
			expectedFeedback = "Error: Invalid hour input for time.";
			Assert::AreEqual(tempFeedbackVector.back(),expectedFeedback);

			//Case 6: Add normal event with invalid min input
			Assert::AreEqual(l.executeUserInput("add cs2; 23apr 11.30-11.61pm"),false);
			tempFeedbackVector = l.getFeedbackStrings();
			expectedFeedback = "Error: Invalid minutes input for time.";
			Assert::AreEqual(tempFeedbackVector.back(),expectedFeedback);


			//Deadline events
			//Case 2: Add deadline event with no dates
			Assert::AreEqual(l.executeUserInput("add cs3; due"),false);
			tempFeedbackVector = l.getFeedbackStrings();
			expectedFeedback = "Error: Wrong formatting, not all information has been successfully recorded.";
			Assert::AreEqual(tempFeedbackVector.back(),expectedFeedback);

			//Case 2: Add deadline event
			Assert::AreEqual(l.executeUserInput("add cs3; due 27may 5pm"),true);
			tempFeedbackVector = l.getFeedbackStrings();
			expectedFeedback = "cs3 added: 27 May, Wednesday";
			Assert::AreEqual(tempFeedbackVector.back(),expectedFeedback);

			//Case 3: Add deadline event with too many dates
			Assert::AreEqual(l.executeUserInput("add cs3; due 22-23may 11pm"),false);
			tempFeedbackVector = l.getFeedbackStrings();
			expectedFeedback = "Error: Too many date inputs detected. Maximum of 1 date input for deadline events.";
			Assert::AreEqual(tempFeedbackVector.back(),expectedFeedback);

			//Case 4: Add deadline event with too many time
			Assert::AreEqual(l.executeUserInput("add cs3; due 22may 10-11pm"),false);
			tempFeedbackVector = l.getFeedbackStrings();
			expectedFeedback = "Error: Too many time inputs detected. Maximum of 1 time input for deadline events";
			Assert::AreEqual(tempFeedbackVector.back(),expectedFeedback);

		}

		TEST_METHOD(System_Del_Event)
		{
			std::string expectedFeedback;
			std::vector<std::string> tempFeedbackVector;

			//Case 1: Del with no event name/index
			Assert::AreEqual(l.executeUserInput("del "),false);
			tempFeedbackVector = l.getFeedbackStrings();
			expectedFeedback = "Error: Missing input.";
			Assert::AreEqual(tempFeedbackVector.back(),expectedFeedback);

			//Case 2: Del with event name
			l.executeUserInput("add cs4; 24apr");
			Assert::AreEqual(l.executeUserInput("del cs4;"),true);
			tempFeedbackVector = l.getFeedbackStrings();
			expectedFeedback = "cs4 deleted";
			Assert::AreEqual(tempFeedbackVector.back(),expectedFeedback);
			
			//Case 3: Del with event index
			l.executeUserInput("add cs1;");
			Assert::AreEqual(l.executeUserInput("del 1"),true);
			tempFeedbackVector = l.getFeedbackStrings();
			expectedFeedback = "cs1 deleted";
			Assert::AreEqual(tempFeedbackVector.back(),expectedFeedback);
			
			//Case 4: Del with more than 1 event index
			Assert::AreEqual(l.executeUserInput("del 2 3"),false);
			tempFeedbackVector = l.getFeedbackStrings();
			expectedFeedback = "Error: Too many inputs detected. Input index only, or event name only ending with ';'.";
			Assert::AreEqual(tempFeedbackVector.back(),expectedFeedback);
		}

		TEST_METHOD(System_Edit_Event)
		{
			std::string expectedFeedback;
			std::vector<std::string> tempFeedbackVector;
			l.executeUserInput("add cs5; 21apr 5-6pm");

			//Case 1: Edit with no event name/index
			Assert::AreEqual(l.executeUserInput("edit "),false);
			tempFeedbackVector = l.getFeedbackStrings();
			expectedFeedback = "Error: Missing input.";
			Assert::AreEqual(tempFeedbackVector.back(),expectedFeedback);

			//Case 2: Edit with event name/index but no additional input
			Assert::AreEqual(l.executeUserInput("edit cs5;"),false);
			tempFeedbackVector = l.getFeedbackStrings();
			expectedFeedback = "Error: Not enough information to execute command.";
			Assert::AreEqual(tempFeedbackVector.back(),expectedFeedback);

			//Case 3: Edit event name
			Assert::AreEqual(l.executeUserInput("edit 1 cs6;"),true);
			tempFeedbackVector = l.getFeedbackStrings();
			expectedFeedback = "cs5 edited";
			Assert::AreEqual(tempFeedbackVector.back(),expectedFeedback);

			//Case 4: Edit event date
			Assert::AreEqual(l.executeUserInput("edit 1 26may"),true);
			tempFeedbackVector = l.getFeedbackStrings();
			expectedFeedback = "cs6 edited";
			Assert::AreEqual(tempFeedbackVector.back(),expectedFeedback);

			//Case 5: Edit event time
			Assert::AreEqual(l.executeUserInput("edit 1 10-11pm"),true);
			tempFeedbackVector = l.getFeedbackStrings();
			expectedFeedback = "cs6 edited";
			Assert::AreEqual(tempFeedbackVector.back(),expectedFeedback);

			//Case 5: Multiple edits
			Assert::AreEqual(l.executeUserInput("edit 1 cs7; 10jun 10am-13jun 11pm"),true);
			tempFeedbackVector = l.getFeedbackStrings();
			expectedFeedback = "cs6 edited";
			Assert::AreEqual(tempFeedbackVector.back(),expectedFeedback);

			//Case 6: Edit floating event
			l.executeUserInput("show float");
			Assert::AreEqual(l.executeUserInput("edit 1 cs8;"),true);
			tempFeedbackVector = l.getFeedbackStrings();
			expectedFeedback = "cs1 edited";
			Assert::AreEqual(tempFeedbackVector.back(),expectedFeedback);
		}

		TEST_METHOD(System_Show_Event)
		{
			std::string expectedFeedback;
			std::vector<std::string> tempFeedbackVector;
		
			//Case 1: Show with no event name/index
			Assert::AreEqual(l.executeUserInput("show "),false);
			tempFeedbackVector = l.getFeedbackStrings();
			expectedFeedback = "Error: Missing input.";
			Assert::AreEqual(tempFeedbackVector.back(),expectedFeedback);

			//Case 2: Show with no registered show-type
			Assert::AreEqual(l.executeUserInput("show cs"),false);
			tempFeedbackVector = l.getFeedbackStrings();
			expectedFeedback = "Error: No registered show found. Please use search instead.";
			Assert::AreEqual(tempFeedbackVector.back(),expectedFeedback);

			//Case 3: System-show type
			Assert::AreEqual(l.executeUserInput("show mth"),true);
			tempFeedbackVector = l.getFeedbackStrings();
			expectedFeedback = "showing mth";
			Assert::AreEqual(tempFeedbackVector.back(),expectedFeedback);

			//Case 4: User show type
			Assert::AreEqual(l.executeUserInput("show 23-24apr"),true);
			tempFeedbackVector = l.getFeedbackStrings();
			expectedFeedback = "showing 23-24apr";
			Assert::AreEqual(tempFeedbackVector.back(),expectedFeedback);
		}


	};
}