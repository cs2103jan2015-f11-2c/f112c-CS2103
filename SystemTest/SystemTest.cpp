//@author A0111379H

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
			expectedFeedback = "Error: Not enough information to execute command.";
			Assert::AreEqual(tempFeedbackVector.back(),expectedFeedback);

			//Case 2: Add floating
			Assert::AreEqual(l.executeUserInput("add systemtest1;"),true);
			tempFeedbackVector = l.getFeedbackStrings();
			expectedFeedback = "added: systemtest1";
			Assert::AreEqual(tempFeedbackVector.back(),expectedFeedback);
			
			//Case 3: Add normal event
			Assert::AreEqual(l.executeUserInput("add systemtest2; 23-24apr 3-4pm"),true);
			tempFeedbackVector = l.getFeedbackStrings();
			expectedFeedback = "added: systemtest2, 23 April - 24 April 2015";
			Assert::AreEqual(tempFeedbackVector.back(),expectedFeedback);

			//Case 4: Add normal event with invalid dates
			Assert::AreEqual(l.executeUserInput("add systemtest3; 31apr"),false);
			tempFeedbackVector = l.getFeedbackStrings();
			expectedFeedback = "Error: Unknown date input.";
			Assert::AreEqual(tempFeedbackVector.back(),expectedFeedback);

			//Case 5: Add normal event with invalid hour input
			Assert::AreEqual(l.executeUserInput("add systemtest3; 23apr 11-13pm"),false);
			tempFeedbackVector = l.getFeedbackStrings();
			expectedFeedback = "Error: Invalid hour input for time.";
			Assert::AreEqual(tempFeedbackVector.back(),expectedFeedback);

			//Case 6: Add normal event with invalid min input
			Assert::AreEqual(l.executeUserInput("add systemtest3; 23apr 11.30-11.61pm"),false);
			tempFeedbackVector = l.getFeedbackStrings();
			expectedFeedback = "Error: Invalid minutes input for time.";
			Assert::AreEqual(tempFeedbackVector.back(),expectedFeedback);


			//Deadline events
			//Case 2: Add deadline event with no dates
			Assert::AreEqual(l.executeUserInput("add systemtest3; due"),false);
			tempFeedbackVector = l.getFeedbackStrings();
			expectedFeedback = "Error: Wrong formatting, not all information has been successfully recorded.";
			Assert::AreEqual(tempFeedbackVector.back(),expectedFeedback);

			//Case 2: Add deadline event
			Assert::AreEqual(l.executeUserInput("add systemtest3; due 27may 5pm"),true);
			tempFeedbackVector = l.getFeedbackStrings();
			expectedFeedback = "added: systemtest3, 27 May 2015, Wednesday";
			Assert::AreEqual(tempFeedbackVector.back(),expectedFeedback);

			//Case 3: Add deadline event with too many dates
			Assert::AreEqual(l.executeUserInput("add systemtest3; due 22-23may 11pm"),false);
			tempFeedbackVector = l.getFeedbackStrings();
			expectedFeedback = "Error: Exceeded maximum of 1 date input for deadline events.";
			Assert::AreEqual(tempFeedbackVector.back(),expectedFeedback);

			//Case 4: Add deadline event with too many time
			Assert::AreEqual(l.executeUserInput("add systemtest3; due 22may 10-11pm"),false);
			tempFeedbackVector = l.getFeedbackStrings();
			expectedFeedback = "Error: Exceeded maximum of 1 time input for deadline events";
			Assert::AreEqual(tempFeedbackVector.back(),expectedFeedback);

		}

		TEST_METHOD(System_Del_Event)
		{
			std::string expectedFeedback;
			std::vector<std::string> tempFeedbackVector;

			//Case 1: Del with no event name/index
			Assert::AreEqual(l.executeUserInput("del "),false);
			tempFeedbackVector = l.getFeedbackStrings();
			expectedFeedback = "Error: Not enough information to execute command.";
			Assert::AreEqual(tempFeedbackVector.back(),expectedFeedback);

			//Case 2: Del with event name
			l.executeUserInput("add systemtest4;");
			Assert::AreEqual(l.executeUserInput("del systemtest4"),true);
			tempFeedbackVector = l.getFeedbackStrings();
			expectedFeedback = "deleted: systemtest4";
			Assert::AreEqual(tempFeedbackVector.back(),expectedFeedback);
		}

		TEST_METHOD(System_Edit_Event)
		{
			std::string expectedFeedback;
			std::vector<std::string> tempFeedbackVector;
			l.executeUserInput("add systemtest5 28apr 5-6pm");

			//Case 1: Edit with no event name/index
			Assert::AreEqual(l.executeUserInput("edit "),false);
			tempFeedbackVector = l.getFeedbackStrings();
			expectedFeedback = "Error: Not enough information to execute command.";
			Assert::AreEqual(tempFeedbackVector.back(),expectedFeedback);

			//Case 3: Edit event name
			Assert::AreEqual(l.executeUserInput("edit systemtest5; systemtest6"),true);
			tempFeedbackVector = l.getFeedbackStrings();
			expectedFeedback = "edited: systemtest5, 28 April 2015, Tuesday";
			Assert::AreEqual(tempFeedbackVector.back(),expectedFeedback);

			//Case 4: Edit event date
			Assert::AreEqual(l.executeUserInput("edit systemtest6; 30apr"),true);
			tempFeedbackVector = l.getFeedbackStrings();
			expectedFeedback = "edited: systemtest6, 28 April 2015, Tuesday";
			Assert::AreEqual(tempFeedbackVector.back(),expectedFeedback);

			//Case 5: Edit event time
			Assert::AreEqual(l.executeUserInput("edit systemtest6; 10-11pm"),true);
			tempFeedbackVector = l.getFeedbackStrings();
			expectedFeedback = "edited: systemtest6, 30 April 2015, Thursday";
			Assert::AreEqual(tempFeedbackVector.back(),expectedFeedback);

			//Case 5: Multiple edits
			Assert::AreEqual(l.executeUserInput("edit systemtest6; systemtest7 10jun 10am-13jun 11pm"),true);
			tempFeedbackVector = l.getFeedbackStrings();
			expectedFeedback = "edited: systemtest6, 30 April 2015, Thursday";
			Assert::AreEqual(tempFeedbackVector.back(),expectedFeedback);

			//Case 6: Edit floating event
			l.executeUserInput("show float");
			Assert::AreEqual(l.executeUserInput("edit systemtest7; systemtest8"),true);
			tempFeedbackVector = l.getFeedbackStrings();
			expectedFeedback = "edited: systemtest7, 10 June - 13 June 2015";
			Assert::AreEqual(tempFeedbackVector.back(),expectedFeedback);
		}

		TEST_METHOD(System_Show_Event)
		{
			std::string expectedFeedback;
			std::vector<std::string> tempFeedbackVector;
		
			//Case 1: Show with no event name/index
			Assert::AreEqual(l.executeUserInput("show "),false);
			tempFeedbackVector = l.getFeedbackStrings();
			expectedFeedback = "Error: Not enough information to execute command.";
			Assert::AreEqual(tempFeedbackVector.back(),expectedFeedback);

			//Case 2: Show with no registered show-type
			Assert::AreEqual(l.executeUserInput("show cs"),false);
			tempFeedbackVector = l.getFeedbackStrings();
			expectedFeedback = "Error: No registered show found. Please use search instead.";
			Assert::AreEqual(tempFeedbackVector.back(),expectedFeedback);

			//Case 3: System-show type
			Assert::AreEqual(l.executeUserInput("show may"),true);
			tempFeedbackVector = l.getFeedbackStrings();
			expectedFeedback = "showing: 1 May - 31 May 2015";
			Assert::AreEqual(tempFeedbackVector.back(),expectedFeedback);

			//Case 4: User show type
			Assert::AreEqual(l.executeUserInput("show 23-24apr"),true);
			tempFeedbackVector = l.getFeedbackStrings();
			expectedFeedback = "showing: 23 April - 24 April 2015";
			Assert::AreEqual(tempFeedbackVector.back(),expectedFeedback);
		}


	};
}