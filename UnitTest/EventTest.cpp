//@author A0111089L
#include "stdafx.h"
#include "CppUnitTest.h"
#include "Event.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	TEST_CLASS(EventTest)
	{
	public:
		
		TEST_METHOD(Event_setName_getName_Test)
		{
			Event e;
			
			//test partition of string consisting of only letters
			e.setName("name");
			string name = "name";
			Assert::AreEqual(e.getName(), name);

			//test partition of string consisting of only numbers
			e.setName("123");
			name = "123";
			Assert::AreEqual(e.getName(), name);

			//test partition of string consisting of both numbers and letters
			e.setName("123abc");
			name = "123abc";
			Assert::AreEqual(e.getName(), name);
		}


		TEST_METHOD(Event_setDate_getDate_Test)
		{
			//test partition of valid date
			Event e1;
			e1.setStartDate(1, 1, 115);
			tm time;
			time.tm_mday = 1;
			time.tm_mon = 1;
			time.tm_year = 115;
			Assert::AreEqual(e1.getStartDate().tm_mday, time.tm_mday);
			Assert::AreEqual(e1.getStartDate().tm_mon, time.tm_mon);
			Assert::AreEqual(e1.getStartDate().tm_year, time.tm_year);

			//test partition of invalid date
			Event e2;
			e2.setStartDate(-1, -1, -1);
			tm time1;
			time1.tm_mday = -1;
			time1.tm_mon = -1;
			time1.tm_year = -1;
			Assert::AreEqual(e2.getStartDate().tm_mday, time1.tm_mday);
			Assert::AreEqual(e2.getStartDate().tm_mon, time1.tm_mon);
			Assert::AreEqual(e2.getStartDate().tm_year, time1.tm_year);
		}


		TEST_METHOD(Event_setTime_getTime_Test)
		{
			//test partition of valid time
			Event e1;
			e1.setStartTime(1, 1);
			tm time;
			time.tm_hour = 1;
			time.tm_min = 1;
			Assert::AreEqual(e1.getStartDate().tm_hour, time.tm_hour);
			Assert::AreEqual(e1.getStartDate().tm_min, time.tm_min);

			//test partition of invalid time
			Event e2;
			e2.setStartTime(-1, -1);
			tm time1;
			time1.tm_hour = -1;
			time1.tm_min = -1;
			Assert::AreEqual(e2.getStartDate().tm_hour, time1.tm_hour);
			Assert::AreEqual(e2.getStartDate().tm_min, time1.tm_min);
		}
		
		TEST_METHOD(Event_setIsFloating_getIsFloating_Test)
		{
			Event e;
			
			//test partition of isFloating == true
			e.setIsFloating(true);
			bool floating = true;
			Assert::AreEqual(e.getIsFloating(), floating);

			//test partition of isFloating == false
			e.setIsFloating(false);
			floating = false;
			Assert::AreEqual(e.getIsFloating(), floating);
		}


		TEST_METHOD(Event_setIsDeadline_getIsDeadline_Test)
		{
			Event e;
			
			//test partition of isDeadline == true
			e.setIsDeadline(true);
			bool deadline = true;
			Assert::AreEqual(e.getIsDeadline(), deadline);

			//test partition of isDeadline == false
			e.setIsDeadline(false);
			deadline = false;
			Assert::AreEqual(e.getIsDeadline(), deadline);
		}


		TEST_METHOD(Event_setIsCompleted_getIsCompleted_Test)
		{
			Event e;
			
			//test partition of isDeadline == true
			e.setIsCompleted(true);
			bool completed = true;
			Assert::AreEqual(e.getIsCompleted(), completed);

			//test partition of isDeadline == false
			e.setIsCompleted(false);
			completed = false;
			Assert::AreEqual(e.getIsCompleted(), completed);
		}


		TEST_METHOD(Event_setImportanceLevel_getImportanceLevel_Test)
		{
			Event e;
			
			//test partition of negative importance (out of bounds, should be set to 0)
			e.setImportanceLevel(-1);
			int importance = 0;
			Assert::AreEqual(e.getImportanceLevel(), importance);

			//test partition of importance == 0
			e.setImportanceLevel(0);
			importance = 0;
			Assert::AreEqual(e.getImportanceLevel(), importance);

			//test partition of importance == 3 (maximum)
			e.setImportanceLevel(3);
			importance = 3;
			Assert::AreEqual(e.getImportanceLevel(), importance);

			//test partition of importance == 4 (out of bounds, should be set to 3)
			e.setImportanceLevel(4);
			importance = 3;
			Assert::AreEqual(e.getImportanceLevel(), importance);
		}


		TEST_METHOD(Event_setFeedback_getFeedback_Test)
		{
			Event e;
			
			//test partition of string consisting of only letters
			e.setFeedback("feedback");
			string feedback = "feedback";
			Assert::AreEqual(e.getFeedback(), feedback);

			//test partition of string consisting of only numbers
			e.setFeedback("123");
			feedback = "123";
			Assert::AreEqual(e.getFeedback(), feedback);

			//test partition of string consisting of both numbers and letters
			e.setFeedback("123abc");
			feedback = "123abc";
			Assert::AreEqual(e.getFeedback(), feedback);
		}


		TEST_METHOD(Event_setID_getID_Test)
		{
			Event e;
			
			//test partition of negative id
			e.setID(-1);
			int id = -1;
			Assert::AreEqual(e.getID(), id);

			//test partition of id == 0
			e.setID(0);
			id = 0;
			Assert::AreEqual(e.getID(), id);

			//test partition of positive id
			e.setID(12345678);
			id = 12345678;
			Assert::AreEqual(e.getID(), id);
		}
	};


}