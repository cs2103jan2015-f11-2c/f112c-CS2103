//@author A0113860M

#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#include "EventFacade.h"
#include "EventOrganiser.h"
#include "EventSearch.h"

namespace UnitTest
{
	TEST_CLASS(EventSearchTest)
	{
	public:
		EventSearch searcher;

		//finds event index in currentContent vector with event ID
		TEST_METHOD(EventSearch_searchIndexWithID_Test)
		{
			/*creating testing objects*/
			Event testEvent1, testEvent2, testEvent3, testEvent4;
			vector<Event> testCurrentContent;

			//creating test event 1
			testEvent1.setName("event1");
			testEvent1.setStartDate(5,3,115);
			testEvent1.setEndDate(7,3,115);
			testEvent1.setStartTime(5,5);
			testEvent1.setEndTime(6,6);
			testEvent1.setIsFloating(false);
			testEvent1.setID(111);

			//creating test event 2
			testEvent2.setName("event2");
			testEvent2.setStartDate(6,3,115);
			testEvent2.setEndDate(8,3,115);
			testEvent2.setStartTime(5,30);
			testEvent2.setEndTime(6,40);
			testEvent2.setIsFloating(false);
			testEvent2.setID(222);

			//creating test event 3
			testEvent3.setName("event3");
			testEvent3.setStartDate(5,3,115);
			testEvent3.setEndDate(7,3,115);
			testEvent3.setStartTime(1,30);
			testEvent3.setEndTime(6,40);
			testEvent3.setIsFloating(false);
			testEvent3.setID(333);

			//creating test event vector
			testCurrentContent.push_back(testEvent1);
			testCurrentContent.push_back(testEvent2);
			testCurrentContent.push_back(testEvent3);
			
			int result, expected;
			/*successful case: 1 search result*/
			expected = 1;
			result = searcher.searchIndexWithID(222,testCurrentContent);
			Assert::AreEqual(expected,result);

			/*boundary case: unsuccessful search */
			expected = -1;
			result = searcher.searchIndexWithID(000,testCurrentContent);
			Assert::AreEqual(expected,result);
		
			//creating test event 4
			testEvent4.setName("event4");
			testEvent4.setStartDate(11,3,115);
			testEvent4.setEndDate(12,3,115);
			testEvent4.setStartTime(2,30);
			testEvent4.setEndTime(3,10);
			testEvent4.setIsFloating(false);
			testEvent4.setID(222);
			
			//adding test cevent 4 to the vector
			testCurrentContent.push_back(testEvent4);
			
			/*boundary case: more than 1 search, takes first result */
			expected = 1;
			result = searcher.searchIndexWithID(222,testCurrentContent);
			Assert::AreEqual(expected,result);
		}

		//finds any name occurrences and returns events sorted by date with markers
		TEST_METHOD(EventSearch_searchCurrentNameOccurrence_test)
		{
			/*creating testing objects*/
			Event testEvent1, testEvent2, testEvent3, marker;
			vector<Event> testNormalContent, testFloatingContent;

			//creating test event 1
			testEvent1.setName("This is event1");
			testEvent1.setStartDate(5,3,115);
			testEvent1.setEndDate(5,3,115);
			testEvent1.setStartTime(5,5);
			testEvent1.setEndTime(6,6);
			testEvent1.setIsFloating(false);
			testEvent1.setID(1426225500);

			//creating test event 2
			testEvent2.setName("event3");
			testEvent2.setStartDate(6,3,115);
			testEvent2.setEndDate(6,3,115);
			testEvent2.setStartTime(5,30);
			testEvent2.setEndTime(6,40);
			testEvent2.setIsFloating(false);
			testEvent2.setID(1426225502);

			//creating test floating event 4
			/*test case: ignore completed*/
			testEvent3.setName("event999");
			testEvent3.setIsFloating(true);
			testEvent3.setID(1426225542);
			testEvent3.setIsCompleted(true);

			//creating marker
			marker.setName("-MSmsgjyw-");

			//creating test event vector
			testNormalContent.push_back(testEvent1);
			testNormalContent.push_back(testEvent2);
			testFloatingContent.push_back(testEvent3);

			EventStorage::storage().setNormalContent(testNormalContent);
			EventStorage::storage().setFloatingContent(testFloatingContent);

			vector<Event> result, expected;
			/*test case: Successful search returns vector of events*/
			expected.push_back(marker);
			expected.push_back(testEvent1);
			expected.push_back(marker);
			expected.push_back(testEvent2);
			result = searcher.searchCurrentNameOccurrence("event");
			
			Assert::AreEqual(expected[0].getName(),result[0].getName());
			Assert::AreEqual(expected[1].getName(),result[1].getName());
			Assert::AreEqual(expected[2].getName(),result[2].getName());
			Assert::AreEqual(expected[3].getName(),result[3].getName());

			/*test boundary case: Unsuccessful search returns empty vector */
			result = searcher.searchCurrentNameOccurrence("inexistentEvent");
			Assert::IsTrue(result.empty());
		}

		//find exact string name match and returns events sorted by date with markers
		TEST_METHOD(EventSearch_searchCurrentNameExact_test)
		{
			/*creating testing objects*/
			Event testEvent1, testEvent2, testEvent3, marker;
			vector<Event> testNormalContent, testFloatingContent;

			//creating test event 1
			testEvent1.setName("This is event1");
			testEvent1.setStartDate(5,3,115);
			testEvent1.setEndDate(5,3,115);
			testEvent1.setStartTime(5,5);
			testEvent1.setEndTime(6,6);
			testEvent1.setIsFloating(false);
			testEvent1.setID(1426225500);

			//creating test event 2
			testEvent2.setName("event111");
			testEvent2.setStartDate(6,3,115);
			testEvent2.setEndDate(8,3,115);
			testEvent2.setStartTime(5,30);
			testEvent2.setEndTime(6,40);
			testEvent2.setIsFloating(false);
			testEvent2.setID(1426225502);

			//creating test floating event 4
			/*test case: ignore completed*/
			testEvent3.setName("event999");
			testEvent3.setIsFloating(true);
			testEvent3.setID(1426225542);
			testEvent3.setIsCompleted(true);

			//creating marker
			marker.setName("-MSmsgjyw-");

			//creating test event vector
			testNormalContent.push_back(testEvent1);
			testNormalContent.push_back(testEvent2);
			testFloatingContent.push_back(testEvent3);

			EventStorage::storage().setNormalContent(testNormalContent);
			EventStorage::storage().setFloatingContent(testFloatingContent);

			vector<Event> result, expected;
			/*test case: Successful search returns vector of events*/
			expected.push_back(marker);
			expected.push_back(testEvent2);
			result = searcher.searchCurrentNameExact("event111");
			
			Assert::AreEqual(expected[0].getName(),result[0].getName());
			Assert::AreEqual(expected[1].getName(),result[1].getName());

			/*test boundary case: Unsuccessful search returns empty vector */
			result = searcher.searchCurrentNameExact("inexistentEvent");
			Assert::IsTrue(result.empty());
		}

		//finds importance level match
		TEST_METHOD(EventSearch_searchLevelImportance_test)
		{
			/*creating testing objects*/
			Event testEvent1, testEvent2, testEvent3, marker;
			vector<Event> testNormalContent, testFloatingContent;

			//creating test event 1
			testEvent1.setName("This is event1");
			testEvent1.setStartDate(5,3,115);
			testEvent1.setEndDate(5,3,115);
			testEvent1.setStartTime(5,5);
			testEvent1.setEndTime(6,6);
			testEvent1.setIsFloating(false);
			testEvent1.setID(1426225500);
			testEvent1.setImportanceLevel(3);

			//creating test event 2
			testEvent2.setName("3");
			testEvent2.setStartDate(6,3,115);
			testEvent2.setEndDate(8,3,115);
			testEvent2.setStartTime(5,30);
			testEvent2.setEndTime(6,40);
			testEvent2.setIsFloating(false);
			testEvent2.setID(1426225502);
			testEvent2.setImportanceLevel(1);

			//creating test event 3
			/*test case: finding floating importance*/
			testEvent3.setName("event3");
			testEvent3.setIsFloating(true);
			testEvent3.setID(1426225532);
			testEvent3.setImportanceLevel(3);

			//creating test event vector
			testNormalContent.push_back(testEvent1);
			testNormalContent.push_back(testEvent2);
			testFloatingContent.push_back(testEvent3);

			//creating marker
			marker.setName("-MSmsgjyw-");			

			EventStorage::storage().setNormalContent(testNormalContent);
			EventStorage::storage().setFloatingContent(testFloatingContent);

			vector<Event> result, expected;
			/*test case: Successful search returns vector of events*/
			expected.push_back(testEvent3);
			expected.push_back(marker);
			expected.push_back(testEvent1);
			result = searcher.searchLevelImportance(3);
			
			Assert::AreEqual(expected[0].getName(),result[0].getName());
			Assert::AreEqual(expected[1].getName(),result[1].getName());

			/*test boundary case: Unsuccessful search returns empty vector */
			result = searcher.searchLevelImportance(2);
			Assert::IsTrue(result.empty());
		}

		//finds all events with importance level greater than 0
		TEST_METHOD(EventSearch_searchAllImportance_test)
		{
			/*creating testing objects*/
			Event testEvent1, testEvent2, testEvent3, marker;
			vector<Event> testNormalContent, testFloatingContent;

			//creating test event 1
			testEvent1.setName("This is event1");
			testEvent1.setStartDate(5,3,115);
			testEvent1.setEndDate(5,3,115);
			testEvent1.setStartTime(5,5);
			testEvent1.setEndTime(6,6);
			testEvent1.setIsFloating(false);
			testEvent1.setID(1426225500);
			testEvent1.setImportanceLevel(3);

			//creating test event 2
			testEvent2.setName("3");
			testEvent2.setStartDate(6,3,115);
			testEvent2.setEndDate(8,3,115);
			testEvent2.setStartTime(5,30);
			testEvent2.setEndTime(6,40);
			testEvent2.setIsFloating(false);
			testEvent2.setID(1426225502);
			testEvent2.setImportanceLevel(0);

			//creating test event 3
			/*test case: finding floating importance*/
			testEvent3.setName("event3");
			testEvent3.setIsFloating(true);
			testEvent3.setID(1426225532);
			testEvent3.setImportanceLevel(3);

			//creating test event vector
			testNormalContent.push_back(testEvent1);
			testNormalContent.push_back(testEvent2);
			testFloatingContent.push_back(testEvent3);
			
			//creating marker
			marker.setName("-MSmsgjyw-");

			EventStorage::storage().setNormalContent(testNormalContent);
			EventStorage::storage().setFloatingContent(testFloatingContent);

			vector<Event> result, expected;
			/*test successful boundary case: 2 important events*/
			expected.push_back(testEvent3);
			expected.push_back(marker);
			expected.push_back(testEvent1);
			result = searcher.searchAllImportance();
			
			Assert::AreEqual(expected[0].getName(),result[0].getName());
			Assert::AreEqual(expected[1].getName(),result[1].getName());

			/*test boundary case: 0 important events*/
			testNormalContent.clear();
			testFloatingContent.clear();
			EventStorage::storage().setNormalContent(testNormalContent);
			EventStorage::storage().setFloatingContent(testFloatingContent);
			result = searcher.searchAllImportance();
			Assert::IsTrue(result.empty());
		}
	};
	TEST_CLASS(EventOrganiserTest)
	{
	public:
		EventOrganiser organiser;

		//filters normalContent vector for uncompleted events
		TEST_METHOD(EventOrganiser_allNormalCurrent_test)
		{
			/*creating testing objects*/
			Event testEvent1, testEvent2, testEvent3;
			vector<Event> testNormalContent;

			//creating test event 1
			testEvent1.setName("This is event1");
			testEvent1.setStartDate(5,3,115);
			testEvent1.setEndDate(5,3,115);
			testEvent1.setStartTime(5,5);
			testEvent1.setEndTime(6,6);
			testEvent1.setIsFloating(false);
			testEvent1.setID(1426225500);
			testEvent1.setIsCompleted(true);

			//creating test event 2
			testEvent2.setName("3");
			testEvent2.setStartDate(6,3,115);
			testEvent2.setEndDate(8,3,115);
			testEvent2.setStartTime(5,30);
			testEvent2.setEndTime(6,40);
			testEvent2.setIsFloating(false);
			testEvent2.setID(1426225502);
			testEvent2.setIsCompleted(false);

			//creating test event 3
			testEvent3.setName("event3");
			testEvent3.setStartDate(5,3,115);
			testEvent3.setEndDate(7,3,115);
			testEvent3.setStartTime(1,30);
			testEvent3.setEndTime(6,40);
			testEvent3.setIsFloating(false);
			testEvent3.setID(1426225532);
			testEvent3.setIsCompleted(true);

			//creating test event vector
			testNormalContent.push_back(testEvent1);
			testNormalContent.push_back(testEvent2);
			testNormalContent.push_back(testEvent3);

			EventStorage::storage().setNormalContent(testNormalContent);
			
			vector<Event> result, expected;
			/*boundary case: 1 uncompleted event*/
			expected.push_back(testEvent2);
			result = organiser.allNormalCurrent();
			
			Assert::AreEqual(expected[0].getName(),result[0].getName());

			/*boundary case: 0 uncompleted events*/
			testNormalContent.clear();
			EventStorage::storage().setNormalContent(testNormalContent);
			result = organiser.allNormalCurrent();
			Assert::IsTrue(result.empty());
		}
	
		//filters floatingContent vector for uncompleted events
		TEST_METHOD(EventOrganiser_allFloatingCurrent_test)
		{
			/*creating testing objects*/
			Event testEvent1, testEvent2, testEvent3;
			vector<Event> testFloatContent;

			//creating test event 1
			testEvent1.setName("This is event1");
			testEvent1.setIsFloating(true);
			testEvent1.setID(1426225500);
			testEvent1.setIsCompleted(true);

			//creating test event 2
			testEvent2.setName("floating");
			testEvent2.setIsFloating(true);
			testEvent2.setID(1426225502);
			testEvent2.setIsCompleted(false);

			//creating test event 3
			testEvent3.setName("event3");
			testEvent3.setIsFloating(true);
			testEvent3.setID(1426225532);
			testEvent3.setIsCompleted(true);

			//creating test event vector
			testFloatContent.push_back(testEvent1);
			testFloatContent.push_back(testEvent2);
			testFloatContent.push_back(testEvent3);

			EventStorage::storage().setFloatingContent(testFloatContent);
			
			vector<Event> result, expected;
			/*boundary case: 1 uncompleted event*/
			expected.push_back(testEvent2);
			result = organiser.allFloatingCurrent();
			
			Assert::AreEqual(expected[0].getName(),result[0].getName());

			/*boundary case: 0 uncompleted events*/
			testFloatContent.clear();
			EventStorage::storage().setFloatingContent(testFloatContent);
			result = organiser.allFloatingCurrent();
			Assert::IsTrue(result.empty());
		}


		//filters normalContent vector for completed events
		TEST_METHOD(EventOrgansier_allNormalCompleted_test)
		{
			/*creating testing objects*/
			Event testEvent1, testEvent2, testEvent3;
			vector<Event> testNormalContent;

			//creating test event 1
			testEvent1.setName("This is event1");
			testEvent1.setStartDate(5,3,115);
			testEvent1.setEndDate(5,3,115);
			testEvent1.setStartTime(5,5);
			testEvent1.setEndTime(6,6);
			testEvent1.setIsFloating(false);
			testEvent1.setID(1426225500);
			testEvent1.setIsCompleted(true);

			//creating test event 2
			testEvent2.setName("test2");
			testEvent2.setStartDate(6,3,115);
			testEvent2.setEndDate(8,3,115);
			testEvent2.setStartTime(5,30);
			testEvent2.setEndTime(6,40);
			testEvent2.setIsFloating(false);
			testEvent2.setID(1426225502);
			testEvent2.setIsCompleted(false);

			//creating test event 3
			testEvent3.setName("event3");
			testEvent3.setStartDate(5,3,115);
			testEvent3.setEndDate(7,3,115);
			testEvent3.setStartTime(1,30);
			testEvent3.setEndTime(6,40);
			testEvent3.setIsFloating(false);
			testEvent3.setID(1426225532);
			testEvent3.setIsCompleted(true);

			//creating test event vector
			testNormalContent.push_back(testEvent1);
			testNormalContent.push_back(testEvent2);
			testNormalContent.push_back(testEvent3);

			EventStorage::storage().setNormalContent(testNormalContent);
			
			vector<Event> result, expected;
			/*boundary case: existing completed event*/
			expected.push_back(testEvent1);
			expected.push_back(testEvent3);
			result = organiser.allNormalCompleted();
			
			Assert::AreEqual(expected[0].getName(),result[0].getName());
			Assert::AreEqual(expected[1].getName(),result[1].getName());

			/*boundary case: 0 completed events*/
			testNormalContent.clear();
			EventStorage::storage().setNormalContent(testNormalContent);
			result = organiser.allNormalCompleted();
			Assert::IsTrue(result.empty());
		}

		//filters floatingContent for completed events
		TEST_METHOD(EventOrganiser_allFloatingCompleted_test)
		{
			/*creating testing objects*/
			Event testEvent1, testEvent2, testEvent3;
			vector<Event> testFloatContent;

			//creating test event 1
			testEvent1.setName("This is event1");
			testEvent1.setIsFloating(true);
			testEvent1.setID(1426225500);
			testEvent1.setIsCompleted(true);

			//creating test event 2
			testEvent2.setName("floating");
			testEvent2.setIsFloating(true);
			testEvent2.setID(1426225502);
			testEvent2.setIsCompleted(false);

			//creating test event 3
			testEvent3.setName("event3");
			testEvent3.setIsFloating(true);
			testEvent3.setID(1426225532);
			testEvent3.setIsCompleted(true);

			//creating test event vector
			testFloatContent.push_back(testEvent1);
			testFloatContent.push_back(testEvent2);
			testFloatContent.push_back(testEvent3);

			EventStorage::storage().setFloatingContent(testFloatContent);
			
			vector<Event> result, expected;
			/*boundary case: existing completed event*/
			expected.push_back(testEvent1);
			expected.push_back(testEvent3);
			result = organiser.allFloatingCompleted();
			
			Assert::AreEqual(expected[0].getName(),result[0].getName());
			Assert::AreEqual(expected[1].getName(),result[1].getName());

			/*boundary case: 0 completed events*/
			testFloatContent.clear();
			EventStorage::storage().setFloatingContent(testFloatContent);
			result = organiser.allFloatingCompleted();
			Assert::IsTrue(result.empty());
		}

		//set normalContents by appending current task onto completed task 
		TEST_METHOD(EventOrganiser_saveNormal_test)
		{
			/*creating testing objects*/
			Event testEvent1, testEvent2, testEvent3;
			vector<Event> testNormalContent;

			//creating test event 1
			testEvent1.setName("This is event1");
			testEvent1.setStartDate(5,3,115);
			testEvent1.setEndDate(5,3,115);
			testEvent1.setStartTime(5,5);
			testEvent1.setEndTime(6,6);
			testEvent1.setIsFloating(false);
			testEvent1.setID(1426225500);
			testEvent1.setIsCompleted(true);

			//creating test event 2
			testEvent2.setName("test2");
			testEvent2.setStartDate(6,3,115);
			testEvent2.setEndDate(8,3,115);
			testEvent2.setStartTime(5,30);
			testEvent2.setEndTime(6,40);
			testEvent2.setIsFloating(false);
			testEvent2.setID(1426225502);
			testEvent2.setIsCompleted(false);
			
			//setting currentContent stub
			testNormalContent.push_back(testEvent1);
			testNormalContent.push_back(testEvent2);
			EventStorage::storage().setNormalContent(testNormalContent);

			//creating test event 3
			testEvent3.setName("event3");
			testEvent3.setStartDate(5,3,115);
			testEvent3.setEndDate(7,3,115);
			testEvent3.setStartTime(1,30);
			testEvent3.setEndTime(6,40);
			testEvent3.setIsFloating(false);
			testEvent3.setID(1426225532);
			testEvent3.setIsCompleted(false);
			
			testNormalContent.clear();
			testNormalContent.push_back(testEvent3);
						
			vector<Event> result, expected;
			/*boundary case: existing completed event*/

			organiser.saveNormal(testNormalContent);
			
			expected.push_back(testEvent3);
			expected.push_back(testEvent1);
			result = EventStorage::storage().getNormalContent();

			Assert::AreEqual(expected[0].getName(),result[0].getName());
			Assert::AreEqual(expected[1].getName(),result[1].getName());

			/*boundary case: 0 completed events, 1 uncompleted*/
			//setting curretnContent stub
			testNormalContent.clear();
			testNormalContent.push_back(testEvent2);
			EventStorage::storage().setNormalContent(testNormalContent);
			//set temp
			testNormalContent.clear();
			testNormalContent.push_back(testEvent3);
		
			organiser.saveNormal(testNormalContent);

			expected.clear();
			result.clear();
			expected.push_back(testEvent3);
			result = EventStorage::storage().getNormalContent();
			Assert::AreEqual(expected[0].getName(),result[0].getName());
		}

		//set floatingContent by appending current task onto completed task 
		TEST_METHOD(EventOrganiser_saveFloating_test)
		{
			/*creating testing objects*/
			Event testEvent1, testEvent2, testEvent3;
			vector<Event> testContent;

			//creating test event 1
			testEvent1.setName("event1");
			testEvent1.setIsFloating(true);
			testEvent1.setID(1426225500);
			testEvent1.setIsCompleted(true);

			//creating test event 2
			testEvent2.setName("event2");
			testEvent2.setIsFloating(true);
			testEvent2.setID(1426225502);
			testEvent2.setIsCompleted(false);
			
			//setting currentContent stub
			testContent.push_back(testEvent1);
			testContent.push_back(testEvent2);
			EventStorage::storage().setFloatingContent(testContent);

			//creating test event 3
			testEvent3.setName("event3");
			testEvent3.setIsFloating(true);
			testEvent3.setID(1426225532);
			testEvent3.setIsCompleted(false);
			
			testContent.clear();
			testContent.push_back(testEvent3);
						
			vector<Event> result, expected;
			/*boundary case: There is existing completed event*/
			organiser.saveFloating(testContent);
			
			expected.push_back(testEvent3);
			expected.push_back(testEvent1);
			result = EventStorage::storage().getFloatingContent();

			Assert::AreEqual(expected[0].getName(),result[0].getName());
			Assert::AreEqual(expected[1].getName(),result[1].getName());

			/*boundary case: 0 completed events, 1 uncompleted*/
			//setting curretnContent stub
			testContent.clear();
			testContent.push_back(testEvent2);
			EventStorage::storage().setFloatingContent(testContent);
			//set temp
			testContent.clear();
			testContent.push_back(testEvent3);
		
			organiser.saveFloating(testContent);

			expected.clear();
			result.clear();
			expected.push_back(testEvent3);
			result = EventStorage::storage().getFloatingContent();
			Assert::AreEqual(expected[0].getName(),result[0].getName());
		}

		//set normalContents by appending completed task onto current task 
		TEST_METHOD(EventOrganiser_saveNormalCompleted_test)
		{
			/*creating testing objects*/
			Event testEvent1, testEvent2, testEvent3;
			vector<Event> testNormalContent;

			//creating test event 1
			testEvent1.setName("This is event1");
			testEvent1.setStartDate(5,3,115);
			testEvent1.setEndDate(5,3,115);
			testEvent1.setStartTime(5,5);
			testEvent1.setEndTime(6,6);
			testEvent1.setIsFloating(false);
			testEvent1.setID(1426225500);
			testEvent1.setIsCompleted(false);

			//creating test event 2
			testEvent2.setName("test2");
			testEvent2.setStartDate(6,3,115);
			testEvent2.setEndDate(8,3,115);
			testEvent2.setStartTime(5,30);
			testEvent2.setEndTime(6,40);
			testEvent2.setIsFloating(false);
			testEvent2.setID(1426225502);
			testEvent2.setIsCompleted(true);
			
			//setting currentContent stub
			testNormalContent.push_back(testEvent1);
			testNormalContent.push_back(testEvent2);
			EventStorage::storage().setNormalContent(testNormalContent);

			//creating test event 3
			testEvent3.setName("event3");
			testEvent3.setStartDate(5,3,115);
			testEvent3.setEndDate(7,3,115);
			testEvent3.setStartTime(1,30);
			testEvent3.setEndTime(6,40);
			testEvent3.setIsFloating(false);
			testEvent3.setID(1426225532);
			testEvent3.setIsCompleted(true);
			
			testNormalContent.clear();
			testNormalContent.push_back(testEvent3);
						
			vector<Event> result, expected;
			/*boundary case: existing uncompleted event*/
			organiser.saveNormalCompleted(testNormalContent);
			
			expected.push_back(testEvent1);
			expected.push_back(testEvent3);
			result = EventStorage::storage().getNormalContent();

			Assert::AreEqual(expected[0].getName(),result[0].getName());
			Assert::AreEqual(expected[1].getName(),result[1].getName());

			/*boundary case: 1 completed event, 0 uncompleted*/
			//setting curretnContent stub
			testNormalContent.clear();
			testNormalContent.push_back(testEvent2);
			EventStorage::storage().setNormalContent(testNormalContent);
			//set temp
			testNormalContent.clear();
			testNormalContent.push_back(testEvent3);
		
			organiser.saveNormalCompleted(testNormalContent);

			expected.clear();
			result.clear();
			expected.push_back(testEvent3);
			result = EventStorage::storage().getNormalContent();
			Assert::AreEqual(expected[0].getName(),result[0].getName());
		}
			
		//set floatingContent by appending completed task onto current task 
		TEST_METHOD(EventOrganiser_saveFloatingCompleted_test)
		{
			/*creating testing objects*/
			Event testEvent1, testEvent2, testEvent3;
			vector<Event> testContent;

			//creating test event 1
			testEvent1.setName("event1");
			testEvent1.setIsFloating(true);
			testEvent1.setID(1426225500);
			testEvent1.setIsCompleted(false);

			//creating test event 2
			testEvent2.setName("event2");
			testEvent2.setIsFloating(true);
			testEvent2.setID(1426225502);
			testEvent2.setIsCompleted(true);
			
			//setting floating Content stub
			testContent.push_back(testEvent1);
			testContent.push_back(testEvent2);
			EventStorage::storage().setFloatingContent(testContent);

			//creating test event 3
			testEvent3.setName("event3");
			testEvent3.setIsFloating(true);
			testEvent3.setID(1426225532);
			testEvent3.setIsCompleted(true);
			
			//setting vector to save
			testContent.clear();
			testContent.push_back(testEvent3);

			vector<Event> result, expected;
			/*boundary case: There are existing uncompleted events when saving*/
			organiser.saveFloatingCompleted(testContent);
			
			expected.push_back(testEvent1);
			expected.push_back(testEvent3);
			result = EventStorage::storage().getFloatingContent();

			Assert::AreEqual(expected[0].getName(),result[0].getName());
			Assert::AreEqual(expected[1].getName(),result[1].getName());

			/*boundary case: 1 completed event, 0 uncompleted*/
			//setting curretnContent stub
			testContent.clear();
			testContent.push_back(testEvent2);
			EventStorage::storage().setFloatingContent(testContent);
			//set temp
			testContent.clear();
			testContent.push_back(testEvent3);
		
			organiser.saveFloatingCompleted(testContent);

			expected.clear();
			result.clear();
			expected.push_back(testEvent3);
			result = EventStorage::storage().getFloatingContent();
			Assert::AreEqual(expected[0].getName(),result[0].getName());
		}
		
		TEST_METHOD(EventOrganiser_showEvents_Test)
		{
			/*creating testing objects*/
			Event testEvent1, testEvent2, marker;
			vector<Event> testNormalContent;

			//creating test event 1
			testEvent1.setName("This is event1");
			testEvent1.setStartDate(5,3,115);
			testEvent1.setEndDate(5,3,115);
			testEvent1.setStartTime(5,5);
			testEvent1.setEndTime(6,6);
			testEvent1.setIsFloating(false);
			testEvent1.setID(1426225500);
			testEvent1.setIsCompleted(false);

			//creating test event 2
			testEvent2.setName("test2");
			testEvent2.setStartDate(6,3,115);
			testEvent2.setEndDate(6,3,115);
			testEvent2.setStartTime(5,30);
			testEvent2.setEndTime(6,40);
			testEvent2.setIsFloating(false);
			testEvent2.setID(1426225502);
			testEvent2.setIsCompleted(false);

			//creating stub contentVector
			testNormalContent.push_back(testEvent1);
			testNormalContent.push_back(testEvent2);
			
			//creating marker
			marker.setName("-MSmsgjyw-");

			vector<Event> result, expected;
			expected.push_back(marker);
			expected.push_back(testEvent1);
			expected.push_back(marker);
			expected.push_back(testEvent2);
			
			/*successful case*/
			result = organiser.showEvents(testNormalContent);
			Assert::AreEqual(expected[0].getName(),result[0].getName());
			Assert::AreEqual(expected[1].getName(),result[1].getName());
			Assert::AreEqual(expected[2].getName(),result[2].getName());
			Assert::AreEqual(expected[3].getName(),result[3].getName());

			/*empty case:*/
			expected.clear();
			result.clear();
			testNormalContent.clear();
			result = organiser.showEvents(testNormalContent);
			Assert::IsTrue(result.empty());

		}
	};

	TEST_CLASS(EventFacadeTest)
	{
	public:
		EventFacade facade;

		//finds event index in currentContent vector with event ID
		TEST_METHOD(EventFacade_addEvent_test)
		{
			/*creating testing objects*/
			Event testEvent1, testEvent2, marker;
			vector<Event> testNormalContent, expected, result;

			//creating marker
			marker.setName("-MSmsgjyw-");

			//creating test event 1
			testEvent1.setName("This is event1");
			testEvent1.setStartDate(5,3,115);
			testEvent1.setEndDate(5,3,115);
			testEvent1.setStartTime(5,5);
			testEvent1.setEndTime(6,6);
			testEvent1.setIsFloating(false);
			testEvent1.setID(1426225500);
			testEvent1.setIsCompleted(false);

			/*test case: add single event in empty storage*/
			result = facade.addEvent(testEvent1);

			expected.push_back(marker);
			expected.push_back(testEvent1);
			Assert::AreEqual(expected[0].getName(),result[0].getName());
			Assert::AreEqual(expected[1].getName(),result[1].getName());

			/*test case: add single event with exisiting event in storage*/
			result.clear();
			expected.clear();

			//creating stub contentVector
			testNormalContent.push_back(testEvent1);
			EventStorage::storage().setNormalContent(testNormalContent);

			//creating test event 2
			testEvent2.setName("test2");
			testEvent2.setStartDate(6,3,115);
			testEvent2.setEndDate(6,3,115);
			testEvent2.setStartTime(5,30);
			testEvent2.setEndTime(6,40);
			testEvent2.setIsFloating(false);
			testEvent2.setID(1426225502);
			testEvent2.setIsCompleted(false);

			result = facade.addEvent(testEvent2);

			expected.push_back(marker);
			expected.push_back(testEvent2);
			expected.push_back(marker);
			expected.push_back(testEvent1);
			
			Assert::AreEqual(expected[0].getName(),result[0].getName());
			Assert::AreEqual(expected[1].getName(),result[1].getName());
		//	Assert::AreEqual(expected[2].getName(),result[2].getName());
		//	Assert::AreEqual(expected[3].getName(),result[3].getName());

			/*test case: add single floating event with empty storage*/
			result.clear();
			expected.clear();

			Event testFloat1;
			vector<Event> testFloatContent;

			//creating test event 1
			testFloat1.setName("event1");
			testFloat1.setIsFloating(true);
			testFloat1.setID(1426225500);
			testFloat1.setIsCompleted(false);	

			expected.push_back(testFloat1);
			result = facade.addEvent(testFloat1);
			Assert::AreEqual(expected[0].getName(),result[0].getName());

			/*test case: add single floating event with exisitng normal in storage*/
			result.clear();
			expected.clear();
			testNormalContent.clear();

			//creating stub contentVector
			testNormalContent.push_back(testEvent1);
			EventStorage::storage().setNormalContent(testNormalContent);

			expected.push_back(testFloat1);
			result = facade.addEvent(testFloat1);
			Assert::AreEqual(expected[0].getName(),result[0].getName());
		
			/*test case: add single normal event with exisitng float in storage*/
			result.clear();
			expected.clear();
			testFloatContent.clear();

			//creating stub contentVector
			testFloatContent.push_back(testEvent1);
			EventStorage::storage().setFloatingContent(testFloatContent);

			expected.push_back(marker);
			expected.push_back(testEvent1);

			result = facade.addEvent(testEvent1);
			Assert::AreEqual(expected[0].getName(),result[0].getName());
			Assert::AreEqual(expected[1].getName(),result[1].getName());
		}
	};
}