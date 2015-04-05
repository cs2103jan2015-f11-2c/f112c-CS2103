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

			//Case 2.1 : Boundary test (year) - front year within boundary of 70
			front.tm_mon = 1; 
			front.tm_mday = 1;
			front.tm_year = 70;
			
			back.tm_mon = 1;  
			back.tm_mday = 10;
			back.tm_year = 115;
			testResult = show.countNumDays(front,back);

			expectedResult = 16445;

			Assert::AreEqual(expectedResult,testResult);

			//Case 2.2 : Boundary test (year) - front year below boundary of 70
			front.tm_mon = 1; 
			front.tm_mday = 1;
			front.tm_year = 69;
			
			back.tm_mon = 1;  
			back.tm_mday = 10;
			back.tm_year = 115;
			testResult = show.countNumDays(front,back);

			//Assert::ExpectException

			//Case 2.3 : Boundary test (year) - back year within boundary of 1110
			front.tm_mon = 1; 
			front.tm_mday = 1;
			front.tm_year = 115;
			
			back.tm_mon = 1;  
			back.tm_mday = 10;
			back.tm_year = 1100;
			testResult = show.countNumDays(front,back);

			expectedResult = 359773;
			Assert::AreEqual(expectedResult,testResult);

			//Case 2.4 : Boundary test (year) - back year above boundary of 1110
			front.tm_mon = 1; 
			front.tm_mday = 1;
			front.tm_year = 115;
			
			back.tm_mon = 1;  
			back.tm_mday = 10;
			back.tm_year = 1101;
			testResult = show.countNumDays(front,back);

			//Assert::ExpectException

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

			//Case 3.2 : Boundary test (month) - after adjustment year 70
			front.tm_mon = -539; 
			front.tm_mday = 0;
			front.tm_year = 115;
			
			back.tm_mon = 0;  
			back.tm_mday = 0;
			back.tm_year = 115;
			testResult = show.countNumDays(front,back);

			expectedResult = 16405;
			Assert::AreEqual(expectedResult,testResult);

			//Case 3.3 : Boundary test (month) - after adjustment year below 70
			front.tm_mon = -540; 
			front.tm_mday = 0;
			front.tm_year = 115;
			
			back.tm_mon = 0;  
			back.tm_mday = 0;
			back.tm_year = 115;
			testResult = show.countNumDays(front,back);

			//Assert::ExpectException
			

			//Case 3.4 : Boundary test (month) - after adjustment year at 1110 
			front.tm_mon = 0; 
			front.tm_mday = 0;
			front.tm_year = 115;
			
			back.tm_mon = 11831;  
			back.tm_mday = 2;
			back.tm_year = 115;
			testResult = show.countNumDays(front,back);

			expectedResult = 360100;
			Assert::AreEqual(expectedResult,testResult);

			//Case 3.5 : Boundary test (month) - after adjustment year above 1110 
			front.tm_mon = 0; 
			front.tm_mday = 0;
			front.tm_year = 115;
			
			back.tm_mon = 11832;  
			back.tm_mday = 2;
			back.tm_year = 115;
			testResult = show.countNumDays(front,back);

			//Assert::ExpectException
			
			//Case 3.4 : Boundary test (month) - above 11
			front.tm_mon = 0; 
			front.tm_mday = 0;
			front.tm_year = 115;
			
			back.tm_mon = 12;  
			back.tm_mday = 0;
			back.tm_year = 115;
			testResult = show.countNumDays(front,back);

			//Assert::ExpectException

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

			//Case 2.1: boundary test - maximum positive int
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

			//Case 2.1: boundary test - maximum difference
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


		TEST_METHOD(UIShow_convertFromTmToString_Test){
			//boundary tests of day,month & year of tm date is voided as it has already been tested in TEST_METHOD(UIShow_countNumDays_Test)
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

			//normal int number

			//maximum int number

			//minimum int number
		
		}

		TEST_METHOD(UIShow_stringToInt_Test){
			int expectedResult;
			int testResult;
			std::string input = "";

			//normal string length

			//minimum int number

			//maximum int number

			//empty string - assertion

			//string not all digit - assertion
		
		}

		TEST_METHOD(UIShow_displayNext_Test){

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

			//full valid date input

			//day -1
			//day 32

			//month -1
			//month 12

			//below min year
			//above max year
		}

		TEST_METHOD(UIShow_generteDisplayFromCalendar_Test){

			//normal valid

			//start date later than end date 
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

			//normal case add

			//normal case ad

			//boundary empty string

			//boundary very large string
		}



	};
}