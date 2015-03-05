#pragma once


#include "World.h"
#include "Player.h"
#include "SpeedLevel.h"

#include "jsoncpp/include/json/json.h"

#include "boost/noncopyable.hpp"

#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

namespace BotWarz {

    class NotImplementedException
        : public std::logic_error 
    {
    public:
        NotImplementedException(const char * error = "Function not yet implemented!")
            : std::logic_error(error)
        {
        }
    };

    class DLL_API GameCommandBase
    {
    public:
        GameCommandBase( unsigned i_nBotId)
        : m_nBotId( i_nBotId )
        {
        }

        virtual ~GameCommandBase()
        {
        }

        unsigned    getBotId() const
        {
            return m_nBotId;
        }

        virtual std::string getCommand() const = 0;

        virtual     Json::Value toJson() const
        {
            const char* jsonKeyCommand = "cmd";
            const char* jsonKeyBotId = "id";

            Json::Value cmd;
            cmd[jsonKeyCommand] = getCommand();
            cmd[jsonKeyBotId] = getBotId();

            return cmd;
        }

        virtual std::ostream& toStream(std::ostream& out) const
        {
            out << "Command = { id: " << getBotId() << " cmd: " << getCommand() << " } ";
            return out;
        }

    private:
        unsigned   m_nBotId;
    };

    class DLL_API GameCommandAccelerate : public GameCommandBase
    {
    public:
        GameCommandAccelerate(unsigned i_nBotId) 
            : GameCommandBase(i_nBotId)
        {
        }

        virtual std::string getCommand() const
        {
            return "accelerate";
        }
    };

    class DLL_API GameCommandBrake : public GameCommandBase
    {
    public:
        GameCommandBrake(unsigned i_nBotId)
            : GameCommandBase(i_nBotId)
        {
        }

        virtual std::string getCommand() const
        {
            return "brake";
        }
    };

    class DLL_API GameCommandSteer : public GameCommandBase
    {
    public:
        GameCommandSteer(unsigned i_nBotId, double i_dAngle) 
            : GameCommandBase(i_nBotId)
            ,m_dAngle(i_dAngle)
        {
        }

        virtual std::string getCommand() const
        {
            return "steer";
        }

        double getAngle() const
        {
            return m_dAngle;
        }

        virtual     Json::Value toJson() const
        {
            const char* jsonKeyAngle = "angle";

            auto cmd = __super::toJson();
            cmd[jsonKeyAngle] = getAngle();
            return cmd;
        }

        std::ostream& toStream(std::ostream& out) const
        {
            out << "Command = { id: " << getBotId() << " cmd: " << getCommand() << " angle: " << getAngle() << " } ";
            return out;
        }

    private:
        double  m_dAngle;
    };

    DLL_API std::ostream& operator<<(std::ostream& out, const GameCommandBase& command);

    class DLL_API StrategyInterface
    {
    public:
        StrategyInterface()
        {
        }
        virtual ~StrategyInterface()
        {
        }

        virtual std::vector<std::shared_ptr<GameCommandBase>>    getCommands(
            const std::shared_ptr<Player> pMyPlayer,
            const std::shared_ptr<Player> pOtherPlayer
            ) = 0;
    };

    class DLL_API AlwaysAccelerateStrategy : public StrategyInterface
    {
    public:
        AlwaysAccelerateStrategy()
        {
        };

        virtual ~AlwaysAccelerateStrategy()
        {
        };

        virtual std::vector<std::shared_ptr<GameCommandBase>>    getCommands(
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

        virtual std::vector<std::shared_ptr<GameCommandBase>>    getCommands(
            const std::shared_ptr<Player> pMyPlayer,
            const std::shared_ptr<Player> pOtherPlayer
            );

    private:
        const std::vector<SpeedLevel>&  m_vSpeedLevels;
        const double m_dBotRadius;
        const std::shared_ptr<World> m_pWorld;
    };
}