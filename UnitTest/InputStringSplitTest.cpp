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

		//Finds the first non spacing after the first spacing and takes the whole string after that
		TEST_METHOD(extractDetails_Test)
		{
			//Case 1: Empty string
			testInput = "";
			expectedOutput = ParserExceptions::ERROR_MISSING_INPUT;
			try {
				testOutput = splitter.extractDetails(testInput);
			} catch (ParserExceptions& e){
				testOutput = e.getExceptionCode();
			}
			Assert::AreEqual(expectedOutput,testOutput);

			//Case 2: One word
			testInput = "add";
			expectedOutput = ParserExceptions::ERROR_MISSING_INPUT;
			try {
				testOutput = splitter.extractDetails(testInput);
			} catch (ParserExceptions& e){
				testOutput = e.getExceptionCode();
			}
			Assert::AreEqual(expectedOutput,testOutput);

			//Case 3: One word plus spaces and symbols
			testInput = "del     ;;;";
			expectedOutput = ParserExceptions::ERROR_MISSING_INPUT;
			try {
				testOutput = splitter.extractDetails(testInput);
			} catch (ParserExceptions& e){
				testOutput = e.getExceptionCode();
			}
			Assert::AreEqual(expectedOutput,testOutput);

			//Case 4: Multiple Words
			testInput = "add event; 17-18mar";
			testOutput = splitter.extractDetails(testInput);
			expectedOutput = "event; 17-18mar";
			Assert::AreEqual(expectedOutput,testOutput);
			
			//Case 5: Multiple Words random input
			testInput = "ave;l233 o4,;s lkkk";
			testOutput = splitter.extractDetails(testInput);
			expectedOutput = "o4,;s lkkk";
			Assert::AreEqual(expectedOutput,testOutput);

			//Case 6: Input with starting spaces
			testInput = "     add";
			testOutput = splitter.extractDetails(testInput);
			expectedOutput = "add";
			Assert::AreEqual(expectedOutput,testOutput);
		}
		
		//Extracts the name of event by finding the last ;, or the index if event name is not found
		TEST_METHOD(extractDelDoneEventName_Test)
		{
			//Case 1: Empty string
			testInput = "";
			expectedOutput = ParserExceptions::ERROR_MISSING_INPUT;
			try {
				testOutput = splitter.extractDelDoneEventName(testInput);
			} catch (ParserExceptions& e){
				testOutput = e.getExceptionCode();
			}
			Assert::AreEqual(expectedOutput,testOutput);

			//Case 2: Index only
			testInput = "13";
			testOutput = splitter.extractDelDoneEventName(testInput);
			expectedOutput = "13";
			Assert::AreEqual(expectedOutput,testOutput);
			
			//Case 3: Event name only
			testInput = "event name12345;";
			testOutput = splitter.extractDelDoneEventName(testInput);
			expectedOutput = "event name12345";
			Assert::AreEqual(expectedOutput,testOutput);

			//Case 4: Event name and additional details
			testInput = "21 jump street; 24-25apr 8pm";
			testOutput = splitter.extractDelDoneEventName(testInput);
			expectedOutput = "21 jump street";
			Assert::AreEqual(expectedOutput,testOutput);

			//Case 5: Many inputs but no name
			testInput = "21 jump street";
			expectedOutput = ParserExceptions::ERROR_TOO_MANY_DEL;
			try {
				testOutput = splitter.extractDelDoneEventName(testInput);
			} catch (ParserExceptions& e){
				testOutput = e.getExceptionCode();
			}
			Assert::AreEqual(expectedOutput,testOutput);

			//Case 6: One input, no name, no index
			testInput = "jumpstreet";
			expectedOutput = ParserExceptions::ERROR_MISSING_INDEX;
			try {
				testOutput = splitter.extractDelDoneEventName(testInput);
			} catch (ParserExceptions& e){
				testOutput = e.getExceptionCode();
			}
			Assert::AreEqual(expectedOutput,testOutput);
		}

		//Extracts the index of the event, or the event name if index is not found
		TEST_METHOD(extractEditEventName_Test)
		{
			//Case 1: Empty string
			testInput = "";
			expectedOutput = ParserExceptions::ERROR_MISSING_INPUT;
			try {
				testOutput = splitter.extractEditEventName(testInput);
			} catch (ParserExceptions& e){
				testOutput = e.getExceptionCode();
			}
			Assert::AreEqual(expectedOutput,testOutput);

			//Case 2: Editting by index
			testInput = "13 24-25apr 9pm";
			testOutput = splitter.extractEditEventName(testInput);
			expectedOutput = "13";
			Assert::AreEqual(expectedOutput,testOutput);
			
			//Case 3: Editting by event name
			testInput = "event name12345; 24-25apr 9pm";
			testOutput = splitter.extractEditEventName(testInput);
			expectedOutput = "event name12345";
			Assert::AreEqual(expectedOutput,testOutput);

			//Case 4: Editting by event name with number in front
			testInput = "21 jump street; 24-25apr 9pm";
			testOutput = splitter.extractEditEventName(testInput);
			expectedOutput = "21";
			Assert::AreEqual(expectedOutput,testOutput);

			//Case 5: Many inputs but no name
			testInput = "jump street";
			expectedOutput = ParserExceptions::ERROR_MISSING_INDEX;
			try {
				testOutput = splitter.extractEditEventName(testInput);
			} catch (ParserExceptions& e){
				testOutput = e.getExceptionCode();
			}
			Assert::AreEqual(expectedOutput,testOutput);

			//Case 6: One input, no name, no index
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
		TEST_METHOD(removeEditEventName_Test)
		{
			std::string eventName;

			//Case 1: Empty string
			testInput = "";
			eventName = "";
			expectedOutput = ParserExceptions::ERROR_MISSING_INPUT;
			try {
				testOutput = splitter.removeEditEventName(testInput,eventName);
			} catch (ParserExceptions& e){
				testOutput = e.getExceptionCode();
			}
			Assert::AreEqual(expectedOutput,testOutput);

			//Case 1: Remove name with no additional input after that
			testInput = "jumpstreet;";
			eventName = splitter.extractEditEventName(testInput);
			expectedOutput = ParserExceptions::ERROR_INSUFFICIENT_INFO;
			try {
				testOutput = splitter.removeEditEventName(testInput,eventName);
			} catch (ParserExceptions& e){
				testOutput = e.getExceptionCode();
			}
			Assert::AreEqual(expectedOutput,testOutput);

			//Case 2: Remove index with no additional input after that
			testInput = "21";
			eventName = splitter.extractEditEventName(testInput);
			expectedOutput = ParserExceptions::ERROR_INSUFFICIENT_INFO;
			try {
				testOutput = splitter.removeEditEventName(testInput,eventName);
			} catch (ParserExceptions& e){
				testOutput = e.getExceptionCode();
			}
			Assert::AreEqual(expectedOutput,testOutput);

			//Case 3: Remove by index
			testInput = "13 24-25apr 9pm";
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

			//Case 1: Empty string
			testInput = "";
			expectedOutput = ParserExceptions::ERROR_MISSING_INPUT;
			try {
				fragmentedWords = splitter.fragmentAddString(testInput);
				testOutput = fragmentedWords[0];
			} catch (ParserExceptions& e){
				testOutput = e.getExceptionCode();
			}
			Assert::AreEqual(expectedOutput,testOutput);

			//Case 2: No event name in add input
			testInput = "event name12345 24-25apr 9am-10pm";
			expectedOutput = ParserExceptions::ERROR_NO_NAME;
			try {
				fragmentedWords = splitter.fragmentAddString(testInput);
				testOutput = fragmentedWords[0];
			} catch (ParserExceptions& e){
				testOutput = e.getExceptionCode();
			}
			Assert::AreEqual(expectedOutput,testOutput);

			//Case 3: Event name only (floating events)
			testInput = "event name12345;";
			fragmentedWords = splitter.fragmentAddString(testInput);
			expectedOutput0 = "event name12345;";
			Assert::AreEqual(expectedOutput0,fragmentedWords[0]);
			
			//Case 4: Add normal event
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

			//Case 5: Add with random input
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

			//Case 1: Empty string
			testInput = "";
			expectedOutput = ParserExceptions::ERROR_MISSING_INPUT;
			try {
				fragmentedWords = splitter.fragmentEditString(testInput);
				testOutput = fragmentedWords[0];
			} catch (ParserExceptions& e){
				testOutput = e.getExceptionCode();
			}
			Assert::AreEqual(expectedOutput,testOutput);

			//Case 2: Input with all " .-"
			testInput = " .-.-. -.- .- ... .";
			expectedOutput = ParserExceptions::ERROR_INSUFFICIENT_INFO;
			try {
				fragmentedWords = splitter.fragmentEditString(testInput);
				testOutput = fragmentedWords[0];
			} catch (ParserExceptions& e){
				testOutput = e.getExceptionCode();
			}
			Assert::AreEqual(expectedOutput,testOutput);

			//Case 3: Edit floating event
			testInput = "event name12345;";
			fragmentedWords = splitter.fragmentEditString(testInput);
			expectedOutput0 = "event name12345;";
			Assert::AreEqual(expectedOutput0,fragmentedWords[0]);
			
			//Case 4: Edit normal event
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

			//Case 5: Edit with random input
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

			//Case 1: Empty string
			testInput = "";
			expectedOutput = ParserExceptions::ERROR_MISSING_INPUT;
			try {
				fragmentedWords = splitter.fragmentShowString(testInput);
				testOutput = fragmentedWords[0];
			} catch (ParserExceptions& e){
				testOutput = e.getExceptionCode();
			}
			Assert::AreEqual(expectedOutput,testOutput);

			//Case 2: Input with all " .-"
			testInput = " .-.-. -.- .- ... .";
			expectedOutput = ParserExceptions::ERROR_INSUFFICIENT_INFO;
			try {
				fragmentedWords = splitter.fragmentShowString(testInput);
				testOutput = fragmentedWords[0];
			} catch (ParserExceptions& e){
				testOutput = e.getExceptionCode();
			}
			Assert::AreEqual(expectedOutput,testOutput);

			//Case 3: Show system input
			testInput = "week 14apr";
			fragmentedWords = splitter.fragmentShowString(testInput);
			expectedOutput0 = "week";
			expectedOutput1 = "14apr";
			Assert::AreEqual(expectedOutput0,fragmentedWords[0]);
			Assert::AreEqual(expectedOutput1,fragmentedWords[1]);
			
			//Case 4: Show user dates
			testInput = "21-25apr";
			fragmentedWords = splitter.fragmentShowString(testInput);
			expectedOutput0 = "21";
			expectedOutput1 = "to";
			expectedOutput2 = "25apr";
			Assert::AreEqual(expectedOutput0,fragmentedWords[0]);
			Assert::AreEqual(expectedOutput1,fragmentedWords[1]);
			Assert::AreEqual(expectedOutput2,fragmentedWords[2]);

			//Case 5: Show random input
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