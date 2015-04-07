/**
 * @author A0111230J
 */

#include "stdafx.h"
#include "CppUnitTest.h"
#include <ctime>

// Please include the .cpp of the file you are testing, else there will be error
#include "UIShow.cpp"
#include "UIHelp.cpp"
#include "UICommandSuggestion.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{	
	// As a convention, put [name of file to be tested] + [Test]

	//Unit test for UIShow class
	TEST_CLASS(UIShowTest)
	{
	public:

		UIShow show;
		
		// As a convention, put [name of class] + [_name of function] + [_Test]

		TEST_METHOD(UIShow_getShowDay_Test)
		{
			//Correct string	
			std::string testCommandShowDay1 = show.getShowDay();
			std::string samepleCommandShowDay1= "show today";
			Assert::AreEqual(samepleCommandShowDay1,testCommandShowDay1);

			//Expected failing test: Incorrect string
			std::string testCommandShowDay2 = show.getShowDay();
			std::string samepleCommandShowDay2= "show today 12345";
			Assert::AreNotEqual(samepleCommandShowDay2,testCommandShowDay2);
		}

		TEST_METHOD(UIShow_countNumDays_Test){
			time_t now;
			struct tm front;
			struct tm back;
			int testResult;
			int expectedResult;

			time(&now);
			front = *localtime(&now);
			back = *localtime(&now);

			//Case 1.1 : Safely within boundary - small days difference of 9 
			front.tm_mon = 1; 
			front.tm_mday = 1;
			front.tm_year = 115;
			
			back.tm_mon = 1;  
			back.tm_mday = 10;
			back.tm_year = 115;
			testResult = show.countNumDays(front,back);

			expectedResult = 9;
			Assert::AreEqual(expectedResult,testResult);

			//Case 1.2 : Same day
			front.tm_mon = 1; 
			front.tm_mday = 1;
			front.tm_year = 115;
			
			back.tm_mon = 1;  
			back.tm_mday = 1;
			back.tm_year = 115;
			testResult = show.countNumDays(front,back);

			expectedResult = 0;
			Assert::AreEqual(expectedResult,testResult);

			//Case 1.3 : Back day before front day
			front.tm_mon = 1; 
			front.tm_mday = 10;
			front.tm_year = 115;
			
			back.tm_mon = 1;  
			back.tm_mday = 8;
			back.tm_year = 115;
			testResult = show.countNumDays(front,back);

			expectedResult = 2;
			Assert::AreEqual(expectedResult,testResult);

			//Case 2.1 : Boundary test (year) - front year within boundary of 71
			front.tm_mon = 1; 
			front.tm_mday = 1;
			front.tm_year = 71;
			
			back.tm_mon = 1;  
			back.tm_mday = 10;
			back.tm_year = 115;
			testResult = show.countNumDays(front,back);

			expectedResult = 16445;

			Assert::AreEqual(expectedResult,testResult);

			//Case 2.2 : Boundary test (year) - front year below boundary of 71
			front.tm_mon = 1; 
			front.tm_mday = 1;
			front.tm_year = 70;
			
			back.tm_mon = 1;  
			back.tm_mday = 10;
			back.tm_year = 115;
			
			std::string expectedErrorString = "Error: Unable to display date before year 1971";
			try{
			testResult = show.countNumDays(front,back);
			}
			catch(const std::string& testErrorString){
				Assert::AreEqual(expectedErrorString,testErrorString);
			}

			//Case 2.3 : Boundary test (year) - back year within boundary of 1099
			front.tm_mon = 1; 
			front.tm_mday = 1;
			front.tm_year = 115;
			
			back.tm_mon = 1;  
			back.tm_mday = 10;
			back.tm_year = 1099;
			testResult = show.countNumDays(front,back);

			expectedResult = 359773;
			Assert::AreEqual(expectedResult,testResult);

			//Case 2.4 : Boundary test (year) - back year above boundary of 1099
			front.tm_mon = 1; 
			front.tm_mday = 1;
			front.tm_year = 115;
			
			back.tm_mon = 1;  
			back.tm_mday = 10;
			back.tm_year = 1100;
			testResult = show.countNumDays(front,back);

			expectedErrorString = "Error: Unable to display date after year 2999";
			try{
			testResult = show.countNumDays(front,back);
			}
			catch(const std::string& testErrorString){
				Assert::AreEqual(expectedErrorString,testErrorString);
			}

			//Case 3.1 : Safely within boundary - month value 0
			front.tm_mon = 0; 
			front.tm_mday = 0;
			front.tm_year = 115;
			
			back.tm_mon = 0;  
			back.tm_mday = 2;
			back.tm_year = 115;
			testResult = show.countNumDays(front,back);

			expectedResult = 2;
			Assert::AreEqual(expectedResult,testResult);

			//Case 3.2 : Boundary test (month) - after adjustment year 71
			front.tm_mon = -538; 
			front.tm_mday = 0;
			front.tm_year = 115;
			
			back.tm_mon = 0;  
			back.tm_mday = 0;
			back.tm_year = 115;
			testResult = show.countNumDays(front,back);

			expectedResult = 16405;
			Assert::AreEqual(expectedResult,testResult);

			//Case 3.3 : Boundary test (month) - after adjustment year below 71
			front.tm_mon = -549; 
			front.tm_mday = 0;
			front.tm_year = 115;
			
			back.tm_mon = 0;  
			back.tm_mday = 0;
			back.tm_year = 115;
			testResult = show.countNumDays(front,back);

			expectedErrorString = "Error: Unable to display date before year 1971";
			try{
			testResult = show.countNumDays(front,back);
			}
			catch(const std::string& testErrorString){
				Assert::AreEqual(expectedErrorString,testErrorString);
			}

			//Case 3.4 : Boundary test (month) - after adjustment year at 1099 
			front.tm_mon = 0; 
			front.tm_mday = 0;
			front.tm_year = 115;
			
			back.tm_mon = 11831;  
			back.tm_mday = 2;
			back.tm_year = 115;
			testResult = show.countNumDays(front,back);

			expectedResult = 360100;
			Assert::AreEqual(expectedResult,testResult);

			//Case 3.5 : Boundary test (month) - after adjustment year above 1099 
			front.tm_mon = 0; 
			front.tm_mday = 0;
			front.tm_year = 115;
			
			back.tm_mon = 11832;  
			back.tm_mday = 2;
			back.tm_year = 115;
			testResult = show.countNumDays(front,back);

			expectedErrorString = "Error: Unable to display date after year 2999";
			try{
			testResult = show.countNumDays(front,back);
			}
			catch(const std::string& testErrorString){
				Assert::AreEqual(expectedErrorString,testErrorString);
			}

		}

		TEST_METHOD(UIShow_isSingleDay_Test){
			tm front;
			tm back;
			vector<tm> testVector;
			bool testResult;
			bool expectedResult;
			
			//Case 1.1: Same day, expected true
			front.tm_mday = 10;
			front.tm_mon = 1;
			front.tm_year = 1;

			back.tm_mday = 10;
			back.tm_mon = 1;
			back.tm_year = 1;

			testVector.push_back(front);
			testVector.push_back(back);

			testResult = show.checkIsSingleDate(testVector);
			expectedResult = true;

			Assert::AreEqual(expectedResult,testResult);
			testVector.clear();

			//Case 1.2: Different day, expected false
			front.tm_mday = 10;
			front.tm_mon = 1;
			front.tm_year = 69;

			back.tm_mday = 10;
			back.tm_mon = 2;
			back.tm_year = 1;

			testVector.push_back(front);
			testVector.push_back(back);

			testResult = show.checkIsSingleDate(testVector);
			expectedResult = false;

			Assert::AreEqual(expectedResult,testResult);
			testVector.clear();

			//Case 2.1: boundary test - maximum negative int
			front.tm_mday = -18446744073709551615;
			front.tm_mon = -18446744073709551615;
			front.tm_year = -18446744073709551615;

			back.tm_mday = -18446744073709551615;
			back.tm_mon = -18446744073709551615;
			back.tm_year = -18446744073709551615;

			testVector.push_back(front);
			testVector.push_back(back);

			testResult = show.checkIsSingleDate(testVector);
			expectedResult = true;

			Assert::AreEqual(expectedResult,testResult);
			testVector.clear();

			//Case 2.2: boundary test - maximum positive int
			front.tm_mday = 18446744073709551615;
			front.tm_mon = 18446744073709551615;
			front.tm_year = 18446744073709551615;

			back.tm_mday = 18446744073709551615;
			back.tm_mon = 18446744073709551615;
			back.tm_year = 18446744073709551615;

			testVector.push_back(front);
			testVector.push_back(back);

			testResult = show.checkIsSingleDate(testVector);
			expectedResult = true;

			Assert::AreEqual(expectedResult,testResult);
			testVector.clear();

			//Case 2.3: boundary test - maximum difference
			front.tm_mday = 18446744073709551615;
			front.tm_mon = 18446744073709551615;
			front.tm_year = 18446744073709551615;

			back.tm_mday = 0;
			back.tm_mon = 0;
			back.tm_year = 0;

			testVector.push_back(front);
			testVector.push_back(back);

			testResult = show.checkIsSingleDate(testVector);
			expectedResult = false;

			Assert::AreEqual(expectedResult,testResult);
			testVector.clear();
		}

		TEST_METHOD(UIShow_checkValidityOftm_Test){
			//Only out-of-range test cases are tested to test on the exception handling 
			//Test cases within range are indirectly tested in TEST_METHOD(UIShow_countNumDays_Test)

			time_t now;
			struct tm date;
			int testResult;
			int expectedResult;

			time(&now);
			date = *localtime(&now);

			//Boundary test (year) - year below boundary of 71
			date.tm_mon = 1; 
			date.tm_mday = 1;
			date.tm_year = 70;
			
			std::string expectedErrorString = "Error: Unable to display date before year 1971";
			try{
				show.checkValidityOftm(date);
			}
			catch(const std::string& testErrorString){
				Assert::AreEqual(expectedErrorString,testErrorString);
			}

			//Boundary test (year) - year above boundary of 1099
			date.tm_mon = 1; 
			date.tm_mday = 1;
			date.tm_year = 1100;

			expectedErrorString = "Error: Unable to display date after year 2999";
			try{
				show.checkValidityOftm(date);
			}
			catch(const std::string& testErrorString){
				Assert::AreEqual(expectedErrorString,testErrorString);
			}

			//Boundary test (mday) - mday below 1
			date.tm_mon = 1; 
			date.tm_mday = 0;
			date.tm_year = 115;

			expectedErrorString = "Error: Invalid Date(s) Selected / Date(s) out of range";
			try{
				show.checkValidityOftm(date);
			}
			catch(const std::string& testErrorString){
				Assert::AreEqual(expectedErrorString,testErrorString);
			}

			//Boundary test (mday) - mday above 31
			date.tm_mon = 1; 
			date.tm_mday = 32;
			date.tm_year = 115;

			expectedErrorString = "Error: Invalid Date(s) Selected / Date(s) out of range";
			try{
				show.checkValidityOftm(date);
			}
			catch(const std::string& testErrorString){
				Assert::AreEqual(expectedErrorString,testErrorString);
			}

			//Boundary test (mon) - mday below 0
			date.tm_mon = 0; 
			date.tm_mday = 10;
			date.tm_year = 115;

			expectedErrorString = "Error: Invalid Date(s) Selected / Date(s) out of range";
			try{
				show.checkValidityOftm(date);
			}
			catch(const std::string& testErrorString){
				Assert::AreEqual(expectedErrorString,testErrorString);
			}
		
			//Boundary test (mon) - mday above 11
			date.tm_mon = 12; 
			date.tm_mday = 10;
			date.tm_year = 115;

			expectedErrorString = "Error: Invalid Date(s) Selected / Date(s) out of range";
			try{
				show.checkValidityOftm(date);
			}
			catch(const std::string& testErrorString){
				Assert::AreEqual(expectedErrorString,testErrorString);
			}
		}

		TEST_METHOD(UIShow_convertFromTmToString_Test){
			//boundary tests of day,month & year of tm date is voided as they are being handled by function checkValidityOftm()
			// and has already been tested in TEST_METHOD(UIShow_checkValidityOftm_Test)
			
			time_t now;
			struct tm date;
			std::string testResult;
			std::string expectedResult;
			

			time(&now);
			date = *localtime(&now);

			//Correct case
			date.tm_mon = 1; 
			date.tm_mday = 1;
			date.tm_year = 115;
			testResult = show.convertFromTmToStr (date);
			expectedResult = "1feb 2015";
			Assert::AreEqual(expectedResult,testResult);

			//Expected failing test: wrong dayofmonth
			date.tm_mon = 2; 
			date.tm_mday = 1;
			date.tm_year = 115;
			testResult = show.convertFromTmToStr (date);
			expectedResult = "1feb 2015";
			Assert::AreNotEqual(expectedResult,testResult);

			//Expected failing test: wrong month
			date.tm_mon = 2; 
			date.tm_mday = 6;
			date.tm_year = 115;
			testResult = show.convertFromTmToStr (date);
			expectedResult = "1feb 2015";
			Assert::AreNotEqual(expectedResult,testResult);

			//Expected failing test: wrong year
			date.tm_mon = 2; 
			date.tm_mday = 1;
			date.tm_year = 118;
			testResult = show.convertFromTmToStr (date);
			expectedResult = "1feb 2015";
			Assert::AreNotEqual(expectedResult,testResult);
		}

		TEST_METHOD(UIShow_shiftDate_Test){
			//boundary tests of day,month & year of tm date is voided as they are being handled by function checkValidityOftm()
			// and has already been tested in TEST_METHOD(UIShow_checkValidityOftm_Test)

			time_t now;
			struct tm date;
			tm testResult;
			int expectedDay;
			int expectedMonth;
			int expectedYear;
			
			time(&now);
			date = *localtime(&now);

			date.tm_mday = 1;
			date.tm_mon = 1; 
			date.tm_year = 115;

			//correct case : shifts dayOfMonth only
			testResult = show.shiftDate(date,5);
			expectedDay = 6;
			expectedMonth = 1;
			expectedYear = 115;
			Assert::AreEqual(expectedDay, testResult.tm_mday);
			Assert::AreEqual(expectedMonth, testResult.tm_mon);
			Assert::AreEqual(expectedYear, testResult.tm_year);


			//correct case : shifts dayOfMonth and Month
			testResult = show.shiftDate(date,40);
			expectedDay = 13;
			expectedMonth = 2;
			expectedYear = 115;
			Assert::AreEqual(expectedDay, testResult.tm_mday);
			Assert::AreEqual(expectedMonth, testResult.tm_mon);
			Assert::AreEqual(expectedYear, testResult.tm_year);

			//correct case : shifts dayOfMonth and Month and Year
			testResult = show.shiftDate(date,400);
			expectedDay = 7;
			expectedMonth = 2;
			expectedYear = 116;
			Assert::AreEqual(expectedDay, testResult.tm_mday);
			Assert::AreEqual(expectedMonth, testResult.tm_mon);
			Assert::AreEqual(expectedYear, testResult.tm_year);

			//Expected failing test : wrong dayOfMonth
			testResult = show.shiftDate(date,5);
			expectedDay = 2;
			expectedMonth = 1;
			expectedYear = 115;
			Assert::AreNotEqual(expectedDay, testResult.tm_mday);
			Assert::AreEqual(expectedMonth, testResult.tm_mon);
			Assert::AreEqual(expectedYear, testResult.tm_year);

			//Expected failing test : wrong Month
			testResult = show.shiftDate(date,40);
			expectedDay = 13;
			expectedMonth = 1;
			expectedYear = 115;
			Assert::AreEqual(expectedDay, testResult.tm_mday);
			Assert::AreNotEqual(expectedMonth, testResult.tm_mon);
			Assert::AreEqual(expectedYear, testResult.tm_year);

			//Expected failing test : wrong Year
			testResult = show.shiftDate(date,400);
			expectedDay = 7;
			expectedMonth = 2;
			expectedYear = 115;
			Assert::AreEqual(expectedDay, testResult.tm_mday);
			Assert::AreEqual(expectedMonth, testResult.tm_mon);
			Assert::AreNotEqual(expectedYear, testResult.tm_year);
		}

		TEST_METHOD(UIShow_intToString_Test){
			int testInput;
			std::string testResult;
			std::string expectedResult;

			//normal int number
			testInput = 8765432;
			testResult = show.intToString(testInput);
			expectedResult = "8765432";
			Assert::AreEqual(expectedResult,testResult);

			//maximum int number
			testInput = 18446744073709551615;
			testResult = show.intToString(testInput);
			expectedResult = "18446744073709551615";
			Assert::AreEqual(expectedResult,testResult);

			//minimum int number
			testInput = 0;
			testResult = show.intToString(testInput);
			expectedResult = "0";
			Assert::AreEqual(expectedResult,testResult);
		}

		TEST_METHOD(UIShow_stringToInt_Test){
			string testInput;
			int testResult;
			int expectedResult;

			//normal positive number string
			testInput = "8765432";
			testResult = show.stringToInt(testInput);
			expectedResult = 8765432;
			Assert::AreEqual(expectedResult,testResult);

			//normal negative number string
			testInput = "-8765432";
			testResult = show.stringToInt(testInput);
			expectedResult = -8765432;
			Assert::AreEqual(expectedResult,testResult);

			//mixture of number and string (number first then string)
			testInput = "8765hello432";
			testResult = show.stringToInt(testInput);
			expectedResult = 8765;
			Assert::AreEqual(expectedResult,testResult);

			//mixture of number and string (string first then number)
			testInput = "hello432";
			testResult = show.stringToInt(testInput);
			expectedResult = 0;
			Assert::AreEqual(expectedResult,testResult);

			//minimum int number
			testInput = "-18446744073709551615";
			testResult = show.stringToInt(testInput);
			expectedResult = -18446744073709551615;
			Assert::AreEqual(expectedResult,testResult);

			//maximum int number
			testInput = "18446744073709551615";
			testResult = show.stringToInt(testInput);
			expectedResult = 18446744073709551615;
			Assert::AreEqual(expectedResult,testResult);
		
		}

		TEST_METHOD(UIShow_displayNext_Test){
			//boundary tests of day,month & year of tm date is voided as they are being handled by function checkValidityOftm()
			// and has already been tested in TEST_METHOD(UIShow_checkValidityOftm_Test)

			tm front;
			tm back;
			vector<tm> testVector;
			bool testResult;
			bool expectedResult;
			
			front.tm_mday = 10;
			front.tm_mon = 1;
			front.tm_year = 1;

			back.tm_mday = 10;
			back.tm_mon = 1;
			back.tm_year = 1;

			testVector.push_back(front);
			testVector.push_back(back);

			//[week] - complete

			//[week] - incomplete

			//[month] - complete
			//[month] - incomplete

			//vector<tm> normal case - 5 days difference
			//vector<tm> normal case - maximum days difference
			//vector<tm> normal case - no day difference
			//vector<tm> front later than back
		}

		TEST_METHOD(UIShow_displayBack_Test){
			//[week] - complete
			//[week] - incomplete

			//[month] - complete
			//[month] - incomplete

			//vector<tm> normal case - 5 days difference
			//vector<tm> normal case - maximum days difference
			//vector<tm> normal case - no day difference
			//vector<tm> front later than back
		}

		TEST_METHOD(UIShow_generateDateString_Test){
			std::string input;
			std::string expectedResult;
			std::string testResult;
			std::string expectedErrorString;

			//full valid date input
			input = "21/8/2015";
			testResult = show.generateDateString(input);
			expectedResult = "21aug 2015";

			Assert::AreEqual(expectedResult,testResult);

			//no mday
			input = "/8/2015";
			expectedErrorString = "Error: Invalid Date(s) Selected / Date(s) out of range";
			try{
				testResult = show.generateDateString(input);
			}
			catch(const std::string& testErrorString){
				Assert::AreEqual(expectedErrorString,testErrorString);
			}

			//boundary test - mday < 1
			input = "0/8/2015";
			expectedErrorString = "Error: Invalid Date(s) Selected / Date(s) out of range";
			try{
				testResult = show.generateDateString(input);
			}
			catch(const std::string& testErrorString){
				Assert::AreEqual(expectedErrorString,testErrorString);
			}

			//boundary test - mday < 31
			input = "32/8/2015";
			testResult = show.generateDateString(input);
			expectedErrorString = "Error: Invalid Date(s) Selected / Date(s) out of range";
			try{
				testResult = show.generateDateString(input);
			}
			catch(const std::string& testErrorString){
				Assert::AreEqual(expectedErrorString,testErrorString);
			}

			//no mon
			input = "8//2015";
			expectedErrorString = "Error: Invalid Date(s) Selected / Date(s) out of range";
			try{
				testResult = show.generateDateString(input);
			}
			catch(const std::string& testErrorString){
				Assert::AreEqual(expectedErrorString,testErrorString);
			}

			//boundary test - mon < 1
			input = "8/0/2015";
			expectedErrorString = "Error: Invalid Date(s) Selected / Date(s) out of range";
			try{
				testResult = show.generateDateString(input);
			}
			catch(const std::string& testErrorString){
				Assert::AreEqual(expectedErrorString,testErrorString);
			}

			//boundary test - mon > 12
			input = "8/13/2015";
			testResult = show.generateDateString(input);
			expectedErrorString = "Error: Invalid Date(s) Selected / Date(s) out of range";
			try{
				testResult = show.generateDateString(input);
			}
			catch(const std::string& testErrorString){
				Assert::AreEqual(expectedErrorString,testErrorString);
			}

			//no year
			input = "8/8/";
			expectedErrorString = "Error: Invalid Date(s) Selected / Date(s) out of range";
			try{
				testResult = show.generateDateString(input);
			}
			catch(const std::string& testErrorString){
				Assert::AreEqual(expectedErrorString,testErrorString);
			}

			//boundary test - year < 1971
			input = "8/0/1970";
			expectedErrorString = "Error: Unable to display date before year 1971";
			try{
				testResult = show.generateDateString(input);
			}
			catch(const std::string& testErrorString){
				Assert::AreEqual(expectedErrorString,testErrorString);
			}

			//boundary test - year > 2999
			input = "8/13/3000";
			testResult = show.generateDateString(input);
			expectedErrorString = "Error: Unable to display date after year 2999";
			try{
				testResult = show.generateDateString(input);
			}
			catch(const std::string& testErrorString){
				Assert::AreEqual(expectedErrorString,testErrorString);
			}
		}

		TEST_METHOD(UIShow_generteCurrentCommand_Test){

			//[week] - complete
			//[week] - incomplete

			//[month] - complete
			//[month] - incomplete

			//vector<tm> normal case - 5 days difference
			//vector<tm> normal case - maximum days difference
			//vector<tm> normal case - no day difference
			//vector<tm> front later than back
		}


	};


	//Unit test for UIcommandSuggest class
	TEST_CLASS(UIcommandSuggestTest)
	{
	public:
		UICommandSuggestion comdSuggest;

		TEST_METHOD(UICommandSuggestion_getComdType_Test){
			UICommandSuggestion::ComdType expectedResult;
			UICommandSuggestion::ComdType testResult;
			std::string input;

			//normal case add
			input = "add";
			testResult = comdSuggest.getComdType(input);
			expectedResult = UICommandSuggestion::ADD_;

			Assert::AreEqual(expectedResult,testResult);

			//normal case ad
			input = "ad";
			testResult = comdSuggest.getComdType(input);
			expectedResult = UICommandSuggestion::UNDISPLAY_;

			Assert::AreEqual(expectedResult,testResult);

			//boundary empty string
			input = "";
			testResult = comdSuggest.getComdType(input);
			expectedResult = UICommandSuggestion::INVALID_;

			Assert::AreEqual(expectedResult,testResult);

			//boundary very large string
			input = "qwertyuiopqwertyuiopqwertyuiopqwertyuiopqwertyuiopqwertyuiopqwertyuiopqwertyuiopqwertyuiopqwertyuiopqwertyuiopqwertyuiop[qwertyuiopqwertyuio";
			testResult = comdSuggest.getComdType(input);
			expectedResult = UICommandSuggestion::INVALID_;

			Assert::AreEqual(expectedResult,testResult);
		}

	};
}