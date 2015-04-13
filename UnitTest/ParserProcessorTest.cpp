//@author A0111379H

#include "stdafx.h"
#include "CppUnitTest.h"
#include "ParserProcessor.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	TEST_CLASS(ParserProcessorTest)
	{
	public:
		ParserProcessor processor;
		Event expectedOutput;
		std::vector<std::string> testInput;
		
		//extractFirstWord always find the first instance of a spacing and take what comes before the space
		TEST_METHOD(processAddEvent_Test)
		{
			//Case 1: One word, event name only
			Event testOutput1;
			testInput.push_back("hello");
			expectedOutput.setName("hello");
			expectedOutput.setStartDate(0,0,0);
			expectedOutput.setEndDate(0,0,0);
			expectedOutput.setStartTime(0,0);
			expectedOutput.setIsDeadline(false);
			expectedOutput.setIsFloating(true);
			expectedOutput.setIsCompleted(false);
			expectedOutput.setImportanceLevel(0);
			testOutput1 = processor.processAddEvent(testInput);
			Assert::AreEqual(expectedOutput.getName(),testOutput1.getName());
			Assert::AreEqual(expectedOutput.getStartDate().tm_mday,testOutput1.getStartDate().tm_mday);
			Assert::AreEqual(expectedOutput.getStartDate().tm_mon,testOutput1.getStartDate().tm_mon);
			Assert::AreEqual(expectedOutput.getStartDate().tm_year,testOutput1.getStartDate().tm_year);
			Assert::AreEqual(expectedOutput.getStartDate().tm_hour,testOutput1.getStartDate().tm_hour);
			Assert::AreEqual(expectedOutput.getStartDate().tm_min,testOutput1.getStartDate().tm_min);
			Assert::AreEqual(expectedOutput.getIsDeadline(),testOutput1.getIsDeadline());
			Assert::AreEqual(expectedOutput.getIsFloating(),testOutput1.getIsFloating());
			Assert::AreEqual(expectedOutput.getIsCompleted(),testOutput1.getIsCompleted());
			Assert::AreEqual(expectedOutput.getImportanceLevel(),testOutput1.getImportanceLevel());

			testInput.clear();

			//Case 2: Full event information
			Event testOutput2;
			testInput.push_back("testing1 testing2 ");
			testInput.push_back("!! ");
			testInput.push_back("22");
			testInput.push_back("apr ");
			testInput.push_back("3");
			testInput.push_back("am ");
			testInput.push_back("to");
			testInput.push_back("3");
			testInput.push_back("may ");
			testInput.push_back("5.30");
			testInput.push_back("pm ");
			expectedOutput.setName("testing1 testing2");
			expectedOutput.setStartDate(22,3,115);
			expectedOutput.setEndDate(3,4,115);
			expectedOutput.setStartTime(3,0);
			expectedOutput.setEndTime(17,30);
			expectedOutput.setIsDeadline(false);
			expectedOutput.setIsFloating(false);
			expectedOutput.setIsCompleted(false);
			expectedOutput.setImportanceLevel(2);
			testOutput2 = processor.processAddEvent(testInput);
			Assert::AreEqual(expectedOutput.getName(),testOutput2.getName());
			Assert::AreEqual(expectedOutput.getStartDate().tm_mday,testOutput2.getStartDate().tm_mday);
			Assert::AreEqual(expectedOutput.getStartDate().tm_mon,testOutput2.getStartDate().tm_mon);
			Assert::AreEqual(expectedOutput.getStartDate().tm_year,testOutput2.getStartDate().tm_year);
			Assert::AreEqual(expectedOutput.getStartDate().tm_hour,testOutput2.getStartDate().tm_hour);
			Assert::AreEqual(expectedOutput.getStartDate().tm_min,testOutput2.getStartDate().tm_min);
			Assert::AreEqual(expectedOutput.getEndDate().tm_mday,testOutput2.getEndDate().tm_mday);
			Assert::AreEqual(expectedOutput.getEndDate().tm_mon,testOutput2.getEndDate().tm_mon);
			Assert::AreEqual(expectedOutput.getEndDate().tm_year,testOutput2.getEndDate().tm_year);
			Assert::AreEqual(expectedOutput.getEndDate().tm_hour,testOutput2.getEndDate().tm_hour);
			Assert::AreEqual(expectedOutput.getEndDate().tm_min,testOutput2.getEndDate().tm_min);
			Assert::AreEqual(expectedOutput.getIsDeadline(),testOutput2.getIsDeadline());
			Assert::AreEqual(expectedOutput.getIsCompleted(),testOutput2.getIsCompleted());
			Assert::AreEqual(expectedOutput.getImportanceLevel(),testOutput2.getImportanceLevel());

			testInput.clear();
		}
	
		TEST_METHOD(processEditEvent_Test)
		{
			//Case 1: One word, event name only
			Event testOutput1;
			testInput.push_back("hello");
			expectedOutput.setName("hello");
			expectedOutput.setStartDate(100,100,100);
			expectedOutput.setEndDate(100,100,100);
			expectedOutput.setStartTime(100,100);
			expectedOutput.setIsDeadline(false);
			expectedOutput.setIsFloating(false);
			expectedOutput.setIsCompleted(false);
			expectedOutput.setImportanceLevel(0);
			testOutput1 = processor.processEditEvent(testInput);
			Assert::AreEqual(expectedOutput.getName(),testOutput1.getName());
			Assert::AreEqual(expectedOutput.getStartDate().tm_mday,testOutput1.getStartDate().tm_mday);
			Assert::AreEqual(expectedOutput.getStartDate().tm_mon,testOutput1.getStartDate().tm_mon);
			Assert::AreEqual(expectedOutput.getStartDate().tm_year,testOutput1.getStartDate().tm_year);
			Assert::AreEqual(expectedOutput.getStartDate().tm_hour,testOutput1.getStartDate().tm_hour);
			Assert::AreEqual(expectedOutput.getStartDate().tm_min,testOutput1.getStartDate().tm_min);
			Assert::AreEqual(expectedOutput.getIsDeadline(),testOutput1.getIsDeadline());
			Assert::AreEqual(expectedOutput.getIsFloating(),testOutput1.getIsFloating());
			Assert::AreEqual(expectedOutput.getIsCompleted(),testOutput1.getIsCompleted());
			Assert::AreEqual(expectedOutput.getImportanceLevel(),testOutput1.getImportanceLevel());

			testInput.clear();

			//Case 2: Full event information
			Event testOutput2;
			testInput.push_back("testing1 testing2 ");
			testInput.push_back("!! ");
			testInput.push_back("22");
			testInput.push_back("apr ");
			testInput.push_back("3");
			testInput.push_back("am ");
			testInput.push_back("to");
			testInput.push_back("3");
			testInput.push_back("may ");
			testInput.push_back("5.30");
			testInput.push_back("pm ");
			expectedOutput.setName("testing1 testing2");
			expectedOutput.setStartDate(22,3,115);
			expectedOutput.setEndDate(3,4,115);
			expectedOutput.setStartTime(3,0);
			expectedOutput.setEndTime(17,30);
			expectedOutput.setIsDeadline(false);
			expectedOutput.setIsFloating(false);
			expectedOutput.setIsCompleted(false);
			expectedOutput.setImportanceLevel(2);
			testOutput2 = processor.processEditEvent(testInput);
			Assert::AreEqual(expectedOutput.getName(),testOutput2.getName());
			Assert::AreEqual(expectedOutput.getStartDate().tm_mday,testOutput2.getStartDate().tm_mday);
			Assert::AreEqual(expectedOutput.getStartDate().tm_mon,testOutput2.getStartDate().tm_mon);
			Assert::AreEqual(expectedOutput.getStartDate().tm_year,testOutput2.getStartDate().tm_year);
			Assert::AreEqual(expectedOutput.getStartDate().tm_hour,testOutput2.getStartDate().tm_hour);
			Assert::AreEqual(expectedOutput.getStartDate().tm_min,testOutput2.getStartDate().tm_min);
			Assert::AreEqual(expectedOutput.getEndDate().tm_mday,testOutput2.getEndDate().tm_mday);
			Assert::AreEqual(expectedOutput.getEndDate().tm_mon,testOutput2.getEndDate().tm_mon);
			Assert::AreEqual(expectedOutput.getEndDate().tm_year,testOutput2.getEndDate().tm_year);
			Assert::AreEqual(expectedOutput.getEndDate().tm_hour,testOutput2.getEndDate().tm_hour);
			Assert::AreEqual(expectedOutput.getEndDate().tm_min,testOutput2.getEndDate().tm_min);
			Assert::AreEqual(expectedOutput.getIsDeadline(),testOutput2.getIsDeadline());
			Assert::AreEqual(expectedOutput.getIsCompleted(),testOutput2.getIsCompleted());
			Assert::AreEqual(expectedOutput.getImportanceLevel(),testOutput2.getImportanceLevel());

			testInput.clear();
		}

		TEST_METHOD(processShowEvent_Test)
		{
			//Case 1: Single day
			Event testOutput1;
			testInput.push_back("24");
			testInput.push_back("apr");
			expectedOutput.setName("");
			expectedOutput.setStartDate(24,3,115);
			expectedOutput.setEndDate(24,3,115);
			expectedOutput.setStartTime(0,0);
			expectedOutput.setIsDeadline(false);
			expectedOutput.setIsFloating(false);
			expectedOutput.setIsCompleted(false);
			expectedOutput.setImportanceLevel(0);
			testOutput1 = processor.processShowEvent(testInput);
			Assert::AreEqual(expectedOutput.getName(),testOutput1.getName());
			Assert::AreEqual(expectedOutput.getStartDate().tm_mday,testOutput1.getStartDate().tm_mday);
			Assert::AreEqual(expectedOutput.getStartDate().tm_mon,testOutput1.getStartDate().tm_mon);
			Assert::AreEqual(expectedOutput.getStartDate().tm_year,testOutput1.getStartDate().tm_year);
			Assert::AreEqual(expectedOutput.getStartDate().tm_hour,testOutput1.getStartDate().tm_hour);
			Assert::AreEqual(expectedOutput.getStartDate().tm_min,testOutput1.getStartDate().tm_min);
			Assert::AreEqual(expectedOutput.getIsDeadline(),testOutput1.getIsDeadline());
			Assert::AreEqual(expectedOutput.getIsFloating(),testOutput1.getIsFloating());
			Assert::AreEqual(expectedOutput.getIsCompleted(),testOutput1.getIsCompleted());
			Assert::AreEqual(expectedOutput.getImportanceLevel(),testOutput1.getImportanceLevel());

			testInput.clear();

			//Case 2: Multiple days
			Event testOutput2;
			testInput.push_back("22");
			testInput.push_back("to");
			testInput.push_back("25");
			testInput.push_back("may");
			expectedOutput.setName("");
			expectedOutput.setStartDate(22,4,115);
			expectedOutput.setEndDate(25,4,115);
			expectedOutput.setStartTime(0,0);
			expectedOutput.setEndTime(0,0);
			expectedOutput.setIsDeadline(false);
			expectedOutput.setIsFloating(false);
			expectedOutput.setIsCompleted(false);
			expectedOutput.setImportanceLevel(0);
			testOutput2 = processor.processShowEvent(testInput);
			Assert::AreEqual(expectedOutput.getName(),testOutput2.getName());
			Assert::AreEqual(expectedOutput.getStartDate().tm_mday,testOutput2.getStartDate().tm_mday);
			Assert::AreEqual(expectedOutput.getStartDate().tm_mon,testOutput2.getStartDate().tm_mon);
			Assert::AreEqual(expectedOutput.getStartDate().tm_year,testOutput2.getStartDate().tm_year);
			Assert::AreEqual(expectedOutput.getStartDate().tm_hour,testOutput2.getStartDate().tm_hour);
			Assert::AreEqual(expectedOutput.getStartDate().tm_min,testOutput2.getStartDate().tm_min);
			Assert::AreEqual(expectedOutput.getEndDate().tm_mday,testOutput2.getEndDate().tm_mday);
			Assert::AreEqual(expectedOutput.getEndDate().tm_mon,testOutput2.getEndDate().tm_mon);
			Assert::AreEqual(expectedOutput.getEndDate().tm_year,testOutput2.getEndDate().tm_year);
			Assert::AreEqual(expectedOutput.getEndDate().tm_hour,testOutput2.getEndDate().tm_hour);
			Assert::AreEqual(expectedOutput.getEndDate().tm_min,testOutput2.getEndDate().tm_min);
			Assert::AreEqual(expectedOutput.getIsDeadline(),testOutput2.getIsDeadline());
			Assert::AreEqual(expectedOutput.getIsCompleted(),testOutput2.getIsCompleted());
			Assert::AreEqual(expectedOutput.getImportanceLevel(),testOutput2.getImportanceLevel());

			testInput.clear();
		}
	};
}