#include "stdafx.h"
#include "CppUnitTest.h"

#include "Testable.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace BotWarzTest
{		
	TEST_CLASS(Test)
	{
	public:
		
		TEST_METHOD(TestMethod)
		{
            Testable testable;
            Assert::AreEqual<unsigned>( 4, testable.add(2,2) );
		}

	};
}