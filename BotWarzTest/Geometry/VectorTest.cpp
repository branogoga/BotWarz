#include "stdafx.h"
#include "CppUnitTest.h"

#include "Geometry\Point.h"
#include "Geometry\Vector.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace BotWarzTest
{
	TEST_CLASS(VectorTest)
	{
	public:
		
		TEST_METHOD(TestAdditionOfPointAndVector)
		{
            const double dPrecision = 1E-01;
            const double Pi = 3.14159265358979323846;

            {
                Geometry::Point     p(0.0, 0.0);
                Geometry::Vector    v(+1.0, -1.0);
                Geometry::Point     result = p + v;
                Geometry::Point     expected(+1.0, -1.0);
                Assert::AreEqual(expected.x(), result.x());
                Assert::AreEqual(expected.y(), result.y());
            }

            {
                Geometry::Point     p(+1.0, -1.0);
                Geometry::Vector    v(0.0, 0.0);
                Geometry::Point     result = p + v;
                Geometry::Point     expected(+1.0, -1.0);
                Assert::AreEqual(expected.x(), result.x());
                Assert::AreEqual(expected.y(), result.y());
            }

            {
                Geometry::Point     p(+1.0, -1.0);
                Geometry::Vector    v(+1.0, -1.0);
                Geometry::Point     result = p + v;
                Geometry::Point     expected(+2.0, -2.0);
                Assert::AreEqual(expected.x(), result.x());
                Assert::AreEqual(expected.y(), result.y());
            }


        }

        TEST_METHOD(TestSubstractionOfTwoPoints)
        {
            const double dPrecision = 1E-01;
            const double Pi = 3.14159265358979323846;

            {
                Geometry::Point     p1(0.0, 0.0);
                Geometry::Point     p2(+1.0, -1.0);
                Geometry::Vector    result = p1 - p2;
                Geometry::Vector    expected(-1.0, +1.0);
                Assert::AreEqual(expected.x(), result.x());
                Assert::AreEqual(expected.y(), result.y());
            }

            {
                Geometry::Point     p1(+1.0, -1.0);
                Geometry::Point     p2(0.0, 0.0);
                Geometry::Vector    result = p1 - p2;
                Geometry::Vector    expected(+1.0, -1.0);
                Assert::AreEqual(expected.x(), result.x());
                Assert::AreEqual(expected.y(), result.y());
            }
        }

    };
}