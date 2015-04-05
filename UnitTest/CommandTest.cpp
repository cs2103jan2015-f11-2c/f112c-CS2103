#include "stdafx.h"
#include "CppUnitTest.h"
#include "Command.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	TEST_CLASS(CommandTest)
	{
	public:
		Event emptyEvent;
		vector<Event> eventVec;
		EventFacade eventFacade;

		TEST_METHOD(Command_getNumEvents_Test)
		{
			//dummy command
			Command* commandPtr = new AddCommand(&eventFacade, emptyEvent);

			Event floating, normalName, normal;
			floating.setIsFloating(true);
			floating.setName("float");
			floating.setID(1);
			normalName.setIsFloating(false);
			normalName.setName("-MSmsgjyw-");
			normalName.setID(-1);
			normal.setIsFloating(false);
			normal.setName("normal");
			normal.setID(2);


			//test partition of only floating events in event vector
			eventVec.push_back(floating);
			Assert::AreEqual(commandPtr->getNumEvents(eventVec), 1);
			eventVec.clear();


			//test partition of only normal events in event vector
			eventVec.push_back(normalName);
			eventVec.push_back(normal);
			Assert::AreEqual(commandPtr->getNumEvents(eventVec), 1);
			eventVec.clear();


			//test partition of both floating and normal events in event vector
			eventVec.push_back(floating);
			eventVec.push_back(normalName);
			eventVec.push_back(normal);
			Assert::AreEqual(commandPtr->getNumEvents(eventVec), 2);
			eventVec.clear();
		}


		TEST_METHOD(Command_getEventFromID_Test)
		{
			//dummy command
			Command* commandPtr = new AddCommand(&eventFacade, emptyEvent);

			Event floating, normalName, normal;
			floating.setIsFloating(true);
			floating.setName("float");
			floating.setID(1);
			normalName.setIsFloating(false);
			normalName.setName("-MSmsgjyw-");
			normalName.setID(-1);
			normal.setIsFloating(false);
			normal.setName("normal");
			normal.setID(2);


			//test partition of only floating events in event vector
			eventVec.push_back(floating);
			Assert::AreEqual(commandPtr->getEventFromID(eventVec, 1).getID(), floating.getID());
			eventVec.clear();


			//test partition of only normal events in event vector
			eventVec.push_back(normalName);
			eventVec.push_back(normal);
			Assert::AreEqual(commandPtr->getEventFromID(eventVec, 2).getID(), normal.getID());
			eventVec.clear();


			//test partition of both floating and normal events in event vector
			eventVec.push_back(floating);
			eventVec.push_back(normalName);
			eventVec.push_back(normal);
			Assert::AreEqual(commandPtr->getEventFromID(eventVec, 1).getID(), floating.getID());
			Assert::AreEqual(commandPtr->getEventFromID(eventVec, 2).getID(), normal.getID());
			eventVec.clear();


			//test partition of id not found in event vector
			eventVec.push_back(floating);
			Assert::AreEqual(commandPtr->getEventFromID(eventVec, 3).getID(), -1);
			eventVec.clear();
		}


		TEST_METHOD(Command_createInvalidEvent_Test)
		{
			//dummy command
			Command* commandPtr = new AddCommand(&eventFacade, emptyEvent);

			Event invalidEvent = commandPtr->createInvalidEvent();
			Assert::AreEqual(invalidEvent.getID(), -1);
		}
	};

/**
* @author A0111089L
*/
}