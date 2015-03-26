#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#include "EventStorage.h"
#include "EventOrganiser.h"
#include "Search.h"

namespace UnitTest
{
	TEST_CLASS(SearchTest)
	{
	public:
		Search search;
		TEST_METHOD(searchIndexWithID_Test)
		{
			/*creating testing objects*/
			Event testEvent1, testEvent2, testEvent3, testEvent4;
			vector<Event> testCurrentContent;
			testEvent1.setName("event1");
			testEvent1.setStartDate(5,3,15);
			testEvent1.setEndDate(7,3,15);
			testEvent1.setStartTime(5,5);
			testEvent1.setEndTime(6,6);
			testEvent1.setIsFloating(false);
			testEvent1.setID(1426225500);

			testEvent2.setName("event2");
			testEvent2.setStartDate(6,3,15);
			testEvent2.setEndDate(8,3,15);
			testEvent2.setStartTime(5,30);
			testEvent2.setEndTime(6,40);
			testEvent2.setIsFloating(false);
			testEvent2.setID(1426225502);

			testEvent3.setName("event3");
			testEvent3.setStartDate(5,3,15);
			testEvent3.setEndDate(7,3,15);
			testEvent3.setStartTime(1,30);
			testEvent3.setEndTime(6,40);
			testEvent3.setIsFloating(false);
			testEvent3.setID(1426225532);

			testEvent4.setName("event4");
			testEvent4.setStartDate(11,3,15);
			testEvent4.setEndDate(12,3,15);
			testEvent4.setStartTime(2,30);
			testEvent4.setEndTime(3,10);
			testEvent4.setIsFloating(false);
			testEvent4.setID(1426225542);

			testCurrentContent.push_back(testEvent1);
			testCurrentContent.push_back(testEvent2);
			testCurrentContent.push_back(testEvent3);
			testCurrentContent.push_back(testEvent4);
			
			int result, expected;
			/*This is for successful search*/
			expected = 2;
			result = search.searchIndexWithID(1426225532,testCurrentContent);
			Assert::AreEqual(expected,result);
			/* This is for unsuccessful search */
			expected = -1;
			result = search.searchIndexWithID(000,testCurrentContent);
			Assert::AreEqual(expected,result);
		}
		TEST_METHOD(searchEventWithName_Test)
		{
			/*creating testing objects*/
			Event testEvent1, testEvent2, testEvent3, testEvent4;
			vector<Event> testCurrentContent;
			testEvent1.setName("event1");
			testEvent1.setStartDate(5,3,15);
			testEvent1.setEndDate(7,3,15);
			testEvent1.setStartTime(5,5);
			testEvent1.setEndTime(6,6);
			testEvent1.setIsFloating(false);
			testEvent1.setID(1426225500);

			testEvent2.setName("event2");
			testEvent2.setStartDate(6,3,15);
			testEvent2.setEndDate(8,3,15);
			testEvent2.setStartTime(5,30);
			testEvent2.setEndTime(6,40);
			testEvent2.setIsFloating(false);
			testEvent2.setID(1426225502);

			testEvent3.setName("event3");
			testEvent3.setStartDate(5,3,15);
			testEvent3.setEndDate(7,3,15);
			testEvent3.setStartTime(1,30);
			testEvent3.setEndTime(6,40);
			testEvent3.setIsFloating(false);
			testEvent3.setID(1426225532);

			testEvent4.setName("event345");
			testEvent4.setStartDate(11,3,15);
			testEvent4.setEndDate(12,3,15);
			testEvent4.setStartTime(2,30);
			testEvent4.setEndTime(3,10);
			testEvent4.setIsFloating(false);
			testEvent4.setID(1426225542);

			testCurrentContent.push_back(testEvent1);
			testCurrentContent.push_back(testEvent2);
			testCurrentContent.push_back(testEvent3);
			testCurrentContent.push_back(testEvent4);

			vector<Event> result, expected;
			/*Successful search returns vector of events*/
			expected.push_back(testEvent3);
			expected.push_back(testEvent4);
			result = search.searchEventWithName("event3",testCurrentContent);
			Assert::AreEqual(expected[0].getName(),result[0].getName());
			Assert::AreEqual(expected[1].getName(),result[1].getName());
			/* Unsuccessful search returns empty vector */
			expected.clear();
			result = search.searchEventWithName("inexistentEvent",testCurrentContent);
			Assert::IsTrue(result.empty());
		}
		TEST_METHOD(searchExactName_Test)
		{
			/*creating testing objects*/
			Event testEvent1, testEvent2, testEvent3, testEvent4;
			vector<Event> testCurrentContent;
			testEvent1.setName("event1");
			testEvent1.setStartDate(5,3,15);
			testEvent1.setEndDate(7,3,15);
			testEvent1.setStartTime(5,5);
			testEvent1.setEndTime(6,6);
			testEvent1.setIsFloating(false);
			testEvent1.setID(1426225500);

			testEvent2.setName("event2");
			testEvent2.setStartDate(6,3,15);
			testEvent2.setEndDate(8,3,15);
			testEvent2.setStartTime(5,30);
			testEvent2.setEndTime(6,40);
			testEvent2.setIsFloating(false);
			testEvent2.setID(1426225502);

			testEvent3.setName("event3");
			testEvent3.setStartDate(5,3,15);
			testEvent3.setEndDate(7,3,15);
			testEvent3.setStartTime(1,30);
			testEvent3.setEndTime(6,40);
			testEvent3.setIsFloating(false);
			testEvent3.setID(1426225532);

			testEvent4.setName("event3");
			testEvent4.setStartDate(11,3,15);
			testEvent4.setEndDate(12,3,15);
			testEvent4.setStartTime(2,30);
			testEvent4.setEndTime(3,10);
			testEvent4.setIsFloating(false);
			testEvent4.setID(1426225542);

			testCurrentContent.push_back(testEvent1);
			testCurrentContent.push_back(testEvent2);
			testCurrentContent.push_back(testEvent3);
			testCurrentContent.push_back(testEvent4);

			vector<Event> result, expected;
			/*Successful search returns vector of events*/
			expected.push_back(testEvent3);
			expected.push_back(testEvent4);
			result = search.searchExactName("event3",testCurrentContent);
			Assert::AreEqual(expected[0].getName(),result[0].getName());
			Assert::AreEqual(expected[1].getName(),result[1].getName());
			/* Unsuccessful search returns empty vector */
			expected.clear();
			result = search.searchExactName("inexistentEvent",testCurrentContent);
			Assert::IsTrue(result.empty());
		}
	};
}