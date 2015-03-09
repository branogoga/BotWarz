#pragma once

#include "./Interface.h"

#include <boost/noncopyable.hpp>

#include <vector>
#include <memory>

#pragma warning(push)
#pragma warning(disable: 4251 /* Shared_ptr going across Dll (Test) */ )

namespace BotWarz {

    class SpeedLevel;
    class World;

    namespace Strategy {

        class TESTABLE AttackClosestBot : public Interface, boost::noncopyable
        {
        public:

            AttackClosestBot(
                const std::vector<SpeedLevel>& i_vSpeedLevels,
                const double i_dBotRadius,
                const std::shared_ptr<World> i_pWorld
                ) :
                m_vSpeedLevels(i_vSpeedLevels),
                m_dBotRadius(i_dBotRadius),
                m_pWorld(i_pWorld)
            {
            }

            virtual ~AttackClosestBot()
            {
            }

            virtual std::vector<std::shared_ptr<Command::Interface>>    getCommands(
                const std::shared_ptr<Player> pMyPlayer,
                const std::shared_ptr<Player> pOtherPlayer
                );

        private:
            const std::vector<SpeedLevel>&  m_vSpeedLevels;
            const double m_dBotRadius;
            const std::shared_ptr<World> m_pWorld;
        };

    }//namespace Strategy
}//namespace BotWarz

#pragma warning(pop)