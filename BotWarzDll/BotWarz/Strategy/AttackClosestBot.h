#pragma once

#include "./Interface.h"

#include <boost/noncopyable.hpp>

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

        private:
            std::unique_ptr<Strategy::FindEnemyBotPolicyInterface>  m_enemyBotFinderPolicy;
            std::unique_ptr<ChasingPolicyInterface> m_chasingStrategyPolicy;

            std::shared_ptr<Command::Interface> chaseBot(
                std::shared_ptr<Bot> myBot,
                std::shared_ptr<Bot> enemyBot,
                const std::shared_ptr<Player> i_pMyPlayer,
                std::shared_ptr<Logger> pLogger = nullptr
                );

            const std::vector<SpeedLevel>&  m_vSpeedLevels;
            const double m_dBotRadius;
            const std::shared_ptr<World> m_pWorld;
            std::shared_ptr<Logger> m_pLogger;
        };

    }//namespace Strategy
}//namespace BotWarz

#pragma warning(pop)