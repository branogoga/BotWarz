#pragma once

#include "./Interface.h"

#include <boost/noncopyable.hpp>
//#include <boost/random/mersenne_twister.hpp>

#include <vector>
#include <memory>

#pragma warning(push)
#pragma warning(disable: 4251 /* Shared_ptr going across Dll (Test) */ )

class Logger;

namespace BotWarz {

    class Bot;
    class Game;
    class SpeedLevel;
    class World;

    namespace Strategy {

        class FindEnemyBotPolicyInterface;
        class ChasingPolicyInterface;

        class TESTABLE AttackClosestBot : public Interface, boost::noncopyable
        {
        public:

            AttackClosestBot(
                const std::vector<SpeedLevel>& i_vSpeedLevels,
                const double i_dBotRadius,
                const std::shared_ptr<World> i_pWorld,
                std::shared_ptr<Logger> i_pLogger = nullptr
                );

            virtual ~AttackClosestBot();

            virtual std::vector<std::shared_ptr<Command::Interface>>    getCommands(
                const std::shared_ptr<Player> pMyPlayer,
                const std::shared_ptr<Player> pOtherPlayer
                );

            virtual std::string getName() const;

            unsigned getNumberOfStepsToChaseEnemyBot(
                const std::shared_ptr<Bot> i_pMyBot,
                const std::shared_ptr<Bot> i_pEnemyBot,
                const std::shared_ptr<Player> i_pMyPlayer,
                double i_dBotRadius
                ) const;

            size_t getClosestEnemyBotIndex(
                const std::shared_ptr<Bot> i_pMyBot,
                const std::vector<std::shared_ptr<Bot>> i_vEnemyBots,
                const std::shared_ptr<Player> i_pMyPlayer,
                double i_dBotRadius
                ) const;

        private:
            std::unique_ptr<Strategy::FindEnemyBotPolicyInterface>  m_enemyBotFinderPolicy;
            std::unique_ptr<ChasingPolicyInterface> m_chasingStrategyPolicy;

            std::shared_ptr<Command::Interface> chaseBot(
                const std::shared_ptr<Bot> myBot,
                const std::shared_ptr<Bot> enemyBot,
                const std::shared_ptr<Player> i_pMyPlayer,
                std::shared_ptr<Logger> pLogger = nullptr
                ) const;

            const std::vector<SpeedLevel>&  m_vSpeedLevels;
            const double m_dBotRadius;
            const std::shared_ptr<World> m_pWorld;
            std::shared_ptr<Logger> m_pLogger;
            //boost::random::mt19937 m_randomGenerator;
        };

    }//namespace Strategy
}//namespace BotWarz

#pragma warning(pop)