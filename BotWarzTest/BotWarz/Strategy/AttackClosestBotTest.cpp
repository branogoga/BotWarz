#include "stdafx.h"
#include "CppUnitTest.h"

#include "BotWarz/Player.h"
#include "BotWarz/SpeedLevel.h"
#include "BotWarz/World.h"
#include "BotWarz/Command/Accelerate.h"
#include "BotWarz/Command/Brake.h"
#include "BotWarz/Command/Steer.h"
#include "BotWarz/Strategy/AttackClosestBot.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace BotWarzTest
{
	TEST_CLASS(AttackClosestBotTest)
	{
	public:
        TEST_METHOD_INITIALIZE(TestInitialize)
        {
            m_dBotRadius = 20.0;
            m_vSpeedLevels = createSpeedLevels();
        }

        TEST_METHOD_CLEANUP(TestCleanUp)
        {
            m_vSpeedLevels.clear();
        }
		
        TEST_METHOD(TestMoveForwardToBotStandingInFrontOfYou)
		{
            auto strategy = createStrategy();

            unsigned nBotId = 1;

            // My Player
            std::vector<std::shared_ptr<BotWarz::Bot>>   vMyBots;
            vMyBots.push_back(
                std::make_shared<BotWarz::Bot>(nBotId++,
                    Geometry::Point(100.0, 100.0),
                    0.0,
                    getMinimalSpeed(m_vSpeedLevels)
                )
                );

            auto myPlayer = createPlayer("My", vMyBots);

            //
            // Enemy player
            //
            std::vector<std::shared_ptr<BotWarz::Bot>>   vEnemyBots;
            vEnemyBots.push_back(
                std::make_shared<BotWarz::Bot>( nBotId++,
                Geometry::Point(120.0, 100.0),
                0.0,
                getMaximalSpeed(m_vSpeedLevels)
                )
                );

            auto enemyPlayer = createPlayer("Enemy", vEnemyBots);

            auto vCommands = strategy->getCommands(
                myPlayer, enemyPlayer
                );

            Assert::AreEqual(
                (unsigned)1,
                (unsigned)vCommands.size()
                );

            auto pAccelerateCommand =
                std::dynamic_pointer_cast<BotWarz::Command::Accelerate>(vCommands[0]);
            Assert::IsTrue(pAccelerateCommand!=nullptr);
		}

        TEST_METHOD(TestSteerToBotStandingInFrontOfYouIfHavingMaximalSpeed)
        {
            auto strategy = createStrategy();

            unsigned nBotId = 1;

            // My Player
            std::vector<std::shared_ptr<BotWarz::Bot>>   vMyBots;
            vMyBots.push_back(
                std::make_shared<BotWarz::Bot>(nBotId++,
                Geometry::Point(100.0, 100.0),
                0.0,
                getMaximalSpeed(m_vSpeedLevels)
                )
                );

            auto myPlayer = createPlayer("My", vMyBots);

            //
            // Enemy player
            //
            std::vector<std::shared_ptr<BotWarz::Bot>>   vEnemyBots;
            vEnemyBots.push_back(
                std::make_shared<BotWarz::Bot>(nBotId++,
                Geometry::Point(120.0, 100.0),
                0.0,
                getMaximalSpeed(m_vSpeedLevels)
                )
                );

            auto enemyPlayer = createPlayer("Enemy", vEnemyBots);

            auto vCommands = strategy->getCommands(
                myPlayer, enemyPlayer
                );

            Assert::AreEqual(
                (unsigned)1,
                (unsigned)vCommands.size()
                );

            auto pSteerCommand =
                std::dynamic_pointer_cast<BotWarz::Command::Steer>(vCommands[0]);
            Assert::IsTrue(pSteerCommand != nullptr);
        }

        // Prevent going too fast. Breaking and changing angle is 
        // significant loss of time.
        TEST_METHOD(TestSteerToBotStandingInFrontOfYouIfItIsCloseEnought)
        {
            auto strategy = createStrategy();

            unsigned nBotId = 1;

            // My Player
            std::vector<std::shared_ptr<BotWarz::Bot>>   vMyBots;
            vMyBots.push_back(
                std::make_shared<BotWarz::Bot>(
                    nBotId++,
                    Geometry::Point(100.0, 100.0),
                    0.0,
                    m_vSpeedLevels[2].getSpeed()
                )
                );

            auto myPlayer = createPlayer("My", vMyBots);

            //
            // Enemy player
            //
            std::vector<std::shared_ptr<BotWarz::Bot>>   vEnemyBots;
            vEnemyBots.push_back(
                std::make_shared<BotWarz::Bot>(
                    nBotId++,
                    Geometry::Point(120.0, 100.0),
                    0.0,
                    getMaximalSpeed(m_vSpeedLevels)
                )
                );

            auto enemyPlayer = createPlayer("Enemy", vEnemyBots);

            auto vCommands = strategy->getCommands(
                myPlayer, enemyPlayer
                );

            Assert::AreEqual(
                (unsigned)1,
                (unsigned)vCommands.size()
                );

            auto pAccelerateCommand =
                std::dynamic_pointer_cast<BotWarz::Command::Accelerate>(vCommands[0]);
            Assert::IsTrue(pAccelerateCommand != nullptr);
        }

        TEST_METHOD(TestMoveForwardToBotStandingInAttackAngleInFrontOfYou)
        {
            auto strategy = createStrategy();

            unsigned nBotId = 1;

            // My Player
            std::vector<std::shared_ptr<BotWarz::Bot>>   vMyBots;
            vMyBots.push_back(
                std::make_shared<BotWarz::Bot>(nBotId++,
                Geometry::Point(100.0, 100.0),
                0.0,
                getMinimalSpeed(m_vSpeedLevels)
                )
                );

            auto myPlayer = createPlayer("My", vMyBots);

            //
            // Enemy player
            //
            std::vector<std::shared_ptr<BotWarz::Bot>>   vEnemyBots;
            vEnemyBots.push_back(
                std::make_shared<BotWarz::Bot>(nBotId++,
                Geometry::Point(120.0, 112.0),
                0.0,
                getMinimalSpeed(m_vSpeedLevels)
                )
                );

            auto enemyPlayer = createPlayer("Enemy", vEnemyBots);

            auto vCommands = strategy->getCommands(
                myPlayer, enemyPlayer
                );

            Assert::AreEqual(
                (unsigned)1,
                (unsigned)vCommands.size()
                );

            auto pAccelerateCommand =
                std::dynamic_pointer_cast<BotWarz::Command::Accelerate>(vCommands[0]);
            Assert::IsTrue(pAccelerateCommand != nullptr);
        }

        TEST_METHOD(TestSteerClockwiseToTheEnemy)
        {
            auto strategy = createStrategy();

            unsigned nBotId = 1;

            // My Player
            std::vector<std::shared_ptr<BotWarz::Bot>>   vMyBots;
            vMyBots.push_back(
                std::make_shared<BotWarz::Bot>(nBotId++,
                Geometry::Point(100.0, 100.0),
                0.0,
                getMinimalSpeed(m_vSpeedLevels)
                )
                );

            auto myPlayer = createPlayer("My", vMyBots);

            //
            // Enemy player
            //
            std::vector<std::shared_ptr<BotWarz::Bot>>   vEnemyBots;
            vEnemyBots.push_back(
                std::make_shared<BotWarz::Bot>(nBotId++,
                Geometry::Point(100.0, 150.0),
                0.0,
                getMinimalSpeed(m_vSpeedLevels)
                )
                );

            auto enemyPlayer = createPlayer("Enemy", vEnemyBots);

            auto vCommands = strategy->getCommands(
                myPlayer, enemyPlayer
                );

            Assert::AreEqual(
                (unsigned)1,
                (unsigned)vCommands.size()
                );

            auto pSteerCommand =
                std::dynamic_pointer_cast<BotWarz::Command::Steer>(vCommands[0]);
            Assert::IsTrue(pSteerCommand != nullptr);

            Assert::AreEqual(
                90.0,
                pSteerCommand->getAngle()
                );
        }


        TEST_METHOD(TestSteerCounterClockwiseToTheEnemy)
        {
            auto strategy = createStrategy();

            unsigned nBotId = 1;

            // My Player
            std::vector<std::shared_ptr<BotWarz::Bot>>   vMyBots;
            vMyBots.push_back(
                std::make_shared<BotWarz::Bot>(nBotId++,
                Geometry::Point(100.0, 100.0),
                0.0,
                getMinimalSpeed(m_vSpeedLevels)
                )
                );

            auto myPlayer = createPlayer("My", vMyBots);

            //
            // Enemy player
            //
            std::vector<std::shared_ptr<BotWarz::Bot>>   vEnemyBots;
            vEnemyBots.push_back(
                std::make_shared<BotWarz::Bot>(nBotId++,
                Geometry::Point(100.0, 50.0),
                0.0,
                getMinimalSpeed(m_vSpeedLevels)
                )
                );

            auto enemyPlayer = createPlayer("Enemy", vEnemyBots);

            auto vCommands = strategy->getCommands(
                myPlayer, enemyPlayer
                );

            Assert::AreEqual(
                (unsigned)1,
                (unsigned)vCommands.size()
                );

            auto pSteerCommand =
                std::dynamic_pointer_cast<BotWarz::Command::Steer>(vCommands[0]);
            Assert::IsTrue(pSteerCommand != nullptr);

            Assert::AreEqual(
                -90.0,
                pSteerCommand->getAngle()
                );
        }

        TEST_METHOD(TestSteerClockwiseToClosestEnemyIfStuckNearTopWall)
        {
            auto strategy = createStrategy();

            unsigned nBotId = 1;

            // My Player
            std::vector<std::shared_ptr<BotWarz::Bot>>   vMyBots;
            vMyBots.push_back(
                std::make_shared<BotWarz::Bot>(nBotId++,
                    Geometry::Point(100.0, m_dBotRadius),
                    -45.0,
                    0.0 /* Stuck near the wall */
                )
                );

            auto myPlayer = createPlayer("My", vMyBots);

            //
            // Enemy player
            //
            std::vector<std::shared_ptr<BotWarz::Bot>>   vEnemyBots;
            vEnemyBots.push_back(
                std::make_shared<BotWarz::Bot>(nBotId++,
                Geometry::Point(100.0, 50.0),
                    0.0,
                    getMinimalSpeed(m_vSpeedLevels)
                )
                );

            auto enemyPlayer = createPlayer("Enemy", vEnemyBots);

            auto vCommands = strategy->getCommands(
                myPlayer, enemyPlayer
                );

            Assert::AreEqual(
                (unsigned)1,
                (unsigned)vCommands.size()
                );

            auto pSteerCommand =
                std::dynamic_pointer_cast<BotWarz::Command::Steer>(vCommands[0]);
            Assert::IsTrue(pSteerCommand != nullptr);

            Assert::AreEqual(
                +30.0,
                pSteerCommand->getAngle()
                );
        }

        TEST_METHOD(TestSteerCounterClockwiseToClosestEnemyIfStuckNearTopWall)
        {
            auto strategy = createStrategy();

            unsigned nBotId = 1;

            // My Player
            std::vector<std::shared_ptr<BotWarz::Bot>>   vMyBots;
            vMyBots.push_back(
                std::make_shared<BotWarz::Bot>(nBotId++,
                Geometry::Point(100.0, m_dBotRadius),
                -45.0,
                0.0 /* Stuck near the wall */
                )
                );

            auto myPlayer = createPlayer("My", vMyBots);

            //
            // Enemy player
            //
            std::vector<std::shared_ptr<BotWarz::Bot>>   vEnemyBots;
            vEnemyBots.push_back(
                std::make_shared<BotWarz::Bot>(nBotId++,
                Geometry::Point(50.0, 50.0),
                0.0,
                getMinimalSpeed(m_vSpeedLevels)
                )
                );

            auto enemyPlayer = createPlayer("Enemy", vEnemyBots);

            auto vCommands = strategy->getCommands(
                myPlayer, enemyPlayer
                );

            Assert::AreEqual(
                (unsigned)1,
                (unsigned)vCommands.size()
                );

            auto pSteerCommand =
                std::dynamic_pointer_cast<BotWarz::Command::Steer>(vCommands[0]);
            Assert::IsTrue(pSteerCommand != nullptr);

            Assert::AreEqual(
                -30.0,
                pSteerCommand->getAngle()
                );
        }

        TEST_METHOD(TestSteerClockwiseToClosestEnemyIfNotInAttackAngle)
        {
            auto strategy = createStrategy();

            unsigned nBotId = 1;

            // My Player
            std::vector<std::shared_ptr<BotWarz::Bot>>   vMyBots;
            vMyBots.push_back(
                std::make_shared<BotWarz::Bot>(nBotId++,
                Geometry::Point(100.0, m_dBotRadius),
                -45.0,
                0.0 /* Stuck near the wall */
                )
                );

            auto myPlayer = createPlayer("My", vMyBots);

            //
            // Enemy player
            //
            std::vector<std::shared_ptr<BotWarz::Bot>>   vEnemyBots;
            vEnemyBots.push_back(
                std::make_shared<BotWarz::Bot>(nBotId++,
                Geometry::Point(50.0, 50.0),
                0.0,
                getMinimalSpeed(m_vSpeedLevels)
                )
                );

            auto enemyPlayer = createPlayer("Enemy", vEnemyBots);

            auto vCommands = strategy->getCommands(
                myPlayer, enemyPlayer
                );

            Assert::AreEqual(
                (unsigned)1,
                (unsigned)vCommands.size()
                );

            auto pSteerCommand =
                std::dynamic_pointer_cast<BotWarz::Command::Steer>(vCommands[0]);
            Assert::IsTrue(pSteerCommand != nullptr);

            Assert::AreEqual(
                -30.0,
                pSteerCommand->getAngle()
                );
        }

        TEST_METHOD(TestChooseMoreRechableBotToAttackTo1)
        {
            auto strategy = createStrategy();

            unsigned nBotId = 1;

            // My Player
            std::vector<std::shared_ptr<BotWarz::Bot>>   vMyBots;
            vMyBots.push_back(
                std::make_shared<BotWarz::Bot>(nBotId++,
                Geometry::Point(100.0, 100.0),
                -45.0,
                10.0 
                )
                );

            auto myPlayer = createPlayer("My", vMyBots);

            //
            // Enemy player
            //
            std::vector<std::shared_ptr<BotWarz::Bot>>   vEnemyBots;
            vEnemyBots.push_back(
                std::make_shared<BotWarz::Bot>(nBotId++,
                Geometry::Point(150.0, 100.0),
                0.0,
                getMinimalSpeed(m_vSpeedLevels)
                )
                );

            vEnemyBots.push_back(
                std::make_shared<BotWarz::Bot>(nBotId++,
                Geometry::Point(50.0, 100.0),
                0.0,
                getMinimalSpeed(m_vSpeedLevels)
                )
                );

            auto enemyPlayer = createPlayer("Enemy", vEnemyBots);

            auto vCommands = strategy->getCommands(
                myPlayer, enemyPlayer
                );

            Assert::AreEqual(
                (unsigned)1,
                (unsigned)vCommands.size()
                );

            auto pSteerCommand =
                std::dynamic_pointer_cast<BotWarz::Command::Steer>(vCommands[0]);
            Assert::IsTrue(pSteerCommand != nullptr);

            Assert::AreEqual(
                45.0,
                pSteerCommand->getAngle()
                );
        }

        TEST_METHOD(TestChooseMoreRechableBotToAttackTo2)
        {
            auto strategy = createStrategy();

            unsigned nBotId = 1;

            // My Player
            std::vector<std::shared_ptr<BotWarz::Bot>>   vMyBots;
            vMyBots.push_back(
                std::make_shared<BotWarz::Bot>(nBotId++,
                Geometry::Point(100.0, 100.0),
                -95.0,
                10.0
                )
                );

            auto myPlayer = createPlayer("My", vMyBots);

            //
            // Enemy player
            //
            std::vector<std::shared_ptr<BotWarz::Bot>>   vEnemyBots;
            vEnemyBots.push_back(
                std::make_shared<BotWarz::Bot>(nBotId++,
                Geometry::Point(150.0, 100.0),
                0.0,
                getMinimalSpeed(m_vSpeedLevels)
                )
                );

            vEnemyBots.push_back(
                std::make_shared<BotWarz::Bot>(nBotId++,
                Geometry::Point(50.0, 100.0),
                0.0,
                getMinimalSpeed(m_vSpeedLevels)
                )
                );

            auto enemyPlayer = createPlayer("Enemy", vEnemyBots);

            auto vCommands = strategy->getCommands(
                myPlayer, enemyPlayer
                );

            Assert::AreEqual(
                (unsigned)1,
                (unsigned)vCommands.size()
                );

            auto pSteerCommand =
                std::dynamic_pointer_cast<BotWarz::Command::Steer>(vCommands[0]);
            Assert::IsTrue(pSteerCommand != nullptr);

            Assert::AreEqual(
                -85.0,
                pSteerCommand->getAngle()
                );
        }

    private:
        std::unique_ptr<BotWarz::Strategy::AttackClosestBot>   createStrategy()
        {
            m_vSpeedLevels = createSpeedLevels();
            auto strategy = std::make_unique<BotWarz::Strategy::AttackClosestBot>(
                m_vSpeedLevels,
                m_dBotRadius,
                createWorld()
                );

            return strategy;
        }

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

        std::shared_ptr<BotWarz::World>    createWorld()
        {
            return std::make_shared<BotWarz::World>(
                900, 600
                );
        }

        std::shared_ptr<BotWarz::Player>    createPlayer(
            const std::string& i_szName,
            const std::vector<std::shared_ptr<BotWarz::Bot>> i_vBots
            )
        {
            auto player = std::make_shared<BotWarz::Player>(i_szName);
            player->setBots(
                i_vBots
                );

            return player;
        }

        double  m_dBotRadius;
        std::vector<BotWarz::SpeedLevel> m_vSpeedLevels;
    };
}