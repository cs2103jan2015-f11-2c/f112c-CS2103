#include "stdafx.h"
#include "CppUnitTest.h"

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
		
		// As a convention, put [name of function] + [_Test]
		// Include & label each test cases used for this function 

		TEST_METHOD(getShowDay_Test)
		{
			//Correct string	
			std::string testCommandShowDay1 = show.getShowDay();
			std::string samepleCommandShowDay1= "show today";
			Assert::AreEqual(samepleCommandShowDay1,testCommandShowDay1);

			//Incorrect string
			std::string testCommandShowDay2 = show.getShowDay();
			std::string samepleCommandShowDay2= "show today ";
			Assert::AreNotEqual(samepleCommandShowDay2,testCommandShowDay2);

		}

	};

	//Unit test for UIHelp class
	TEST_CLASS(UIHelpTest)
	{
	public:




	};
}