#include "stdafx.h"
#include "CppUnitTest.h"

#include "BotWarz/Bot.h"
#include "BotWarz/Strategy/Strategy.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace BotWarzTest
{
    TEST_CLASS(StrategyTest)
    {
    public:

        TEST_METHOD(TestFindClosestBot)
        {
            std::vector<std::shared_ptr<BotWarz::Bot>>   vBots;
            vBots.push_back(std::make_shared<BotWarz::Bot>(1, Geometry::Point(100.0, 100.0)));
            vBots.push_back(std::make_shared<BotWarz::Bot>(2, Geometry::Point(200.0, 100.0)));
            vBots.push_back(std::make_shared<BotWarz::Bot>(3, Geometry::Point(200.0, 200.0)));
            vBots.push_back(std::make_shared<BotWarz::Bot>(4, Geometry::Point(100.0, 200.0)));

            Assert::AreEqual(
                (unsigned)0,
                (unsigned)BotWarz::Strategy::findClosestBot(vBots, Geometry::Point(0.0, 0.0))
                );

            Assert::AreEqual(
                (unsigned)1,
                (unsigned)BotWarz::Strategy::findClosestBot(vBots, Geometry::Point(175.0, 100.0))
                );

            Assert::AreEqual(
                (unsigned)1,
                (unsigned)BotWarz::Strategy::findClosestBot(vBots, Geometry::Point(168.0, 132.0))
                );

            Assert::AreEqual(
                (unsigned)2,
                (unsigned)BotWarz::Strategy::findClosestBot(vBots, Geometry::Point(210.0, 210.0))
                );

            Assert::AreEqual(
                (unsigned)3,
                (unsigned)BotWarz::Strategy::findClosestBot(vBots, Geometry::Point(132.0, 184.0))
                );

        }

        TEST_METHOD(TestCalculateMaxAttackAngle)
        {
            Assert::AreEqual(
                180.0,
                BotWarz::Strategy::calculateMaxAttackAngleInDegrees(10.0, 0.0)
                );

            Assert::AreEqual(
                45.0,
                BotWarz::Strategy::calculateMaxAttackAngleInDegrees(10.0, 10.0)
                );

            Assert::AreEqual(
                26.5,
                BotWarz::Strategy::calculateMaxAttackAngleInDegrees(10.0, 20.0),
                1E-01
                );
        }

        TEST_METHOD(TestIsCollisionExpectedParallelBots)
        {
                // Two parallel bots with different position and speed won`t colide
                BotWarz::Bot bot1( 1,
                    Geometry::Point(100.0, 100.0),
                    0.0,
                    10.0
                );

                BotWarz::Bot bot2( 2,
                    Geometry::Point(150.0, 100.0),
                    0.0,
                    10.0
                    );

                Assert::IsFalse(
                    BotWarz::Strategy::isCollisionExpected(bot1, bot2, 1000.0)
                    );
        }

        TEST_METHOD(TestIsCollisionExpectedParallelBotsFasterBehindSlower)
        {
            // Two parallel bots with different position and different speed can colide
            BotWarz::Bot bot1( 1,
                Geometry::Point(100.0, 100.0),
                0.0,
                1.0
                );

            BotWarz::Bot bot2( 2,
                Geometry::Point(80.0, 100.0),
                0.0,
                1E+06
                );

            Assert::IsTrue(
                BotWarz::Strategy::isCollisionExpected(bot1, bot2, 1000.0)
                );
        }

        TEST_METHOD(TestIsCollisionExpectedCrossingLines)
        {
            // Two parallel bots with different position and different speed can colide
            BotWarz::Bot bot1(1,
                Geometry::Point(100.0, 100.0),
                0.0,
                100.0
                );

            BotWarz::Bot bot2(2,
                Geometry::Point(150.0, 50.0),
                90.0,
                100
                );

            Assert::IsTrue(
                BotWarz::Strategy::isCollisionExpected(bot1, bot2, 1000.0)
                );
        }


        TEST_METHOD(TestIsCollisionExpectedMissingLines)
        {
            // Two parallel bots with different position and different speed can colide
            BotWarz::Bot bot1(1,
                Geometry::Point(100.0, 100.0),
                0.0,
                100.0
                );

            BotWarz::Bot bot2(2,
                Geometry::Point(50.0, 50.0),
                90.0,
                100
                );

            Assert::IsFalse(
                BotWarz::Strategy::isCollisionExpected(bot1, bot2, 1000.0)
                );
        }

        TEST_METHOD(TestCurrentPositionChasingPolicy)
        {
            auto pBot = std::make_shared<BotWarz::Bot>( 1,
                Geometry::Point(100.0, 100.0),
                90.0,
                100.0
                );

            BotWarz::Strategy::CurrentPositionChasingPolicy chasingPolicy(pBot);

            auto ptExpected = Geometry::Point(100.0, 100.0);
            auto ptCalculated = chasingPolicy.getDestinationPoint();
            Assert::AreEqual(
                ptExpected.x(),
                ptCalculated.x()
                );

            Assert::AreEqual(
                ptExpected.y(),
                ptCalculated.y()
                );
        }

        TEST_METHOD(TestFuturePositionChasingPolicy)
        {
            auto pBot = std::make_shared<BotWarz::Bot>(1,
                Geometry::Point(100.0, 100.0),
                90.0,
                100
                );

            const double dTimeDeltaInMilliseconds = 1000.0;
            BotWarz::Strategy::FuturePositionChasingPolicy chasingPolicy(
                pBot, dTimeDeltaInMilliseconds
                );

            auto ptExpected = Geometry::Point(100.0, 200.0);
            auto ptCalculated = chasingPolicy.getDestinationPoint();
            Assert::AreEqual(
                ptExpected.x(),
                ptCalculated.x()
                );

            Assert::AreEqual(
                ptExpected.y(),
                ptCalculated.y()
                );
        }

        TEST_METHOD(TestFuturePositionChasingPolicyZeroSpeed)
        {
            auto pBot = std::make_shared<BotWarz::Bot>( 1,
                Geometry::Point(100.0, 100.0),
                90.0,
                0.0
                );

            const double dTimeDeltaInMilliseconds = 1000.0;
            BotWarz::Strategy::FuturePositionChasingPolicy chasingPolicy(
                pBot, dTimeDeltaInMilliseconds
                );

            auto ptExpected = Geometry::Point(100.0, 100.0);
            auto ptCalculated = chasingPolicy.getDestinationPoint();
            Assert::AreEqual(
                ptExpected.x(),
                ptCalculated.x()
                );

            Assert::AreEqual(
                ptExpected.y(),
                ptCalculated.y()
                );
        }

    };
}