#include "stdafx.h"
#include "CppUnitTest.h"

#include "Geometry\Line.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace BotWarzTest
{
	TEST_CLASS(LineTest)
	{
	public:
		
        TEST_METHOD(TestAreLinesParallelOnParallelLines)
        {
            Geometry::Line line1(
                Geometry::Point(100.0, 100.0),
                Geometry::Point(200.0, 100.0)
                );

            Geometry::Line line2(
                Geometry::Point(100.0, 200.0),
                Geometry::Point(200.0, 200.0)
            );

            Assert::IsTrue(Geometry::areLinesParallel(line1, line2));
        }

        TEST_METHOD(TestAreLinesParallelPerpendicularLines)
        {
            Geometry::Line line1(
                Geometry::Point(100.0, 100.0),
                Geometry::Point(200.0, 100.0)
                );

            Geometry::Line line2(
                Geometry::Point(150.0, 50.0),
                Geometry::Point(150.0, 150.0)
                );

            Assert::IsFalse(Geometry::areLinesParallel(line1, line2));
        }

        TEST_METHOD(TestLineIntersetionParallelLines)
        {
            Geometry::Line line1(
                Geometry::Point(100.0, 100.0),
                Geometry::Point(200.0, 100.0)
                );

            Geometry::Line line2(
                Geometry::Point(100.0, 200.0),
                Geometry::Point(200.0, 200.0)
                );

            Assert::IsTrue(Geometry::areLinesParallel(line1, line2));
        }

        TEST_METHOD(TestLineIntersetionParallelOverlapingLines)
        {
            Geometry::Line line1(
                Geometry::Point(100.0, 100.0),
                Geometry::Point(200.0, 100.0)
                );

            Geometry::Line line2(
                Geometry::Point(50.0, 100.0),
                Geometry::Point(150.0, 100.0)
                );

            Assert::IsTrue(Geometry::areLinesParallel(line1, line2));
        }

        TEST_METHOD(TestLineIntersetionCrossingLines)
        {
            Geometry::Line line1(
                Geometry::Point(100.0, 100.0),
                Geometry::Point(200.0, 100.0)
                );

            Geometry::Line line2(
                Geometry::Point(150.0, 50.0),
                Geometry::Point(150.0, 150.0)
                );

            Assert::IsFalse(Geometry::areLinesParallel(line1, line2));
        }

        TEST_METHOD(TestLineIntersetionParallelLinesWithoutIntersection)
        {
            Geometry::Line line1(
                Geometry::Point(100.0, 100.0),
                Geometry::Point(200.0, 100.0)
                );

            // Not parallel, but do not cross each other
            Geometry::Line line2(
                Geometry::Point(50.0, 50.0),
                Geometry::Point(50.0, 150.0)
                );

            Assert::IsFalse(Geometry::areLinesParallel(line1, line2));
        }

        TEST_METHOD(TestLineAngle)
        {
            {
                Geometry::Line line1(
                    Geometry::Point(100.0, 100.0),
                    Geometry::Point(200.0, 100.0)
                );

                Geometry::Line line2(
                    Geometry::Point(50.0, 50.0),
                    Geometry::Point(50.0, 150.0)
                );

                Assert::AreEqual(
                    90.0,
                    Geometry::angleInDegrees(line1, line2)
                    );
            }

            {
                Geometry::Line line1(
                    Geometry::Point(100.0, 100.0),
                    Geometry::Point(200.0, 100.0)
                    );


                Geometry::Line line2(
                    Geometry::Point(50.0, 50.0),
                    Geometry::Point(150.0, 150.0)
                    );

                Assert::AreEqual(
                    45.0,
                    Geometry::angleInDegrees(line1, line2),
                    1E-02
                    );

                Assert::AreEqual(
                    /*180.0 - 45.0*/ 45.0,
                    Geometry::angleInDegrees(line2, line1),
                    1E-02
                    );
            }
        }

        TEST_METHOD(TestPointToLineDistance)
        {
            Geometry::Line line(
                Geometry::Point(100.0, 100.0),
                Geometry::Point(200.0, 100.0)
                );

            Assert::AreEqual(
                50.0,
                Geometry::pointToLineDistance(
                Geometry::Point(50.0, 100.0), line
                )
                );

            Assert::AreEqual(
                50.0,
                Geometry::pointToLineDistance(
                Geometry::Point(250.0, 100.0), line
                )
                );

            Assert::AreEqual(
                50.0,
                Geometry::pointToLineDistance(
                Geometry::Point(150.0, 150.0), line
                )
                );

            Assert::AreEqual(
                0.0,
                Geometry::pointToLineDistance(
                Geometry::Point(150.0, 100.0), line
                )
                );
        }
    };

}