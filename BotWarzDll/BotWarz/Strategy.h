#pragma once


#include "World.h"
#include "Player.h"
#include "SpeedLevel.h"

#include "BotWarz/Command/Accelerate.h"
#include "BotWarz/Command/Brake.h"
#include "BotWarz/Command/Steer.h"

#include "jsoncpp/include/json/json.h"

#include "boost/noncopyable.hpp"

#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

namespace BotWarz {

    class StrategyInterface
    {
    public:
        StrategyInterface()
        {
        }
        virtual ~StrategyInterface()
        {
        }

        virtual std::vector<std::shared_ptr<Command::Interface>>    getCommands(
            const std::shared_ptr<Player> pMyPlayer,
            const std::shared_ptr<Player> pOtherPlayer
            ) = 0;
    };

    class AlwaysAccelerateStrategy : public StrategyInterface
    {
    public:
        AlwaysAccelerateStrategy()
        {
        };

        virtual ~AlwaysAccelerateStrategy()
        {
        };

        virtual std::vector<std::shared_ptr<Command::Interface>>    getCommands(
            const std::shared_ptr<Player> pMyPlayer,
            const std::shared_ptr<Player> pOtherPlayer
            );
    };

    template class  std::shared_ptr<World>;

    class  AttackTheClosestBot : public StrategyInterface, boost::noncopyable
    {
    public:
        AttackTheClosestBot(
            const std::vector<SpeedLevel>& i_vSpeedLevels,
            const double i_dBotRadius,
            const std::shared_ptr<World> i_pWorld
            ) : 
            m_vSpeedLevels(i_vSpeedLevels),
            m_dBotRadius( i_dBotRadius ),
            m_pWorld(i_pWorld)
        {
        };

        virtual ~AttackTheClosestBot()
        {
        };

        virtual std::vector<std::shared_ptr<Command::Interface>>    getCommands(
            const std::shared_ptr<Player> pMyPlayer,
            const std::shared_ptr<Player> pOtherPlayer
            );

    private:
        const std::vector<SpeedLevel>&  m_vSpeedLevels;
        const double m_dBotRadius;
        const std::shared_ptr<World> m_pWorld;
    };
}