#include "stdafx.h"
#include "CppUnitTest.h"

#include "Geometry\Angle.h"

#define _USE_MATH_DEFINES
#include <math.h>
#undef _USE_MATH_DEFINES

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace BotWarzTest
{
    TEST_CLASS(AngleTest)
    {
    public:

        TEST_METHOD(TestConvertAngleFromRadiansToDegrees)
        {
            const double dPrecision = 1E-01;

            Assert::AreEqual(0.0, Geometry::convertAngleFromRadiansToDegrees(0.0), dPrecision);
            Assert::AreEqual(+180.0, Geometry::convertAngleFromRadiansToDegrees(M_PI), dPrecision);
            Assert::AreEqual(-180.0, Geometry::convertAngleFromRadiansToDegrees(-M_PI), dPrecision);
        }

        TEST_METHOD(TestConvertAngleFromDegreesToRadians)
        {
            const double dPrecision = 1E-01;

            Assert::AreEqual(0.0, Geometry::convertAngleFromDegreesToRadians(0.0), dPrecision);
            Assert::AreEqual(M_PI, Geometry::convertAngleFromDegreesToRadians(180), dPrecision);
            Assert::AreEqual(-M_PI, Geometry::convertAngleFromDegreesToRadians(-180), dPrecision);
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
    };

}