#include "stdafx.h"
#include "CppUnitTest.h"

#include "Geometry\Point.h"
#include "Geometry\Vector.h"

#include <cmath>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace BotWarzTest
{
	TEST_CLASS(VectorTest)
	{
	public:
		
		TEST_METHOD(TestAdditionOfPointAndVector)
		{
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

        TEST_METHOD(TestAddVectors)
        {
            {
                Geometry::Vector    v1(0.0, 0.0);
                Geometry::Vector    v2(+1.0, -1.0);
                Geometry::Vector    result = v1 + v2;
                Geometry::Vector    expected(+1.0, -1.0);
                Assert::AreEqual(expected.x(), result.x());
                Assert::AreEqual(expected.y(), result.y());
            }

            {
                Geometry::Vector    v1(5.0, 9.0);
                Geometry::Vector    v2(+1.0, -1.0);
                Geometry::Vector    result = v1 + v2;
                Geometry::Vector    expected(6.0, 8.0);
                Assert::AreEqual(expected.x(), result.x());
                Assert::AreEqual(expected.y(), result.y());
            }

        }

        TEST_METHOD(TestScaleVectors)
        {
            {
                double scale = 1.0;
                Geometry::Vector    v(1.0, -1.0);
                Geometry::Vector    expected(+1.0, -1.0);

                Geometry::Vector    result1 = scale * v;
                Assert::AreEqual(expected.x(), result1.x());
                Assert::AreEqual(expected.y(), result1.y());

                Geometry::Vector    result2 = v * scale;
                Assert::AreEqual(expected.x(), result2.x());
                Assert::AreEqual(expected.y(), result2.y());

                Geometry::Vector    resultDivision = v / scale;
                Geometry::Vector    expectedDivision(+1.0, -1.0);
                Assert::AreEqual(expectedDivision.x(), resultDivision.x());
                Assert::AreEqual(expectedDivision.y(), resultDivision.y());
            }

            {
                double scale = 2.0;
                Geometry::Vector    v(1.0, -1.0);
                Geometry::Vector    expected(+2.0, -2.0);

                Geometry::Vector    result1 = scale * v;
                Assert::AreEqual(expected.x(), result1.x());
                Assert::AreEqual(expected.y(), result1.y());

                Geometry::Vector    result2 = v * scale;
                Assert::AreEqual(expected.x(), result2.x());
                Assert::AreEqual(expected.y(), result2.y());

                Geometry::Vector    resultDivision = v / scale;
                Geometry::Vector    expectedDivision(+0.5, -0.5);
                Assert::AreEqual(expectedDivision.x(), resultDivision.x());
                Assert::AreEqual(expectedDivision.y(), resultDivision.y());
        }

            {
                double scale = 3.0;
                Geometry::Vector    v(6.0, -9.0);
                Geometry::Vector    expected(+18.0, -27.0);

                Geometry::Vector    result1 = scale * v;
                Assert::AreEqual(expected.x(), result1.x());
                Assert::AreEqual(expected.y(), result1.y());

                Geometry::Vector    result2 = v * scale;
                Assert::AreEqual(expected.x(), result2.x());
                Assert::AreEqual(expected.y(), result2.y());

                Geometry::Vector    resultDivision = v / scale;
                Geometry::Vector    expectedDivision(+2.0, -3.0);
                Assert::AreEqual(expectedDivision.x(), resultDivision.x());
                Assert::AreEqual(expectedDivision.y(), resultDivision.y());
            }

            {
                auto function = [this] {
                    Geometry::Vector vector(1.0,0.0);
                    return vector / 0.0;
                };
                Assert::ExpectException<std::invalid_argument>(
                    function
                    );
            }

        }

        TEST_METHOD(TestLength)
        {
            Assert::AreEqual(0.0, length(Geometry::Vector(0.0,0.0)));
            Assert::AreEqual(1.0, length(Geometry::Vector(1.0, 0.0)));
            Assert::AreEqual(1.0, length(Geometry::Vector(0.0, 1.0)));
            Assert::AreEqual(sqrt(2.0), length(Geometry::Vector(1.0, 1.0)));
            Assert::AreEqual(2.0, length(Geometry::Vector(2.0, 0.0)));
            Assert::AreEqual(2.0, length(Geometry::Vector(0.0, 2.0)));
        }

        TEST_METHOD(TestNormalize)
        {
            {
                Geometry::Vector    v(1.0, 0.0);
                Geometry::Vector    expected(1.0, 0.0);

                Geometry::Vector    result = normalize(v);
                Assert::AreEqual(expected.x(), result.x());
                Assert::AreEqual(expected.y(), result.y());
            }

            {
                Geometry::Vector    v(0.0, 1.0);
                Geometry::Vector    expected(0.0, 1.0);

                Geometry::Vector    result = normalize(v);
                Assert::AreEqual(expected.x(), result.x());
                Assert::AreEqual(expected.y(), result.y());
            }

            {
                Geometry::Vector    v(2.0, 0.0);
                Geometry::Vector    expected(1.0, 0.0);

                Geometry::Vector    result = normalize(v);
                Assert::AreEqual(expected.x(), result.x());
                Assert::AreEqual(expected.y(), result.y());
            }

            {
                Geometry::Vector    v(0.0, 2.0);
                Geometry::Vector    expected(0.0, 1.0);

                Geometry::Vector    result = normalize(v);
                Assert::AreEqual(expected.x(), result.x());
                Assert::AreEqual(expected.y(), result.y());
            }

            {
                Geometry::Vector    v(0.5, 0.0);
                Geometry::Vector    expected(1.0, 0.0);

                Geometry::Vector    result = normalize(v);
                Assert::AreEqual(expected.x(), result.x());
                Assert::AreEqual(expected.y(), result.y());
            }

            {
                Geometry::Vector    v(0.0, 0.5);
                Geometry::Vector    expected(0.0, 1.0);

                Geometry::Vector    result = normalize(v);
                Assert::AreEqual(expected.x(), result.x());
                Assert::AreEqual(expected.y(), result.y());
            }

            {
                Geometry::Vector    v(2.0, 0.0);
                Geometry::Vector    expected(1.0, 0.0);

                Geometry::Vector    result = normalize(v);
                Assert::AreEqual(expected.x(), result.x());
                Assert::AreEqual(expected.y(), result.y());
            }

            {
                const double dPrecision = 1E-06;

                Geometry::Vector    v(10.0, 10.0);
                Geometry::Vector    expected(sqrt(2.0)/2.0, sqrt(2.0)/2.0);

                Geometry::Vector    result = normalize(v);
                Assert::AreEqual(expected.x(), result.x(), dPrecision);
                Assert::AreEqual(expected.y(), result.y(), dPrecision);
            }
        }

        TEST_METHOD(TestNormalizeThrowsOnZeroVector)
        {
            auto function = [this] {
                Geometry::Vector vector(0.0, 0.0);
                return normalize(vector);
            };
            Assert::ExpectException<std::invalid_argument>(
                function
                );
        }

        TEST_METHOD(TestDotProduct)
        {
            {
                Geometry::Vector    v1(1.0, 0.0);
                Geometry::Vector    v2(1.0, 0.0);
                double    expected = +1.0;

                Assert::AreEqual(expected, v1*v2);
                Assert::AreEqual(expected, v2*v1);
                Assert::AreEqual(expected, dotProduct(v1, v2));
                Assert::AreEqual(expected, dotProduct(v2, v1));
            }

            {
                Geometry::Vector    v1(1.0, 0.0);
                Geometry::Vector    v2(0.0, 1.0);
                double    expected = +0.0;

                Assert::AreEqual(expected, v1*v2);
                Assert::AreEqual(expected, v2*v1);
                Assert::AreEqual(expected, dotProduct(v1, v2));
                Assert::AreEqual(expected, dotProduct(v2, v1));
            }
        }

        TEST_METHOD(TestIsPerpendicular)
        {
            Assert::IsTrue(
                arePerpendicular(
                    Geometry::Vector(1.0, 0.0), 
                    Geometry::Vector(0.0, 1.0)
                    )
                );

            Assert::IsFalse(
                arePerpendicular(
                Geometry::Vector(1.0, 0.0),
                Geometry::Vector(1.0, 0.0)
                )
                );

            Assert::IsFalse(
                arePerpendicular(
                    Geometry::Vector(1.0, 0.0),
                    Geometry::Vector(1.0, 1.0)
                    )
                );
        }

        TEST_METHOD(TestIsParallel)
        {
            Assert::IsFalse(
                areParallel(
                Geometry::Vector(1.0, 0.0),
                Geometry::Vector(0.0, 1.0)
                )
                );

            Assert::IsTrue(
                areParallel(
                Geometry::Vector(1.0, 0.0),
                Geometry::Vector(1.0, 0.0)
                )
                );

            Assert::IsFalse(
                areParallel(
                Geometry::Vector(1.0, 0.0),
                Geometry::Vector(1.0, 1.0)
                )
                );
        }

        TEST_METHOD(TestIsConvexAngle)
        {
            Assert::IsFalse(
                isConvexAngle(
                Geometry::Vector(1.0, 0.0),
                Geometry::Vector(0.0, 1.0)
                )
                );

            Assert::IsFalse(
                isConvexAngle(
                Geometry::Vector(0.0, 1.0),
                Geometry::Vector(1.0, 0.0)
                )
                );

            Assert::IsTrue(
                isConvexAngle(
                Geometry::Vector(1.0, 0.0),
                Geometry::Vector(1.0, 1.0)
                )
                );

            Assert::IsFalse(
                isConvexAngle(
                Geometry::Vector(1.0, 0.0),
                Geometry::Vector(-1.0, -1.0)
                )
                );
        }

        TEST_METHOD(TestIsConcaveAngle)
        {
            Assert::IsFalse(
                isConcaveAngle(
                Geometry::Vector(1.0, 0.0),
                Geometry::Vector(0.0, 1.0)
                )
                );

            Assert::IsFalse(
                isConcaveAngle(
                Geometry::Vector(0.0, 1.0),
                Geometry::Vector(1.0, 0.0)
                )
                );

            Assert::IsFalse(
                isConcaveAngle(
                Geometry::Vector(1.0, 0.0),
                Geometry::Vector(1.0, 1.0)
                )
                );

            Assert::IsTrue(
                isConcaveAngle(
                Geometry::Vector(1.0, 0.0),
                Geometry::Vector(-1.0, -1.0)
                )
                );
        }

        TEST_METHOD(TestAngleInRadians)
        {
            const double Pi = 3.14159265358979323846;
            const double Precision = 1E-06;

            Assert::AreEqual(
                0.0,
                angleInRadians(
                Geometry::Vector(1.0, 0.0),
                Geometry::Vector(1.0, 0.0)
                )
                );

            Assert::AreEqual(
                Pi / 2,
                angleInRadians(
                    Geometry::Vector(1.0, 0.0),
                    Geometry::Vector(0.0, 1.0)
                )                
            );

            Assert::AreEqual(
                Pi / 2,
                angleInRadians(
                    Geometry::Vector(0.0, 1.0),
                    Geometry::Vector(1.0, 0.0)
                )
                );

            Assert::AreEqual(
                Pi / 4,
                angleInRadians(
                Geometry::Vector(1.0, 0.0),
                Geometry::Vector(1.0, 1.0)
                ), Precision
                );

        }

        TEST_METHOD(TestPerpendicular)
        {
            {
                Geometry::Vector    v(1.0, 0.0);
                Geometry::Vector    expectedClockwise(0.0, -1.0);
                Geometry::Vector    expectedCounterClockwise(0.0, 1.0);

                Geometry::Vector    resultClockwise = clockwisePerpendicular(v);
                Assert::IsTrue(arePerpendicular(v, resultClockwise));
                Assert::AreEqual(expectedClockwise.x(), resultClockwise.x());
                Assert::AreEqual(expectedClockwise.y(), resultClockwise.y());

                Geometry::Vector    resultCounterClockwise = counterClockwisePerpendicular(v);
                Assert::IsTrue(arePerpendicular(v, resultCounterClockwise));
                Assert::AreEqual(expectedCounterClockwise.x(), resultCounterClockwise.x());
                Assert::AreEqual(expectedCounterClockwise.y(), resultCounterClockwise.y());
            }
        }


    };
}