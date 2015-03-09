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

        class TESTABLE FindEnemyBotPolicyInterface
        {
        public:
            FindEnemyBotPolicyInterface();
            virtual ~FindEnemyBotPolicyInterface();

            virtual size_t getBotIndex(
                std::shared_ptr<Bot> myBot,
                const std::vector < std::shared_ptr<Bot>>& i_vBots
                ) = 0;
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
        private:
            std::vector<BotWarz::SpeedLevel> m_vSpeedLevels;
        };

        class TESTABLE ChasingPolicyInterface
        {
        public:
            ChasingPolicyInterface();
            ~ChasingPolicyInterface();

            virtual Geometry::Point getDestinationPoint() = 0;
        private:
        };

        class TESTABLE CurrentPositionChasingPolicy : public ChasingPolicyInterface
        {
        public:
            CurrentPositionChasingPolicy( const std::shared_ptr<Bot> i_pBot );
            ~CurrentPositionChasingPolicy();

            virtual Geometry::Point getDestinationPoint();
        private:
            std::shared_ptr<Bot> m_pBot;
        };


        class TESTABLE FuturePositionChasingPolicy : public ChasingPolicyInterface
        {
        public:
            FuturePositionChasingPolicy(
                const std::shared_ptr<Bot> i_pBot,
                double i_dTimeDeltaInMilliseconds = 1000.0
                );
            ~FuturePositionChasingPolicy();

            virtual Geometry::Point getDestinationPoint();
        private:
            std::shared_ptr<Bot> m_pBot;
            double m_dTimeDeltaInMilliseconds;
        };

    }//namespace Strategy
}//namespace BotWarz

#pragma warning(pop)
