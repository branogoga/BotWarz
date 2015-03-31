#include "stdafx.h"
#include "CppUnitTest.h"

#include "Geometry\Point.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace BotWarzTest
{
    TEST_CLASS(PointTest)
    {
    public:
        TEST_METHOD(TestAngleOfLineWithHorizontalAxis)
        {
            Geometry::Point point1(100.0, 100.0);
            Geometry::Point point2(200.0, 100.0);

            const double dPrecision = 1E-01;
            const double dExpectedAngle = 0.0;
            double dAngle = Geometry::angleInDegrees(point1, point2);
            Assert::AreEqual(dExpectedAngle, dAngle, dPrecision);
        }

        TEST_METHOD(TestAngleOfLineWithVerticalAxis)
        {
            Geometry::Point point1(100.0, 100.0);
            Geometry::Point point2(100.0, 200.0);

            const double dPrecision = 1E-01;
            const double dExpectedAngle = +90.0;
            double dAngle = Geometry::angleInDegrees(point1, point2);
            Assert::AreEqual(dExpectedAngle, dAngle, dPrecision);
        }
    };

}