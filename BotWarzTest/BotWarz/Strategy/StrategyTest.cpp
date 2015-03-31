#include "stdafx.h"
#include "CppUnitTest.h"

#include "BotWarz/Bot.h"
#include "BotWarz/SpeedLevel.h"
#include "BotWarz/Strategy/Strategy.h"
#include "BotWarz/World.h"

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

        TEST_METHOD(TestFindClosestBotPolicy)
        {
            std::vector<std::shared_ptr<BotWarz::Bot>>   vBots;
            vBots.push_back(std::make_shared<BotWarz::Bot>(1, Geometry::Point(100.0, 100.0)));
            vBots.push_back(std::make_shared<BotWarz::Bot>(2, Geometry::Point(200.0, 100.0)));
            vBots.push_back(std::make_shared<BotWarz::Bot>(3, Geometry::Point(200.0, 200.0)));
            vBots.push_back(std::make_shared<BotWarz::Bot>(4, Geometry::Point(100.0, 200.0)));

            BotWarz::Strategy::FindClosestBotPolicy botFinder;

            auto myBot = std::make_shared<BotWarz::Bot>(
                0, 
                Geometry::Point(0.0,0.0),
                0.0,
                10.0
                );

            myBot->setPosition(Geometry::Point(0.0, 0.0));
            Assert::AreEqual(
                (unsigned)0,
                (unsigned)botFinder.getBotIndex(myBot,vBots)
                );

            myBot->setPosition(Geometry::Point(175.0, 100.0));
            Assert::AreEqual(
                (unsigned)1,
                (unsigned)botFinder.getBotIndex(myBot, vBots)
                );

            myBot->setPosition(Geometry::Point(168.0, 132.0));
            Assert::AreEqual(
                (unsigned)1,
                (unsigned)botFinder.getBotIndex(myBot, vBots)
                );

            myBot->setPosition(Geometry::Point(210.0, 210.0));
            Assert::AreEqual(
                (unsigned)2,
                (unsigned)botFinder.getBotIndex(myBot, vBots)
                );

            myBot->setPosition(Geometry::Point(132.0, 184.0));
            Assert::AreEqual(
                (unsigned)3,
                (unsigned)botFinder.getBotIndex(myBot, vBots)
                );
        }

        TEST_METHOD(TestCalculateMaxAttackAngle)
        {
            Assert::AreEqual(
                180.0,
                BotWarz::Strategy::calculateMaxAttackAngleInDegrees(10.0, 0.0)
                );

            Assert::AreEqual(
                /* (45.0 / 2) */ 22.5,
                BotWarz::Strategy::calculateMaxAttackAngleInDegrees(10.0, 10.0)
                );

            Assert::AreEqual(
                /* (26.5 / 2) */ 13.25,
                BotWarz::Strategy::calculateMaxAttackAngleInDegrees(10.0, 20.0),
                1E-01
                );

            Assert::AreEqual(
                /* (26.5 / 2) */ 13.25,
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

            BotWarz::Strategy::CurrentPositionChasingPolicy chasingPolicy;

            auto ptExpected = Geometry::Point(100.0, 100.0);
            auto ptCalculated = chasingPolicy.getDestinationPoint(pBot);
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
                dTimeDeltaInMilliseconds
                );

            auto ptExpected = Geometry::Point(100.0, 200.0);
            auto ptCalculated = chasingPolicy.getDestinationPoint(pBot);
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
                dTimeDeltaInMilliseconds
                );

            auto ptExpected = Geometry::Point(100.0, 100.0);
            auto ptCalculated = chasingPolicy.getDestinationPoint(pBot);
            Assert::AreEqual(
                ptExpected.x(),
                ptCalculated.x()
                );

            Assert::AreEqual(
                ptExpected.y(),
                ptCalculated.y()
                );
        }

        TEST_METHOD(TestNumberOfStepsToReachAPoint_MoveForward)
        {
            auto myBot = std::make_shared<BotWarz::Bot>(
                1,
                Geometry::Point(100.0, 100.0),
                0.0,
                10.0
                );

            const double dTimeDelta = 1000.0;

            // Steer 0, move (100.0,100.0) -> (110.0,110.0)
            // Steer 0, move (110.0,100.0) -> (120.0,110.0)
            Assert::AreEqual(
                (unsigned)2,
                (unsigned)BotWarz::Strategy::numberOfStepsToReachPoint(myBot, Geometry::Point(120.0, 100.0), createSpeedLevels(), dTimeDelta)
                );

            // Accelerate (10 -> 30), move (100.0,100.0) -> (110.0,110.0)
            // Steer 0, move (110.0,100.0) -> (140.0,110.0)
            Assert::AreEqual(
                (unsigned)2,
                (unsigned)BotWarz::Strategy::numberOfStepsToReachPoint(myBot, Geometry::Point(140.0, 100.0), createSpeedLevels(), dTimeDelta)
                );

        }

        TEST_METHOD(TestNumberOfStepsToReachAPoint_RotateAndMoveForward)
        {
            const double dTimeDelta = 1000.0;

            {
                auto myBot = std::make_shared<BotWarz::Bot>(
                1,
                Geometry::Point(100.0, 100.0),
                -30.0,
                10.0
                );

                Assert::AreEqual(
                    (unsigned)2,
                    (unsigned)BotWarz::Strategy::numberOfStepsToReachPoint(myBot, Geometry::Point(110.0, 100.0), createSpeedLevels(), dTimeDelta)
                    );
            }

            {
                auto myBot = std::make_shared<BotWarz::Bot>(
                    1,
                    Geometry::Point(100.0, 100.0),
                    -60.0,
                    10.0
                    );

                Assert::AreEqual(
                        (unsigned)3,
                        (unsigned)BotWarz::Strategy::numberOfStepsToReachPoint(myBot, Geometry::Point(110.0, 100.0), createSpeedLevels(), dTimeDelta)
                        );
            }

            {
                auto myBot = std::make_shared<BotWarz::Bot>(
                    1,
                    Geometry::Point(100.0, 100.0),
                    -20.0,
                    30.0
                    );

                Assert::AreEqual(
                    (unsigned)3,
                    (unsigned)BotWarz::Strategy::numberOfStepsToReachPoint(myBot, Geometry::Point(110.0, 100.0), createSpeedLevels(), dTimeDelta)
                    );
            }
        }

        TEST_METHOD(TestFindMostReachableBotPolicy)
        {
            std::vector<std::shared_ptr<BotWarz::Bot>>   vBots;
            vBots.push_back(std::make_shared<BotWarz::Bot>(1, Geometry::Point(100.0, 100.0)));
            vBots.push_back(std::make_shared<BotWarz::Bot>(2, Geometry::Point(200.0, 100.0)));
            vBots.push_back(std::make_shared<BotWarz::Bot>(3, Geometry::Point(200.0, 200.0)));
            vBots.push_back(std::make_shared<BotWarz::Bot>(4, Geometry::Point(100.0, 200.0)));

            BotWarz::Strategy::FindMostReachableBotPolicy botFinder(
                createSpeedLevels()
                );

            auto myBot = std::make_shared<BotWarz::Bot>(
                0,
                Geometry::Point(0.0, 0.0),
                0.0,
                10.0
                );

            myBot->setPosition(Geometry::Point(150.0, 100.0));
            myBot->setAngleInDegrees(180.0);
            Assert::AreEqual(
                (unsigned)0,
                (unsigned)botFinder.getBotIndex(myBot, vBots)
                );

            myBot->setPosition(Geometry::Point(150.0, 100.0));
            myBot->setAngleInDegrees(0.0);
            Assert::AreEqual(
                (unsigned)1,
                (unsigned)botFinder.getBotIndex(myBot, vBots)
                );
        }

        TEST_METHOD(TestIsBotAlignedWithAttackZone_EnemyBotIsTurnedOutwards1)
        {
            auto myBot = std::make_shared<BotWarz::Bot>(
                0,
                Geometry::Point(100.0, 100.0),
                0.0,
                10.0
            );

            auto enemyBot = std::make_shared<BotWarz::Bot>(
                0,
                Geometry::Point(110.0, 100.0),
                +90.0,
                10.0
                );

            Assert::IsFalse(
                BotWarz::Strategy::isBotAlignedWithAttackZone(myBot, enemyBot)
                );
        }

        TEST_METHOD(TestIsBotAlignedWithAttackZone_EnemyBotIsTurnedOutwards2)
        {
            auto myBot = std::make_shared<BotWarz::Bot>(
                0,
                Geometry::Point(100.0, 100.0),
                0.0,
                10.0
                );

            auto enemyBot = std::make_shared<BotWarz::Bot>(
                0,
                Geometry::Point(110.0, 100.0),
                -90.0,
                10.0
                );

            Assert::IsFalse(
                BotWarz::Strategy::isBotAlignedWithAttackZone(myBot, enemyBot)
                );
        }

        TEST_METHOD(TestIsBotAlignedWithAttackZone_EnemyBotIsTurnedInwardsButIsFar)
        {
            auto myBot = std::make_shared<BotWarz::Bot>(
                0,
                Geometry::Point(100.0, 100.0),
                0.0,
                10.0
                );

            auto enemyBot = std::make_shared<BotWarz::Bot>(
                0,
                Geometry::Point(200.0, 100.0),
                -180.0,
                10.0
                );

            Assert::IsFalse(
                BotWarz::Strategy::isBotAlignedWithAttackZone(myBot, enemyBot)
                );
        }

        TEST_METHOD(TestIsBotAlignedWithAttackZone_EnemyBotIsTurnedInwardsAndCloseEnought)
        {
            auto myBot = std::make_shared<BotWarz::Bot>(
                0,
                Geometry::Point(100.0, 100.0),
                0.0,
                10.0
                );

            auto enemyBot = std::make_shared<BotWarz::Bot>(
                0,
                Geometry::Point(110.0, 100.0),
                -180.0,
                180.0/*speed*/
                );

            Assert::IsTrue(
                BotWarz::Strategy::isBotAlignedWithAttackZone(myBot, enemyBot)
                );
        }

        TEST_METHOD(TestIsStuckedNearTheWall)
        {
            auto myBot = std::make_shared<BotWarz::Bot>(
                    0,
                    Geometry::Point(0.0, 0.0),
                    0.0,
                    0.0
                );

            auto pWorld = std::make_shared<BotWarz::World>();
            auto vSpeedLevels = createSpeedLevels();
            double dNoBotRadius = 0.0;

            //
            // Top Wall
            //
            auto ptNearTopWall = Geometry::Point(100.0, 0.0);
            {
                myBot->setPosition(ptNearTopWall);
                myBot->setAngleInDegrees(+1.0);

                Assert::IsFalse(
                    BotWarz::Strategy::isStuckedNearTheWall(
                    myBot, pWorld, vSpeedLevels, dNoBotRadius
                    )
                    );
            }

            {
                myBot->setPosition(ptNearTopWall);
                myBot->setAngleInDegrees(-1.0);

                Assert::IsTrue(
                    BotWarz::Strategy::isStuckedNearTheWall(
                    myBot, pWorld, vSpeedLevels, dNoBotRadius
                    )
                    );
            }

            {
                myBot->setPosition(ptNearTopWall);
                myBot->setAngleInDegrees(-179.0);

                Assert::IsTrue(
                    BotWarz::Strategy::isStuckedNearTheWall(
                    myBot, pWorld, vSpeedLevels, dNoBotRadius
                    )
                    );
            }

            {
                myBot->setPosition(ptNearTopWall);
                myBot->setAngleInDegrees(+179.0);

                Assert::IsFalse(
                    BotWarz::Strategy::isStuckedNearTheWall(
                    myBot, pWorld, vSpeedLevels, dNoBotRadius
                    )
                    );
            }

            //
            // Left Wall
            //
            auto ptNearLeftWall = Geometry::Point(0.0, 100.0);
            {
                myBot->setPosition(ptNearLeftWall);
                myBot->setAngleInDegrees(-89.0);

                Assert::IsFalse(
                    BotWarz::Strategy::isStuckedNearTheWall(
                    myBot, pWorld, vSpeedLevels, dNoBotRadius
                    )
                    );
            }

            {
                myBot->setPosition(ptNearLeftWall);
                myBot->setAngleInDegrees(-91.0);

                Assert::IsTrue(
                    BotWarz::Strategy::isStuckedNearTheWall(
                    myBot, pWorld, vSpeedLevels, dNoBotRadius
                    )
                    );
            }

            {
                myBot->setPosition(ptNearLeftWall);
                myBot->setAngleInDegrees(+91.0);

                Assert::IsTrue(
                    BotWarz::Strategy::isStuckedNearTheWall(
                    myBot, pWorld, vSpeedLevels, dNoBotRadius
                    )
                    );
            }

            {
                myBot->setPosition(ptNearLeftWall);
                myBot->setAngleInDegrees(+89.0);

                Assert::IsFalse(
                    BotWarz::Strategy::isStuckedNearTheWall(
                    myBot, pWorld, vSpeedLevels, dNoBotRadius
                    )
                    );
            }

            //
            // Bottom Wall
            //
            auto ptNearBottomWall = Geometry::Point(100.0, pWorld->getSizeY());
            {
                myBot->setPosition(ptNearBottomWall);
                myBot->setAngleInDegrees(-1.0);

                Assert::IsFalse(
                    BotWarz::Strategy::isStuckedNearTheWall(
                    myBot, pWorld, vSpeedLevels, dNoBotRadius
                    )
                    );
            }

            {
                myBot->setPosition(ptNearBottomWall);
                myBot->setAngleInDegrees(+1.0);

                Assert::IsTrue(
                    BotWarz::Strategy::isStuckedNearTheWall(
                    myBot, pWorld, vSpeedLevels, dNoBotRadius
                    )
                    );
            }

            {
                myBot->setPosition(ptNearBottomWall);
                myBot->setAngleInDegrees(+179.0);

                Assert::IsTrue(
                    BotWarz::Strategy::isStuckedNearTheWall(
                    myBot, pWorld, vSpeedLevels, dNoBotRadius
                    )
                    );
            }

            {
                myBot->setPosition(ptNearBottomWall);
                myBot->setAngleInDegrees(-179.0);

                Assert::IsFalse(
                    BotWarz::Strategy::isStuckedNearTheWall(
                    myBot, pWorld, vSpeedLevels, dNoBotRadius
                    )
                    );
            }

            //
            // Right Wall
            //
            auto ptNearRightWall = Geometry::Point(pWorld->getSizeX(), 100.0);
            {
                myBot->setPosition(ptNearRightWall);
                myBot->setAngleInDegrees(+89.0);

                Assert::IsTrue(
                    BotWarz::Strategy::isStuckedNearTheWall(
                    myBot, pWorld, vSpeedLevels, dNoBotRadius
                    )
                    );
            }

            {
                myBot->setPosition(ptNearRightWall);
                myBot->setAngleInDegrees(+91.0);

                Assert::IsFalse(
                    BotWarz::Strategy::isStuckedNearTheWall(
                    myBot, pWorld, vSpeedLevels, dNoBotRadius
                    )
                    );
            }

            {
                myBot->setPosition(ptNearRightWall);
                myBot->setAngleInDegrees(-91.0);

                Assert::IsFalse(
                    BotWarz::Strategy::isStuckedNearTheWall(
                    myBot, pWorld, vSpeedLevels, dNoBotRadius
                    )
                    );
            }

            {
                myBot->setPosition(ptNearRightWall);
                myBot->setAngleInDegrees(-89.0);

                Assert::IsTrue(
                    BotWarz::Strategy::isStuckedNearTheWall(
                    myBot, pWorld, vSpeedLevels, dNoBotRadius
                    )
                    );
            }

        }

    private:
        std::vector<BotWarz::SpeedLevel>    createSpeedLevels()
        {
            std::vector<BotWarz::SpeedLevel> vSpeedLevels;
            vSpeedLevels.push_back(BotWarz::SpeedLevel(10.0, 30.0));
            vSpeedLevels.push_back(BotWarz::SpeedLevel(30.0, 15.0));
            vSpeedLevels.push_back(BotWarz::SpeedLevel(90.0, 10.0));
            vSpeedLevels.push_back(BotWarz::SpeedLevel(180.0, 5.0));
            vSpeedLevels.push_back(BotWarz::SpeedLevel(360.0, 2.0));
            return vSpeedLevels;
        }
    };
}