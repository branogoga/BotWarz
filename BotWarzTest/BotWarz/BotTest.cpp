#include "stdafx.h"
#include "CppUnitTest.h"

#include "BotWarz\Bot.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace BotWarzTest
{
	TEST_CLASS(BotTest)
	{
	public:
		
		TEST_METHOD(TestFuturePosition)
		{
            {
                BotWarz::Bot bot(1);
                bot.setPosition(Geometry::Point(100.0, 100.0));
                bot.setAngleInDegrees(0.0);
                bot.setSpeed(10);

                Geometry::Point positionInSecond = bot.getFuturePosition(1000.0);

                const double dPrecision = 1E-01;
                Assert::AreEqual(110.0, positionInSecond.x(), dPrecision);
                Assert::AreEqual(100.0, positionInSecond.y(), dPrecision);
            }

            {
                BotWarz::Bot bot(1);
                bot.setPosition(Geometry::Point(100.0, 100.0));
                bot.setAngleInDegrees(0.0);
                bot.setSpeed(10);

                Geometry::Point positionInSecond = bot.getFuturePosition(250.0);

                const double dPrecision = 1E-01;
                Assert::AreEqual(102.5, positionInSecond.x(), dPrecision);
                Assert::AreEqual(100.0, positionInSecond.y(), dPrecision);
            }

            {
                BotWarz::Bot bot(1);
                bot.setPosition(Geometry::Point(100.0, 100.0));
                bot.setAngleInDegrees(0.0);
                bot.setSpeed(20);

                Geometry::Point positionInSecond = bot.getFuturePosition(1000.0);

                const double dPrecision = 1E-01;
                Assert::AreEqual(120.0, positionInSecond.x(), dPrecision);
                Assert::AreEqual(100.0, positionInSecond.y(), dPrecision);
            }

            {
                BotWarz::Bot bot(1);
                bot.setPosition(Geometry::Point(100.0, 100.0));
                bot.setAngleInDegrees(90.0);
                bot.setSpeed(10);

                Geometry::Point positionInSecond = bot.getFuturePosition(1000.0);

                const double dPrecision = 1E-01;
                Assert::AreEqual(100.0, positionInSecond.x(), dPrecision);
                Assert::AreEqual(110.0, positionInSecond.y(), dPrecision);
            }

            {
                BotWarz::Bot bot(1);
                bot.setPosition(Geometry::Point(100.0, 100.0));
                bot.setAngleInDegrees(-45.0);
                bot.setSpeed(10);

                Geometry::Point positionInSecond = bot.getFuturePosition(1000.0);

                const double dPrecision = 1E-01;
                Assert::AreEqual(107.0, positionInSecond.x(), dPrecision);
                Assert::AreEqual(93.0, positionInSecond.y(), dPrecision);
            }
        }

        TEST_METHOD(TestSetAngle)
        {
            BotWarz::Bot    bot(1);

            bot.setAngleInDegrees(0.0);
            Assert::AreEqual(0.0, bot.getAngleInDegrees());

            bot.setAngleInDegrees(+15.0);
            Assert::AreEqual(+15.0, bot.getAngleInDegrees());

            bot.setAngleInDegrees(-15.0);
            Assert::AreEqual(-15.0, bot.getAngleInDegrees());

            bot.setAngleInDegrees(+30.0);
            Assert::AreEqual(+30.0, bot.getAngleInDegrees());

            bot.setAngleInDegrees(-30.0);
            Assert::AreEqual(-30.0, bot.getAngleInDegrees());

            bot.setAngleInDegrees(+90.0);
            Assert::AreEqual(+90.0, bot.getAngleInDegrees());

            bot.setAngleInDegrees(-90.0);
            Assert::AreEqual(-90.0, bot.getAngleInDegrees());

            bot.setAngleInDegrees(+160.0);
            Assert::AreEqual(+160.0, bot.getAngleInDegrees());

            bot.setAngleInDegrees(-160.0);
            Assert::AreEqual(-160.0, bot.getAngleInDegrees());

            bot.setAngleInDegrees(+180.0);
            Assert::AreEqual(+180.0, bot.getAngleInDegrees());

            bot.setAngleInDegrees(-180.0);
            Assert::AreEqual(+180.0, bot.getAngleInDegrees());

            bot.setAngleInDegrees(+181.0);
            Assert::AreEqual(-179.0, bot.getAngleInDegrees());

            bot.setAngleInDegrees(-181.0);
            Assert::AreEqual(+179.0, bot.getAngleInDegrees());
        }

        TEST_METHOD(TestAdvanceBot)
        {
            {
                BotWarz::Bot bot(1);
                bot.setPosition(Geometry::Point(100.0, 100.0));
                bot.setAngleInDegrees(0.0);
                bot.setSpeed(10);

                bot.advance(1000.0);

                const double dPrecision = 1E-01;
                Assert::AreEqual(110.0, bot.getPositionX(), dPrecision);
                Assert::AreEqual(100.0, bot.getPositionY(), dPrecision);
            }
        }

    };
}