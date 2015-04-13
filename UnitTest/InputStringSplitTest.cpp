//@author A0111379H

#include "stdafx.h"
#include "CppUnitTest.h"
#include "InputStringSplit.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	TEST_CLASS(InputStringSplitTest)
	{
	public:
		
		InputStringSplit splitter;
		std::string testInput;
		std::string testOutput;
		std::string expectedOutput;
		
		//extractFirstWord always find the first instance of a spacing and take what comes before the space
		TEST_METHOD(InputStringSplitTest_extractFirstWord_Test)
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
			testInput = "     add hello";
			testOutput = splitter.extractFirstWord(testInput);
			expectedOutput = "add";
			Assert::AreEqual(expectedOutput,testOutput);
		}

		//Finds the first non spacing after the first spacing and takes the whole string after that
		TEST_METHOD(InputStringSplitTest_extractDetails_Test)
		{
			//Case 1: One word
			testInput = "add";
			expectedOutput = ParserExceptions::ERROR_MISSING_INPUT;
			try {
				testOutput = splitter.extractDetails(testInput);
			} catch (ParserExceptions& e){
				testOutput = e.getExceptionCode();
			}
			Assert::AreEqual(expectedOutput,testOutput);

			//Case 2: One word plus spaces and symbols
			testInput = "del     ;;;";
			testOutput = splitter.extractDetails(testInput);
			expectedOutput = ";;;";
			Assert::AreEqual(expectedOutput,testOutput);

			//Case 3: Multiple Words
			testInput = "add event; 17-18mar";
			testOutput = splitter.extractDetails(testInput);
			expectedOutput = "event; 17-18mar";
			Assert::AreEqual(expectedOutput,testOutput);
			
			//Case 4: Multiple Words random input
			testInput = "ave;l233 o4,;s lkkk";
			testOutput = splitter.extractDetails(testInput);
			expectedOutput = "o4,;s lkkk";
			Assert::AreEqual(expectedOutput,testOutput);

			//Case 5: Input with starting spaces
			testInput = "     add";
			expectedOutput = ParserExceptions::ERROR_MISSING_INPUT;
			try { 
				testOutput = splitter.extractDetails(testInput);
			} catch (ParserExceptions& e){
				testOutput = e.getExceptionCode();
			}
			Assert::AreEqual(expectedOutput,testOutput);
		}
		
		//Extracts the index of the event, or the event name if index is not found
		TEST_METHOD(InputStringSplitTest_extractEditEventName_Test)
		{
			//Case 1: Editting by index
			testInput = "13; 24-25apr 9pm";
			testOutput = splitter.extractEditEventName(testInput);
			expectedOutput = "13";
			Assert::AreEqual(expectedOutput,testOutput);
			
			//Case 2: Editting by event name
			testInput = "event name12345; 24-25apr 9pm";
			testOutput = splitter.extractEditEventName(testInput);
			expectedOutput = "event name12345";
			Assert::AreEqual(expectedOutput,testOutput);

			//Case 3: Editting by event name with number in front
			testInput = "21 jump street; 24-25apr 9pm";
			testOutput = splitter.extractEditEventName(testInput);
			expectedOutput = "21 jump street";
			Assert::AreEqual(expectedOutput,testOutput);

			//Case 4: Many inputs but no ; to indicate name
			testInput = "jump street";
			expectedOutput = ParserExceptions::ERROR_MISSING_INDEX;
			try {
				testOutput = splitter.extractEditEventName(testInput);
			} catch (ParserExceptions& e){
				testOutput = e.getExceptionCode();
			}
			Assert::AreEqual(expectedOutput,testOutput);

			//Case 5: One input, no name, no index
			testInput = "jumpstreet";
			expectedOutput = ParserExceptions::ERROR_MISSING_INDEX;
			try {
				testOutput = splitter.extractEditEventName(testInput);
			} catch (ParserExceptions& e){
				testOutput = e.getExceptionCode();
			}
			Assert::AreEqual(expectedOutput,testOutput);
		}

		//Removes the index of the event, or the event name from the string
		TEST_METHOD(InputStringSplitTest_removeEditEventName_Test)
		{
			std::string eventName;

			//Case 1: Remove name with no additional input after that
			testInput = "jumpstreet;";
			eventName = splitter.extractEditEventName(testInput);
			expectedOutput = "";
			Assert::AreEqual(expectedOutput,testOutput);

			//Case 2: Remove index with no additional input after that
			testInput = "21;";
			eventName = splitter.extractEditEventName(testInput);
			testOutput = splitter.removeEditEventName(testInput,eventName);
			expectedOutput = "to>>>float";
			Assert::AreEqual(expectedOutput,testOutput);

			//Case 3: Remove by index
			testInput = "13; 24-25apr 9pm";
			eventName = splitter.extractEditEventName(testInput);
			testOutput = splitter.removeEditEventName(testInput,eventName);
			expectedOutput = "24-25apr 9pm";
			Assert::AreEqual(expectedOutput,testOutput);
			
			//Case 4: Remove by event name
			testInput = "event name12345; 24-25apr 9pm";
			eventName = splitter.extractEditEventName(testInput);
			testOutput = splitter.removeEditEventName(testInput,eventName);
			expectedOutput = "24-25apr 9pm";
			Assert::AreEqual(expectedOutput,testOutput);

			//Case 5: Remove name with number at the front
			testInput = "21 jump street; 24-25apr 9pm";
			eventName = splitter.extractEditEventName(testInput);
			testOutput = splitter.removeEditEventName(testInput,eventName);
			expectedOutput = "24-25apr 9pm";
			Assert::AreEqual(expectedOutput,testOutput);
		}

		//Fragment the input string by taking out delimiters such as " .-"
		TEST_METHOD(InputStringSplitTest_fragmentString_Test)
		{
			std::vector<std::string> fragmentedWords;
			std::string expectedOutput0;
			std::string expectedOutput1;
			std::string expectedOutput2;
			std::string expectedOutput3;
			std::string expectedOutput4;
			std::string expectedOutput5;
			std::string expectedOutput6;
			std::string expectedOutput7;
			std::string expectedOutput8;
			std::string expectedOutput9;
			std::string expectedOutput10;
			std::string expectedOutput11;
			std::string expectedOutput12;

			//Case 1: One word
			testInput = "event";
			expectedOutput0 = "event";
			fragmentedWords = splitter.fragmentString(testInput);
			testOutput = fragmentedWords[0];
			Assert::AreEqual(expectedOutput0,testOutput);

			//Case 2: Event name only (floating events)
			testInput = "event name12345;";
			fragmentedWords = splitter.fragmentString(testInput);
			expectedOutput0 = "event ";
			expectedOutput1 = "name";
			expectedOutput2 = "12345";
			expectedOutput3 = ";";
			Assert::AreEqual(expectedOutput0,fragmentedWords[0]);
			Assert::AreEqual(expectedOutput1,fragmentedWords[1]);
			Assert::AreEqual(expectedOutput2,fragmentedWords[2]);
			Assert::AreEqual(expectedOutput3,fragmentedWords[3]);
			
			//Case 3: Add normal event
			testInput = "event name12345; 24-25apr 9am-10pm";
			fragmentedWords = splitter.fragmentString(testInput);
			expectedOutput0 = "event ";
			expectedOutput1 = "name";
			expectedOutput2 = "12345";
			expectedOutput3 = "; ";
			expectedOutput4 = "24";
			expectedOutput5 = "to";
			expectedOutput6 = "25";
			expectedOutput7 = "apr ";
			expectedOutput8 = "9";
			expectedOutput9 = "am";
			expectedOutput10 = "to";
			expectedOutput11 = "10";
			expectedOutput12 = "pm";
			Assert::AreEqual(expectedOutput0,fragmentedWords[0]);
			Assert::AreEqual(expectedOutput1,fragmentedWords[1]);
			Assert::AreEqual(expectedOutput2,fragmentedWords[2]);
			Assert::AreEqual(expectedOutput3,fragmentedWords[3]);
			Assert::AreEqual(expectedOutput4,fragmentedWords[4]);
			Assert::AreEqual(expectedOutput5,fragmentedWords[5]);
			Assert::AreEqual(expectedOutput6,fragmentedWords[6]);
			Assert::AreEqual(expectedOutput7,fragmentedWords[7]);
			Assert::AreEqual(expectedOutput8,fragmentedWords[8]);
			Assert::AreEqual(expectedOutput9,fragmentedWords[9]);
			Assert::AreEqual(expectedOutput10,fragmentedWords[10]);
			Assert::AreEqual(expectedOutput11,fragmentedWords[11]);
			Assert::AreEqual(expectedOutput12,fragmentedWords[12]);

			//Case 4: Add with random input
			testInput = "gvtr d'kfnd;;; ndfv-nlksn' lkfdnv. dkl";
			fragmentedWords = splitter.fragmentString(testInput);
			expectedOutput0 = "gvtr ";
			expectedOutput1 = "d'kfnd;;; ";
			expectedOutput2 = "ndfv";
			expectedOutput3 = "to";
			expectedOutput4 = "nlksn' ";
			expectedOutput5 = "lkfdnv. ";
			expectedOutput6 = "dkl";
			Assert::AreEqual(expectedOutput0,fragmentedWords[0]);
			Assert::AreEqual(expectedOutput1,fragmentedWords[1]);
			Assert::AreEqual(expectedOutput2,fragmentedWords[2]);
			Assert::AreEqual(expectedOutput3,fragmentedWords[3]);
			Assert::AreEqual(expectedOutput4,fragmentedWords[4]);
			Assert::AreEqual(expectedOutput5,fragmentedWords[5]);
			Assert::AreEqual(expectedOutput6,fragmentedWords[6]);
		}
	};
}