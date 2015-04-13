//@author A0111089L
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

		TEST_METHOD(Command_getEventVector_Test)
		{
			//dummy command
			vector<tm> dummyTM;
			Command* commandPtr = new AddCommand(&eventFacade, emptyEvent, dummyTM);


			//test partition of unexecuted command
			int size = commandPtr->getEventVector().size();
			Assert::AreEqual(size, 0);
			delete commandPtr;
			commandPtr = NULL;
		}


		TEST_METHOD(Command_getIsExecuted_Test)
		{
			//dummy command
			vector<tm> dummyTM;
			Command* commandPtr = new AddCommand(&eventFacade, emptyEvent, dummyTM);


			//test partition of unexecuted command
			Assert::AreEqual(commandPtr->getIsExecuted(), false);
			delete commandPtr;
			commandPtr = NULL;
		}


		TEST_METHOD(Command_getIsUndoable_Test)
		{
			//dummy command
			vector<tm> dummyTM;
			Command* commandPtr = new AddCommand(&eventFacade, emptyEvent, dummyTM);


			//test partition of undoable command
			Assert::AreEqual(commandPtr->getIsUndoable(), true);
			delete commandPtr;
			commandPtr = NULL;


			//test partition of non undoable command
			commandPtr = new ShowCommand(&eventFacade, emptyEvent);
			Assert::AreEqual(commandPtr->getIsUndoable(), false);
			delete commandPtr;
			commandPtr = NULL;
		}


		TEST_METHOD(Command_getEventFromID_Test)
		{
			//dummy command
			vector<tm> dummyTM;
			Command* commandPtr = new AddCommand(&eventFacade, emptyEvent, dummyTM);

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

			delete commandPtr;
			commandPtr = NULL;
		}


		TEST_METHOD(Command_createInvalidEvent_Test)
		{
			//dummy command
			vector<tm> dummyTM;
			Command* commandPtr = new AddCommand(&eventFacade, emptyEvent, dummyTM);

			Event invalidEvent = commandPtr->createInvalidEvent();
			Assert::AreEqual(invalidEvent.getID(), -1);

			delete commandPtr;
			commandPtr = NULL;
		}
	};
}