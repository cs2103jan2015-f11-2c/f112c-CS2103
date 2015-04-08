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
			// true
			// false
			// true 

			// weekMonthorNothing - month

			// same date
			// all valid, different year
			// all valid, different month
			// front date later than back date

			//1st jan 1971
			//31 dec 2999
		}

		TEST_METHOD(LogicUpdater_isDisplayWeek_Test){
			// boundary cases for validty of dates are not covered here as they are targetted at tesing function countNumDays, 
			// which have been covered in the unit testing of UIShow.h as this function and implementation are the same 
			
			// true
			// false
			// true 

			// weekMonthorNothing week
			
			// normal
			// all valid, different year
			// all valid, different month
			// front date later than back date

			//1st jan 1971
			//31 dec 2999		
		}

		TEST_METHOD(LogicUpdater_intToTime_Test){
			// normal
			// 0000
			// negative time
			// 2359
			// hour above boundary 
			// min above boundary
		}

		TEST_METHOD(LogicUpdater_setSingleDayString_Test){
			//today
			//tomorrow
			//single date
			//1st jan 1971
			//31 dec 2999
		}


		TEST_METHOD(LogicUpdater_setMultipleDaysString_Test){
			//month
			//week
			//normal
			//very very large dates

			//1st jan 1971
			//31 dec 2999
		}

		TEST_METHOD(LogicUpdater_setMainDisplayLabel_Test){
			//today
			//tomorrow
			//week
			//month
			//single date 
			//very very large dates

			//1st jan 1971
			//31 dec 2999
		}

		TEST_METHOD(LogicUpdater_setMarkerEventString_Test){
			//index = 0
			//index = 1

			//normal

			//1st jan 1971
			//31 dec 2999
	
		}

		TEST_METHOD(LogicUpdater_setNormalEventDateString_Test){
			//normal

			//DUE
			//AllDay

			//1st jan 1971
			//31 dec 2999
		}

		TEST_METHOD(LogicUpdater_setNormalEventEventString_Test){
			//normal
			//empty string
			//very very very large string
		}

	};
}