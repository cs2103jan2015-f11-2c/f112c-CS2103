#include "stdafx.h"
#include "CppUnitTest.h"
#include <ctime>

// Please include the .cpp of the file you are testing, else there will be error
#include "UIShow.cpp"
#include "UIHelp.cpp"

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

			front.tm_mon = 1; 
			front.tm_mday = 1;
			front.tm_year = 115;
			
			back.tm_mon = 1;  
			back.tm_mday = 10;
			back.tm_year = 115;
			testResult = show.countNumDays(front,back);
			
			//Case 1 : Correct number of days - 9
			expectedResult = 9;
			Assert::AreEqual(expectedResult,testResult);

			// Expected failing test
			// Case 2: boundary testing - more than 9
			expectedResult = 10;
			Assert::AreNotEqual(expectedResult,testResult);

			// Expected failing test
			// Case 3: boundary testing - less than 9
			expectedResult = 8;
			Assert::AreNotEqual(expectedResult,testResult);

		}

		TEST_METHOD(UIShow_isSingleDay_Test){
			tm front;
			tm back;
			vector<tm> testVector;
			bool testResult;
			bool expectedResult;
			
			//Same day, expected true
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

			//Different day, expected false
			front.tm_mday = 10;
			front.tm_mon = 1;
			front.tm_year = 1;

			back.tm_mday = 10;
			back.tm_mon = 2;
			back.tm_year = 1;

			testVector.push_back(front);
			testVector.push_back(back);

			testResult = show.checkIsSingleDate(testVector);
			expectedResult = false;

			Assert::AreEqual(expectedResult,testResult);
			testVector.clear();

			//Expected failing test
			front.tm_mday = 10;
			front.tm_mon = 1;
			front.tm_year = 1;

			back.tm_mday = 10;
			back.tm_mon = 2;
			back.tm_year = 1;

			testVector.push_back(front);
			testVector.push_back(back);

			testResult = show.checkIsSingleDate(testVector);
			expectedResult = true;

			Assert::AreNotEqual(expectedResult,testResult);
			testVector.clear();
		}


		TEST_METHOD(UIShow_convertFromTmToString_Test){
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

		TEST_METHOD(UIShow_displayNext_Test){
		
		
		
		}

		TEST_METHOD(UIShow_displayBack_Test){



		}


	};

	//Unit test for UIHelp class
	TEST_CLASS(UIHelpTest)
	{
	public:




	};

	//Unit test for commandSuggest class
	TEST_CLASS(commandSuggestTest)
	{
	public:




	};
}