#include "stdafx.h"
#include "CppUnitTest.h"

#include "Geometry\Point.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace BotWarzTest
{
	TEST_CLASS(PointTest)
	{
	public:
		
		TEST_METHOD(TestConvertAngleFromRadiansToDegrees)
		{
            const double dPrecision = 1E-01;
            const double Pi = 3.14159265358979323846;

            Assert::AreEqual( 0.0, Geometry::convertAngleFromRadiansToDegrees(0.0), dPrecision);
            Assert::AreEqual( +180.0, Geometry::convertAngleFromRadiansToDegrees(Pi), dPrecision);
            Assert::AreEqual( -180.0, Geometry::convertAngleFromRadiansToDegrees(-Pi), dPrecision);
        }

        TEST_METHOD(TestConvertAngleFromDegreesToRadians)
        {
            const double dPrecision = 1E-01;
            const double Pi = 3.14159265358979323846;

            Assert::AreEqual( 0.0, Geometry::convertAngleFromDegreesToRadians(0.0), dPrecision);
            Assert::AreEqual( Pi, Geometry::convertAngleFromDegreesToRadians(180), dPrecision);
            Assert::AreEqual( -Pi, Geometry::convertAngleFromDegreesToRadians(-180), dPrecision);
        }

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

        TEST_METHOD(TestLineIntersetion)
        {
            Geometry::Point startLine1(100.0, 100.0);
            Geometry::Point endLine1(200.0, 100.0);

            Geometry::Point startLine2(100.0, 200.0);
            Geometry::Point endLine2(200.0, 200.0);

            Geometry::Point startLine3(50.0, 50.0);
            Geometry::Point endLine3(150.0, 150.0);

            Assert::IsFalse(Geometry::doLinesIntersect(startLine1, endLine1, startLine2, endLine2));
            Assert::IsTrue(Geometry::doLinesIntersect(startLine1, endLine1, startLine3, endLine3));
        }
    };
}