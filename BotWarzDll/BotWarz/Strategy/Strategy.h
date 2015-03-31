#pragma once

#include "dll.h"

#include <vector>
#include <memory>

#pragma warning(push)
#pragma warning(disable: 4251 /* Shared_ptr going across Dll (Test) */ )

namespace Geometry {
    class Point;
}

namespace BotWarz {

    class Bot;
    class SpeedLevel;
    class World;

    namespace Strategy {

        TESTABLE size_t  findClosestBot(
            const std::vector<std::shared_ptr<BotWarz::Bot>>& i_vBots,
            const Geometry::Point& i_pPoint
            );

        TESTABLE unsigned    numberOfStepsToReachPoint(
            const std::shared_ptr<Bot> myBot,
            const Geometry::Point& pointToReach,
            const std::vector<SpeedLevel>& i_vSpeedLevels,
            const double i_dTimeDeltaInMilliseconds = 200.0
            );

        TESTABLE size_t  findMostReachableBot(
            const std::vector<std::shared_ptr<BotWarz::Bot>>& i_vBots,
            const std::shared_ptr<BotWarz::Bot> myBot,
            const std::vector<BotWarz::SpeedLevel>& i_vSpeedLevels
            );

        TESTABLE bool    isCollisionExpected(
            const BotWarz::Bot& bot1,
            const BotWarz::Bot& bot2,
            const double dTimeDeltaInMilliseconds = 250.0
            );

        TESTABLE double calculateMaxAttackAngleInDegrees(
            const double i_dBotRadius,
            const double i_dBotDistance
            );

        TESTABLE bool   isStuckedNearTheWall(
            const std::shared_ptr<BotWarz::Bot> i_pBot,
            const std::shared_ptr<BotWarz::World> i_pWorld,
            const std::vector<BotWarz::SpeedLevel>& i_vspeedLevels,
            double i_dBotRadius
            );

        TESTABLE bool   isBotAlignedWithAttackZone(
            const std::shared_ptr<BotWarz::Bot> i_pBot1,
            const std::shared_ptr<BotWarz::Bot> i_pBot2
            );

        class TESTABLE FindEnemyBotPolicyInterface
        {
        public:
            FindEnemyBotPolicyInterface();
            virtual ~FindEnemyBotPolicyInterface();

            virtual size_t getBotIndex(
                std::shared_ptr<Bot> myBot,
                const std::vector < std::shared_ptr<Bot>>& i_vBots
                ) = 0;

            virtual std::string getName() const = 0;
        };

        class TESTABLE FindClosestBotPolicy : public FindEnemyBotPolicyInterface
        {
        public:
            FindClosestBotPolicy();
            virtual ~FindClosestBotPolicy();

            virtual size_t getBotIndex(
                std::shared_ptr<Bot> myBot,
                const std::vector < std::shared_ptr<Bot>>& i_vBots
                );

            virtual std::string getName() const
            {
                return "FindClosestBotPolicy";
            }

        };


        class TESTABLE FindMostReachableBotPolicy : public FindEnemyBotPolicyInterface
        {
        public:
            FindMostReachableBotPolicy(
                const std::vector<BotWarz::SpeedLevel>& i_vSpeedLevels
                );
            virtual ~FindMostReachableBotPolicy();

            virtual size_t getBotIndex(
                std::shared_ptr<Bot> myBot,
                const std::vector < std::shared_ptr<Bot>>& i_vBots
                );

            virtual std::string getName() const
            {
                return "FindMostReachableBotPolicy";
            }

        private:
            std::vector<BotWarz::SpeedLevel> m_vSpeedLevels;
        };

        class TESTABLE ChasingPolicyInterface
        {
        public:
            ChasingPolicyInterface();
            ~ChasingPolicyInterface();

            virtual Geometry::Point getDestinationPoint(const std::shared_ptr<Bot> i_pBot) = 0;
            virtual std::string getName() const = 0;
        private:
        };

        class TESTABLE CurrentPositionChasingPolicy : public ChasingPolicyInterface
        {
        public:
            CurrentPositionChasingPolicy();
            ~CurrentPositionChasingPolicy();

            virtual Geometry::Point getDestinationPoint(const std::shared_ptr<Bot> i_pBot);

            virtual std::string getName() const
            {
                return "CurrentPositionChasingPolicy";
            }
        };

        class TESTABLE FuturePositionChasingPolicy : public ChasingPolicyInterface
        {
        public:
            FuturePositionChasingPolicy(
                double i_dTimeDeltaInMilliseconds = 250.0
                );
            ~FuturePositionChasingPolicy();

            virtual Geometry::Point getDestinationPoint(const std::shared_ptr<Bot> i_pBot);

            virtual std::string getName() const
            {
                return "FuturePositionChasingPolicy";
            }
        private:
            double m_dTimeDeltaInMilliseconds;
        };

    }//namespace Strategy
}//namespace BotWarz

#pragma warning(pop)
