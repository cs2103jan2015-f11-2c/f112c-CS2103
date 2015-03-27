#include "stdafx.h"
#include "CppUnitTest.h"
#include "ParserProcessor.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	TEST_CLASS(ParserProcessorTest)
	{
	public:
		/*
		ParserProcessor processor;
		std::string testInput;
		std::string testOutput;
		std::string expectedOutput;
		
		//extractFirstWord always find the first instance of a spacing and take what comes before the space
		TEST_METHOD(extractFirstWord_Test)
		{
			//Case 1: Empty string
			testInput = "";
			expectedOutput = ParserExceptions::ERROR_MISSING_INPUT;
			try {
				testOutput = splitter.extractFirstWord(testInput);
			} catch (ParserExceptions& e){
				testOutput = e.getExceptionCode();
			}
			Assert::AreEqual(expectedOutput,testOutput);

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
		}
		*/
	};
}