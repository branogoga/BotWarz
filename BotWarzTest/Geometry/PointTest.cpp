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

        TEST_METHOD(TestNormalizeAngleInDegrees)
        {
            Assert::AreEqual(0.0, Geometry::normalizeAngleInDegrees(0.0));
            Assert::AreEqual(30.0, Geometry::normalizeAngleInDegrees(30.0));
            Assert::AreEqual(-30.0, Geometry::normalizeAngleInDegrees(-30.0));
            Assert::AreEqual(120.0, Geometry::normalizeAngleInDegrees(120.0));
            Assert::AreEqual(-120.0, Geometry::normalizeAngleInDegrees(-120.0));
            Assert::AreEqual(180.0, Geometry::normalizeAngleInDegrees(180.0));
            Assert::AreEqual(180.0, Geometry::normalizeAngleInDegrees(-180.0));
            Assert::AreEqual(-150.0, Geometry::normalizeAngleInDegrees(210.0));
            Assert::AreEqual(+150.0, Geometry::normalizeAngleInDegrees(-210.0));
            Assert::AreEqual(1.0, Geometry::normalizeAngleInDegrees(361.0));
            Assert::AreEqual(-1.0, Geometry::normalizeAngleInDegrees(-361.0));
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

        TEST_METHOD(TestAreLinesParallelOnParallelLines)
        {
            Geometry::Point startLine1(100.0, 100.0);
            Geometry::Point endLine1(200.0, 100.0);

            Geometry::Point startLine2(100.0, 200.0);
            Geometry::Point endLine2(200.0, 200.0);
            Assert::IsTrue(Geometry::areLinesParallel(startLine1, endLine1, startLine2, endLine2));
        }

        TEST_METHOD(TestAreLinesParallelPerpendicularLines)
        {
            Geometry::Point startLine1(100.0, 100.0);
            Geometry::Point endLine1(200.0, 100.0);

            Geometry::Point startLine3(150.0, 50.0);
            Geometry::Point endLine3(150.0, 150.0);
            Assert::IsFalse(Geometry::areLinesParallel(startLine1, endLine1, startLine3, endLine3));
        }

        TEST_METHOD(TestLineIntersetionParallelLines)
        {
            Geometry::Point startLine1(100.0, 100.0);
            Geometry::Point endLine1(200.0, 100.0);

            // Parallel
            Geometry::Point startLine2(100.0, 200.0);
            Geometry::Point endLine2(200.0, 200.0);

            Assert::IsFalse(Geometry::doLinesIntersect(startLine1, endLine1, startLine2, endLine2));
        }

        TEST_METHOD(TestLineIntersetionParallelOverlapingLines)
        {
            Geometry::Point startLine1(100.0, 100.0);
            Geometry::Point endLine1(200.0, 100.0);

            // Parallel
            Geometry::Point startLine2(50.0, 100.0);
            Geometry::Point endLine2(150.0, 100.0);

            Assert::IsTrue(Geometry::doLinesIntersect(startLine1, endLine1, startLine2, endLine2));
        }

        TEST_METHOD(TestLineIntersetionCrossingLines)
        {
            Geometry::Point startLine1(100.0, 100.0);
            Geometry::Point endLine1(200.0, 100.0);

            // Crossing each other
            Geometry::Point startLine3(150.0, 50.0);
            Geometry::Point endLine3(150.0, 150.0);

            Assert::IsTrue(Geometry::doLinesIntersect(startLine1, endLine1, startLine3, endLine3));
        }

        TEST_METHOD(TestLineIntersetionParallelLinesWithoutIntersection)
        {
            Geometry::Point startLine1(100.0, 100.0);
            Geometry::Point endLine1(200.0, 100.0);

            // Not parallel, but do not cross each other
            Geometry::Point startLine4(50.0, 50.0);
            Geometry::Point endLine4(50.0, 150.0);

            Assert::IsFalse(Geometry::doLinesIntersect(startLine1, endLine1, startLine4, endLine4));
        }

        TEST_METHOD(TestLineAngle)
        {
            {
                Geometry::Point startLine1(100.0, 100.0);
                Geometry::Point endLine1(200.0, 100.0);

                Geometry::Point startLine2(50.0, 50.0);
                Geometry::Point endLine2(50.0, 150.0);

                Assert::AreEqual(
                    90.0,
                    Geometry::lineAngleInDegrees(startLine1, endLine1, startLine2, endLine2)
                    );
            }

            {
            Geometry::Point startLine1(100.0, 100.0);
            Geometry::Point endLine1(200.0, 100.0);

            Geometry::Point startLine2(50.0, 50.0);
            Geometry::Point endLine2(150.0, 150.0);

            Assert::AreEqual(
                45.0,
                Geometry::lineAngleInDegrees(startLine1, endLine1, startLine2, endLine2),
                1E-02
                );

            Assert::AreEqual(
                180.0 - 45.0,
                Geometry::lineAngleInDegrees(startLine2, endLine2, startLine1, endLine1),
                1E-02
                );
            }
        }

        TEST_METHOD(TestPointToLineDistance)
        {
            Geometry::Point line1(100.0, 100.0);
            Geometry::Point line2(200.0, 100.0);

            Assert::AreEqual(
                50.0,
                Geometry::pointToLineDistance(
                Geometry::Point(50.0,100.0), line1, line2
                )
                );

            Assert::AreEqual(
                50.0,
                Geometry::pointToLineDistance(
                Geometry::Point(250.0, 100.0), line1, line2
                )
                );

            Assert::AreEqual(
                50.0,
                Geometry::pointToLineDistance(
                Geometry::Point(150.0, 150.0), line1, line2
                )
                );

            Assert::AreEqual(
                0.0,
                Geometry::pointToLineDistance(
                Geometry::Point(150.0, 100.0), line1, line2
                )
                );
        }
    };
}