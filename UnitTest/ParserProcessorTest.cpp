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
		Event testOutput;
		std::vector<std::string> testInput;
		
		//extractFirstWord always find the first instance of a spacing and take what comes before the space
		TEST_METHOD(processAddEvent_Test)
		{
			//Case 1: One word, event name
			testInput.push_back("hello");
			expectedOutput.setName("hello");
			expectedOutput.setStartDate(0,0,0);
			expectedOutput.setEndDate(0,0,0);
			expectedOutput.setStartTime(0,0);
			expectedOutput.setIsDeadline(false);
			expectedOutput.setIsFloating(true);
			expectedOutput.setIsCompleted(false);
			expectedOutput.setImportanceLevel(0);
			testOutput = processor.processAddEvent(testInput);
			Assert::AreEqual(expectedOutput.getName(),testOutput.getName());
			Assert::AreEqual(expectedOutput.getStartDate().tm_mday,testOutput.getStartDate().tm_mday);
			Assert::AreEqual(expectedOutput.getStartDate().tm_mon,testOutput.getStartDate().tm_mon);
			Assert::AreEqual(expectedOutput.getStartDate().tm_year,testOutput.getStartDate().tm_year);
			Assert::AreEqual(expectedOutput.getStartDate().tm_hour,testOutput.getStartDate().tm_hour);
			Assert::AreEqual(expectedOutput.getStartDate().tm_min,testOutput.getStartDate().tm_min);
			Assert::AreEqual(expectedOutput.getIsDeadline(),testOutput.getIsDeadline());
			Assert::AreEqual(expectedOutput.getIsFloating(),testOutput.getIsFloating());
			Assert::AreEqual(expectedOutput.getIsCompleted(),testOutput.getIsCompleted());
			Assert::AreEqual(expectedOutput.getImportanceLevel(),testOutput.getImportanceLevel());

			/*
			//Case 2: One Word
			testInput = "add";
			testOutput = splitter.extractFirstWord(testInput);
			expectedOutput = "add";
			Assert::AreEqual(expectedOutput,testOutput);

			//Case 3: Multiple Words
			testInput = "add event; 17-18mar";
			testOutput = splitter.extractFirstWord(testInput);
			expectedOutput = "add";
			Assert::AreEqual(expectedOutput,testOutput);
			
			//Case 4: Multiple Words random input
			testInput = "ave;l233 o4,;s lkkk";
			testOutput = splitter.extractFirstWord(testInput);
			expectedOutput = "ave;l233";
			Assert::AreEqual(expectedOutput,testOutput);

			//Case 5: Input with starting spaces
			testInput = "     add";
			testOutput = splitter.extractFirstWord(testInput);
			expectedOutput = "";
			Assert::AreEqual(expectedOutput,testOutput);
			*/
		}
		
	};
}