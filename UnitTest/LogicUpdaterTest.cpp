#include "stdafx.h"
#include "CppUnitTest.h"


#include "LogicUpdater.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	TEST_CLASS(LogicUpdaterTest)
	{
	public:

		LogicUpdater lgUpdater;

		TEST_METHOD(LogicUpdater_isDisplayMonth_Test){
			time_t now;
			struct tm front;
			struct tm back;
			bool testResult;
			bool expectedResult;

			time(&now);
			front = *localtime(&now);
			back = *localtime(&now);

			// true
			front.tm_mon = 0; 
			front.tm_mday = 1;
			front.tm_year = 115;
			
			back.tm_mon = 0;  
			back.tm_mday = 31;
			back.tm_year = 115;

			lgUpdater.setWeekMonthOrNothing("");

			expectedResult = true;
			testResult = lgUpdater.isDisplayMonth(front,back);
			Assert::AreEqual(expectedResult,testResult);

			// false - backdate 1 day before end of month
			front.tm_mon = 0; 
			front.tm_mday = 1;
			front.tm_year = 115;
			
			back.tm_mon = 0;  
			back.tm_mday = 30;
			back.tm_year = 115;

			lgUpdater.setWeekMonthOrNothing("");

			expectedResult = false;
			testResult = lgUpdater.isDisplayMonth(front,back);
			Assert::AreEqual(expectedResult,testResult);

			// false - frontdate 1 day after start of month
			front.tm_mon = 0; 
			front.tm_mday = 2;
			front.tm_year = 115;
			
			back.tm_mon = 0;  
			back.tm_mday = 31;
			back.tm_year = 115;

			lgUpdater.setWeekMonthOrNothing("");

			expectedResult = false;
			testResult = lgUpdater.isDisplayMonth(front,back);
			Assert::AreEqual(expectedResult,testResult);


			// weekMonthorNothing - month
			front.tm_mon = 0; 
			front.tm_mday = 8;
			front.tm_year = 115;
			
			back.tm_mon = 0;  
			back.tm_mday = 31;
			back.tm_year = 115;

			lgUpdater.setWeekMonthOrNothing("Month");

			expectedResult = true;
			testResult = lgUpdater.isDisplayMonth(front,back);
			Assert::AreEqual(expectedResult,testResult);

			// same date
			front.tm_mon = 1; 
			front.tm_mday = 8;
			front.tm_year = 115;
			
			back.tm_mon = 1;  
			back.tm_mday = 8;
			back.tm_year = 115;

			lgUpdater.setWeekMonthOrNothing("");

			expectedResult = false;
			testResult = lgUpdater.isDisplayMonth(front,back);
			Assert::AreEqual(expectedResult,testResult);

			// all valid, different year 
			front.tm_mon = 0; 
			front.tm_mday = 1;
			front.tm_year = 115;
			
			back.tm_mon = 0;  
			back.tm_mday = 31;
			back.tm_year = 116;

			lgUpdater.setWeekMonthOrNothing("");

			expectedResult = false;
			testResult = lgUpdater.isDisplayMonth(front,back);
			Assert::AreEqual(expectedResult,testResult);

			// all valid, different month
			front.tm_mon = 0; 
			front.tm_mday = 1;
			front.tm_year = 115;
			
			back.tm_mon = 2;  
			back.tm_mday = 31;
			back.tm_year = 115;

			lgUpdater.setWeekMonthOrNothing("");

			expectedResult = false;
			testResult = lgUpdater.isDisplayMonth(front,back);
			Assert::AreEqual(expectedResult,testResult);

			//boundary test - 1st jan 1971
			front.tm_mon = 0; 
			front.tm_mday = 1;
			front.tm_year = 71;
			
			back.tm_mon = 0;  
			back.tm_mday = 31;
			back.tm_year = 71;

			lgUpdater.setWeekMonthOrNothing("");

			expectedResult = true;
			testResult = lgUpdater.isDisplayMonth(front,back);
			Assert::AreEqual(expectedResult,testResult);

			//boundary test - 31 dec 2999
			front.tm_mon = 11; 
			front.tm_mday = 1;
			front.tm_year = 1099;
			
			back.tm_mon = 11;  
			back.tm_mday = 31;
			back.tm_year = 1099;

			lgUpdater.setWeekMonthOrNothing("");

			expectedResult = true;
			testResult = lgUpdater.isDisplayMonth(front,back);
			Assert::AreEqual(expectedResult,testResult);
		}

		TEST_METHOD(LogicUpdater_isDisplayWeek_Test){
			// boundary cases for validty of dates are not covered here as they are targetted at tesing function countNumDays, 
			// which have been covered in the unit testing of UIShow.h as this function and implementation are the same 
			
			time_t now;
			struct tm front;
			struct tm back;
			bool testResult;
			bool expectedResult;

			time(&now);
			front = *localtime(&now);
			back = *localtime(&now);

			// true
			front.tm_mon = 0; 
			front.tm_mday = 4;
			front.tm_year = 115;
			
			back.tm_mon = 0;  
			back.tm_mday = 10;
			back.tm_year = 115;

			lgUpdater.setWeekMonthOrNothing("");

			expectedResult = true;
			testResult = lgUpdater.isDisplayWeek(front,back);
			Assert::AreEqual(expectedResult,testResult);

			// false - backdate 1 day before end of week
			front.tm_mon = 0; 
			front.tm_mday = 4;
			front.tm_year = 115;
			
			back.tm_mon = 0;  
			back.tm_mday = 9;
			back.tm_year = 115;

			lgUpdater.setWeekMonthOrNothing("");

			expectedResult = false;
			testResult = lgUpdater.isDisplayWeek(front,back);
			Assert::AreEqual(expectedResult,testResult);

			// false - frontdate 1 day after start of week
			front.tm_mon = 0; 
			front.tm_mday = 5;
			front.tm_year = 115;
			
			back.tm_mon = 0;  
			back.tm_mday = 10;
			back.tm_year = 115;

			lgUpdater.setWeekMonthOrNothing("");

			expectedResult = false;
			testResult = lgUpdater.isDisplayWeek(front,back);
			Assert::AreEqual(expectedResult,testResult);


			// weekMonthorNothing - month
			front.tm_mon = 0; 
			front.tm_mday = 5;
			front.tm_year = 115;
			
			back.tm_mon = 0;  
			back.tm_mday = 10;
			back.tm_year = 115;

			lgUpdater.setWeekMonthOrNothing("Week");

			expectedResult = true;
			testResult = lgUpdater.isDisplayWeek(front,back);
			Assert::AreEqual(expectedResult,testResult);

			// same date
			front.tm_mon = 1; 
			front.tm_mday = 8;
			front.tm_year = 115;
			
			back.tm_mon = 1;  
			back.tm_mday = 8;
			back.tm_year = 115;

			lgUpdater.setWeekMonthOrNothing("");

			expectedResult = false;
			testResult = lgUpdater.isDisplayWeek(front,back);
			Assert::AreEqual(expectedResult,testResult);

			// all valid, different weeks
			front.tm_mon = 0; 
			front.tm_mday = 4;
			front.tm_year = 115;
			
			back.tm_mon = 0;  
			back.tm_mday = 17;
			back.tm_year = 116;

			lgUpdater.setWeekMonthOrNothing("");

			expectedResult = false;
			testResult = lgUpdater.isDisplayMonth(front,back);
			Assert::AreEqual(expectedResult,testResult);
					
		}

		TEST_METHOD(LogicUpdater_intToTime_Test){
			int input;
			std::string testResult;
			std::string expectedResult;

			// normal
			input = 1531;
			testResult = "03:31pm";
			expectedResult=lgUpdater.intToTime(input);

			Assert::AreEqual(expectedResult,testResult);

			// boundary - 0000
			input = 0000;
			testResult = "00:00am";
			expectedResult=lgUpdater.intToTime(input);

			Assert::AreEqual(expectedResult,testResult);

			// boundary - 2359
			input = 2359;
			testResult = "11:59pm";
			expectedResult=lgUpdater.intToTime(input);

			Assert::AreEqual(expectedResult,testResult);

			// boundary - 1200
			input = 1200;
			testResult = "12:00pm";
			expectedResult=lgUpdater.intToTime(input);

			Assert::AreEqual(expectedResult,testResult);
		}

		TEST_METHOD(LogicUpdater_setSingleDayString_Test){
			time_t now;
			struct tm date;
			std::string testResult;
			std::string expectedResult;

			time(&now);
			date = *localtime(&now);

			// normal
			date.tm_mon = 0; 
			date.tm_mday = 4;
			date.tm_year = 115;

			testResult = "4 January 2015, Sunday";

			expectedResult=lgUpdater.setSingleDayString(date);

			Assert::AreEqual(expectedResult,testResult);
			
			//boundary - 1st jan 1971
			date.tm_mon = 0; 
			date.tm_mday = 1;
			date.tm_year = 71;

			testResult = "1 January 1971, Friday";

			expectedResult=lgUpdater.setSingleDayString(date);

			Assert::AreEqual(expectedResult,testResult);

			//boundary - 31 dec 2999
			date.tm_mon = 11; 
			date.tm_mday = 31;
			date.tm_year = 1099;

			testResult = "31 December 2999, Tuesday";

			expectedResult=lgUpdater.setSingleDayString(date);

			Assert::AreEqual(expectedResult,testResult);
		}


		TEST_METHOD(LogicUpdater_setMultipleDaysString_Test){
			time_t now;
			struct tm front;
			struct tm back;
			std::string testResult;
			std::string expectedResult;

			time(&now);
			front = *localtime(&now);
			back = *localtime(&now);

			// normal
			front.tm_mon = 0; 
			front.tm_mday = 4;
			front.tm_year = 115;
			
			back.tm_mon = 0;  
			back.tm_mday = 20;
			back.tm_year = 115;

			expectedResult = "4 January - 20 January 2015";
			testResult = lgUpdater.setMultipleDaysString(front,back);
			Assert::AreEqual(expectedResult,testResult);

			//very very large dates
			front.tm_mon = 0; 
			front.tm_mday = 4;
			front.tm_year = 115;
			
			back.tm_mon = 4;  
			back.tm_mday = 20;
			back.tm_year = 250;

			expectedResult = "4 January 2015 - 20 May 2150";
			testResult = lgUpdater.setMultipleDaysString(front,back);
			Assert::AreEqual(expectedResult,testResult);

			//boundary test - 1st jan 1971 - 31 dec 2999
			front.tm_mon = 0; 
			front.tm_mday = 1;
			front.tm_year = 71;
			
			back.tm_mon = 11;  
			back.tm_mday = 31;
			back.tm_year = 1099;

			expectedResult = "1 January 1971 - 31 December 2999";
			testResult = lgUpdater.setMultipleDaysString(front,back);
			Assert::AreEqual(expectedResult,testResult);
		}

		TEST_METHOD(LogicUpdater_setMainDisplayLabel_Test){
			time_t now;
			struct tm front;
			struct tm back;
			std::vector<tm> testVec;
			std::string testResult;
			std::string expectedResult;

			time(&now);
			front = *localtime(&now);
			back = *localtime(&now);

			//today & tomorrow are not tested as they changes everyday

			//week
			front.tm_mon = 0; 
			front.tm_mday = 4;
			front.tm_year = 115;
			
			back.tm_mon = 0;  
			back.tm_mday = 10;
			back.tm_year = 115;

			testVec.push_back(front);
			testVec.push_back(back);

			expectedResult = "[Week] 4 January - 10 January 2015";
			lgUpdater.setMainDisplayLabel(testVec);
			testResult = lgUpdater.getMainDisplayLabel();
			Assert::AreEqual(expectedResult,testResult);

			testVec.clear();

			//month
			front.tm_mon = 0; 
			front.tm_mday = 1;
			front.tm_year = 115;
			
			back.tm_mon = 0;  
			back.tm_mday = 31;
			back.tm_year = 115;

			testVec.push_back(front);
			testVec.push_back(back);

			expectedResult = "[Month] 1 January - 31 January 2015";
			lgUpdater.setMainDisplayLabel(testVec);
			testResult = lgUpdater.getMainDisplayLabel();
			Assert::AreEqual(expectedResult,testResult);

			testVec.clear();

			//single date 
			front.tm_mon = 0; 
			front.tm_mday = 1;
			front.tm_year = 115;
			
			back.tm_mon = 0;  
			back.tm_mday = 1;
			back.tm_year = 115;

			testVec.push_back(front);
			testVec.push_back(back);

			expectedResult = "1 January 2015, Thursday";
			lgUpdater.setMainDisplayLabel(testVec);
			testResult = lgUpdater.getMainDisplayLabel();
			Assert::AreEqual(expectedResult,testResult);

			testVec.clear();

			//boundary case - 1st jan 1971 - 31 dec 2999
			front.tm_mon = 0; 
			front.tm_mday = 1;
			front.tm_year = 71;
			
			back.tm_mon = 11;  
			back.tm_mday = 31;
			back.tm_year = 1099;

			testVec.push_back(front);
			testVec.push_back(back);

			expectedResult = "1 January 1971 - 31 December 2999";
			lgUpdater.setMainDisplayLabel(testVec);
			testResult = lgUpdater.getMainDisplayLabel();
			Assert::AreEqual(expectedResult,testResult);

			testVec.clear();
		}

		TEST_METHOD(LogicUpdater_setNormalEventDateString_Test){

			Event input;
			int inputIndex;
			std::string expectedResult;
			std::string testResult;

			//normal
			inputIndex = 10;
			input.setStartDate(5,5,2015);
			input.setStartTime(10,25);

			input.setEndDate(5,5,2015);
			input.setEndTime(11,45);

			expectedResult = "10.	[10:25am-11:45am]	";
			testResult= lgUpdater.setNormalEventDateString(input,inputIndex);
			Assert::AreEqual(expectedResult,testResult);

			//DUE
			inputIndex = 10;
			input.setStartDate(5,5,2015);
			input.setStartTime(11,45);

			input.setEndDate(5,5,2015);
			input.setEndTime(11,45);
			input.setIsDeadline(true);

			expectedResult = "10.	[*DUE*   11:45am]	";
			testResult= lgUpdater.setNormalEventDateString(input,inputIndex);
			Assert::AreEqual(expectedResult,testResult);

			//AllDay
			inputIndex = 10;
			input.setStartDate(5,5,2015);
			input.setStartTime(00,00);

			input.setEndDate(5,5,2015);
			input.setEndTime(23,59);
			input.setIsDeadline(false);

			expectedResult = "10.	[    All Day    ]	";
			testResult= lgUpdater.setNormalEventDateString(input,inputIndex);
			Assert::AreEqual(expectedResult,testResult);

			//boundary - 1st jan 1971
			inputIndex = 10;
			input.setStartDate(5,5,1971);
			input.setStartTime(00,00);

			input.setEndDate(5,5,1971);
			input.setEndTime(20,59);
			input.setIsDeadline(false);

			expectedResult = "10.	[00:00am-08:59pm]	";
			testResult= lgUpdater.setNormalEventDateString(input,inputIndex);
			Assert::AreEqual(expectedResult,testResult);

			//31 dec 2999
			inputIndex = 10;
			input.setStartDate(5,5,2999);
			input.setStartTime(00,00);

			input.setEndDate(5,5,2999);
			input.setEndTime(20,59);
			input.setIsDeadline(false);

			expectedResult = "10.	[00:00am-08:59pm]	";
			testResult= lgUpdater.setNormalEventDateString(input,inputIndex);
			Assert::AreEqual(expectedResult,testResult);
		}

		TEST_METHOD(LogicUpdater_setNormalEventEventString_Test){
			Event input;
			std::string expectedResult;
			std::string testResult;

			//normal
			input.setName("Hello");

			expectedResult = "Hello";
			testResult= lgUpdater.setNormalEventEventString(input);
			Assert::AreEqual(expectedResult,testResult);

			//empty string
			input.setName("");

			expectedResult = "";
			testResult= lgUpdater.setNormalEventEventString(input);
			Assert::AreEqual(expectedResult,testResult);

			//input string larger than 42
			input.setName("qwertyuiopqwertyuiopqwertyuiopqwertyuiopqwertyuiopqwert");

			expectedResult = "qwertyuiopqwertyuiopqwertyuiopqwertyuiopqw\n\t\t\t\t\tertyuiopqwert";
			testResult= lgUpdater.setNormalEventEventString(input);
			Assert::AreEqual(expectedResult,testResult);
		}

	};
}