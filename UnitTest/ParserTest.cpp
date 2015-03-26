#include "stdafx.h"
#include "CppUnitTest.h"
#include "Parser.cpp"
#include "InputStringSplit.cpp"
#include "ParserProcessor.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	TEST_CLASS(ParserTest)
	{
	public:
		
		InputStringSplit splitter;
		ParserProcessor processor;
		std::string testInput;
		std::string testOutput;
		std::string expectedOutput;
		
		//extractFirstWord always find the first instance of a spacing and take what comes before the space
		TEST_METHOD(extractFirstWord_Test)
		{
			//Case 1: One Word
			testInput = "add";
			testOutput = splitter.extractFirstWord(testInput);
			expectedOutput = "add";
			Assert::AreEqual(expectedOutput,testOutput);

			//Case 2: Multiple Words
			testInput = "add event; 17-18mar";
			testOutput = splitter.extractFirstWord(testInput);
			expectedOutput = "add";
			Assert::AreEqual(expectedOutput,testOutput);
			
			//Case 3: Multiple Words random input
			testInput = "ave;l233 o4,;s lkkk";
			testOutput = splitter.extractFirstWord(testInput);
			expectedOutput = "ave;l233";
			Assert::AreEqual(expectedOutput,testOutput);

			//Case 4: Input with starting spaces
			testInput = "     add";
			testOutput = splitter.extractFirstWord(testInput);
			expectedOutput = "";
			Assert::AreEqual(expectedOutput,testOutput);
		}

		//Finds the first non spacing after the first spacing and takes the whole string after that
		TEST_METHOD(extractDetails_Test)
		{
			//Case 1: Multiple Words
			testInput = "add event; 17-18mar";
			testOutput = splitter.extractDetails(testInput);
			expectedOutput = "event; 17-18mar";
			Assert::AreEqual(expectedOutput,testOutput);
			
			//Case 2: Multiple Words random input
			testInput = "ave;l233 o4,;s lkkk";
			testOutput = splitter.extractDetails(testInput);
			expectedOutput = "o4,;s lkkk";
			Assert::AreEqual(expectedOutput,testOutput);

			//Case 3: Input with starting spaces
			testInput = "     add";
			testOutput = splitter.extractDetails(testInput);
			expectedOutput = "add";
			Assert::AreEqual(expectedOutput,testOutput);
		}
		
		//Extracts the name of event by finding the last ;, or the index if event name is not found
		TEST_METHOD(extractDelEventName_Test)
		{
			//Case 1: Index
			testInput = "13";
			testOutput = splitter.extractDelEventName(testInput);
			expectedOutput = "13";
			Assert::AreEqual(expectedOutput,testOutput);
			
			//Case 2: Event name
			testInput = "event name12345;";
			testOutput = splitter.extractDelEventName(testInput);
			expectedOutput = "event name12345";
			Assert::AreEqual(expectedOutput,testOutput);

			//Case 3: Name with number at the front
			testInput = "21 jump street;";
			testOutput = splitter.extractDelEventName(testInput);
			expectedOutput = "21 jump street";
			Assert::AreEqual(expectedOutput,testOutput);
		}

		//Extracts the index of the event, or the event name if index is not found
		TEST_METHOD(extractEditEventName_Test)
		{
			//Case 1: Index
			testInput = "13 24-25apr 9pm";
			testOutput = splitter.extractEditEventName(testInput);
			expectedOutput = "13";
			Assert::AreEqual(expectedOutput,testOutput);
			
			//Case 2: Event name
			testInput = "event name12345; 24-25apr 9pm";
			testOutput = splitter.extractEditEventName(testInput);
			expectedOutput = "event name12345";
			Assert::AreEqual(expectedOutput,testOutput);

			//Case 3: Name with number at the front
			testInput = "21 jump street; 24-25apr 9pm";
			testOutput = splitter.extractEditEventName(testInput);
			expectedOutput = "21";
			Assert::AreEqual(expectedOutput,testOutput);
		}

		//Removes the index of the event, or the event name from the string
		TEST_METHOD(removeEditEventName_Test)
		{
			std::string eventName;

			//Case 1: Index
			testInput = "13 24-25apr 9pm";
			eventName = splitter.extractEditEventName(testInput);
			testOutput = splitter.removeEditEventName(testInput,eventName);
			expectedOutput = "24-25apr 9pm";
			Assert::AreEqual(expectedOutput,testOutput);
			
			//Case 2: Event name
			testInput = "event name12345; 24-25apr 9pm";
			eventName = splitter.extractEditEventName(testInput);
			testOutput = splitter.removeEditEventName(testInput,eventName);
			expectedOutput = "24-25apr 9pm";
			Assert::AreEqual(expectedOutput,testOutput);

			//Case 3: Name with number at the front
			testInput = "21 jump street; 24-25apr 9pm";
			eventName = splitter.extractEditEventName(testInput);
			testOutput = splitter.removeEditEventName(testInput,eventName);
			expectedOutput = "jump street; 24-25apr 9pm";
			Assert::AreEqual(expectedOutput,testOutput);
		}

		//Fragment the input string by taking out delimiters such as " .-"
		TEST_METHOD(fragmentAddString_Test)
		{
			std::vector<std::string> fragmentedWords;
			std::string expectedOutput0;
			std::string expectedOutput1;
			std::string expectedOutput2;
			std::string expectedOutput3;
			std::string expectedOutput4;
			std::string expectedOutput5;
			std::string expectedOutput6;

			//Case 1: Add floating event
			testInput = "event name12345;";
			fragmentedWords = splitter.fragmentAddString(testInput);
			expectedOutput0 = "event name12345;";
			Assert::AreEqual(expectedOutput0,fragmentedWords[0]);
			
			//Case 2: Add normal event
			testInput = "event name12345; 24-25apr 9am-10pm";
			fragmentedWords = splitter.fragmentAddString(testInput);
			expectedOutput0 = "event name12345;";
			expectedOutput1 = "24";
			expectedOutput2 = "to";
			expectedOutput3 = "25apr";
			expectedOutput4 = "9am";
			expectedOutput5 = "to";
			expectedOutput6 = "10pm";
			Assert::AreEqual(expectedOutput0,fragmentedWords[0]);
			Assert::AreEqual(expectedOutput1,fragmentedWords[1]);
			Assert::AreEqual(expectedOutput2,fragmentedWords[2]);
			Assert::AreEqual(expectedOutput3,fragmentedWords[3]);
			Assert::AreEqual(expectedOutput4,fragmentedWords[4]);
			Assert::AreEqual(expectedOutput5,fragmentedWords[5]);
			Assert::AreEqual(expectedOutput6,fragmentedWords[6]);

			//Case 2: Add with random input
			testInput = "gvtr d'kfnd;;; ndfv-nlksn' lkfdnv. dkl";
			fragmentedWords = splitter.fragmentAddString(testInput);
			expectedOutput0 = "gvtr d'kfnd;;;";
			expectedOutput1 = "ndfv";
			expectedOutput2 = "to";
			expectedOutput3 = "nlksn'";
			expectedOutput4 = "lkfdnv";
			expectedOutput5 = "dkl";
			Assert::AreEqual(expectedOutput0,fragmentedWords[0]);
			Assert::AreEqual(expectedOutput1,fragmentedWords[1]);
			Assert::AreEqual(expectedOutput2,fragmentedWords[2]);
			Assert::AreEqual(expectedOutput3,fragmentedWords[3]);
			Assert::AreEqual(expectedOutput4,fragmentedWords[4]);
			Assert::AreEqual(expectedOutput5,fragmentedWords[5]);
		}

		//Fragment the input string by taking out delimiters such as " .-"
		TEST_METHOD(fragmentEditString_Test)
		{
			std::vector<std::string> fragmentedWords;
			std::string expectedOutput0;
			std::string expectedOutput1;
			std::string expectedOutput2;
			std::string expectedOutput3;
			std::string expectedOutput4;
			std::string expectedOutput5;
			std::string expectedOutput6;

			//Case 1: Edit floating event
			testInput = "event name12345;";
			fragmentedWords = splitter.fragmentEditString(testInput);
			expectedOutput0 = "event name12345;";
			Assert::AreEqual(expectedOutput0,fragmentedWords[0]);
			
			//Case 2: Edit normal event
			testInput = "event name12345; 24-25apr 9am-10pm";
			fragmentedWords = splitter.fragmentEditString(testInput);
			expectedOutput0 = "event name12345;";
			expectedOutput1 = "24";
			expectedOutput2 = "to";
			expectedOutput3 = "25apr";
			expectedOutput4 = "9am";
			expectedOutput5 = "to";
			expectedOutput6 = "10pm";
			Assert::AreEqual(expectedOutput0,fragmentedWords[0]);
			Assert::AreEqual(expectedOutput1,fragmentedWords[1]);
			Assert::AreEqual(expectedOutput2,fragmentedWords[2]);
			Assert::AreEqual(expectedOutput3,fragmentedWords[3]);
			Assert::AreEqual(expectedOutput4,fragmentedWords[4]);
			Assert::AreEqual(expectedOutput5,fragmentedWords[5]);
			Assert::AreEqual(expectedOutput6,fragmentedWords[6]);

			//Case 2: Edit with random input
			testInput = "gvtr d'kfnd;;; ndfv-nlksn' lkfdnv. dkl";
			fragmentedWords = splitter.fragmentEditString(testInput);
			expectedOutput0 = "gvtr d'kfnd;";
			expectedOutput1 = "ndfv";
			expectedOutput2 = "to";
			expectedOutput3 = "nlksn'";
			expectedOutput4 = "lkfdnv";
			expectedOutput5 = "dkl";
			Assert::AreEqual(expectedOutput0,fragmentedWords[0]);
			Assert::AreEqual(expectedOutput1,fragmentedWords[1]);
			Assert::AreEqual(expectedOutput2,fragmentedWords[2]);
			Assert::AreEqual(expectedOutput3,fragmentedWords[3]);
			Assert::AreEqual(expectedOutput4,fragmentedWords[4]);
			Assert::AreEqual(expectedOutput5,fragmentedWords[5]);
		}

		//Fragment the input string by taking out delimiters such as " .-"
		TEST_METHOD(fragmentShowString_Test)
		{
			std::vector<std::string> fragmentedWords;
			std::string expectedOutput0;
			std::string expectedOutput1;
			std::string expectedOutput2;
			std::string expectedOutput3;
			std::string expectedOutput4;
			std::string expectedOutput5;
			std::string expectedOutput6;

			//Case 1: Show system input
			testInput = "week 14apr";
			fragmentedWords = splitter.fragmentShowString(testInput);
			expectedOutput0 = "week";
			expectedOutput1 = "14apr";
			Assert::AreEqual(expectedOutput0,fragmentedWords[0]);
			Assert::AreEqual(expectedOutput1,fragmentedWords[1]);
			
			//Case 2: Show user dates
			testInput = "21-25apr";
			fragmentedWords = splitter.fragmentShowString(testInput);
			expectedOutput0 = "21";
			expectedOutput1 = "to";
			expectedOutput2 = "25apr";
			Assert::AreEqual(expectedOutput0,fragmentedWords[0]);
			Assert::AreEqual(expectedOutput1,fragmentedWords[1]);
			Assert::AreEqual(expectedOutput2,fragmentedWords[2]);

			//Case 2: Show random input
			testInput = "ndfv-nlksn' lkfdnv. dkl";
			fragmentedWords = splitter.fragmentShowString(testInput);
			expectedOutput0 = "ndfv";
			expectedOutput1 = "to";
			expectedOutput2 = "nlksn'";
			expectedOutput3 = "lkfdnv";
			expectedOutput4 = "dkl";
			Assert::AreEqual(expectedOutput0,fragmentedWords[0]);
			Assert::AreEqual(expectedOutput1,fragmentedWords[1]);
			Assert::AreEqual(expectedOutput2,fragmentedWords[2]);
			Assert::AreEqual(expectedOutput3,fragmentedWords[3]);
			Assert::AreEqual(expectedOutput4,fragmentedWords[4]);
		}



	};
}