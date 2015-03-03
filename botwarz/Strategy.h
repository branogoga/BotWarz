#pragma once

#include "Player.h"

#include "jsoncpp/include/json/json.h"

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

    class GameCommandBase
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

    class GameCommandAccelerate : public GameCommandBase
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

    class GameCommandBrake : public GameCommandBase
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

    class GameCommandSteer : public GameCommandBase
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

    std::ostream& operator<<(std::ostream& out, const GameCommandBase& command);

    class StrategyInterface
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

    class AlwaysAccelerateStrategy : public StrategyInterface
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

    class AttackTheClosestBot : public StrategyInterface
    {
    public:
        AttackTheClosestBot()
        {
        };

        virtual ~AttackTheClosestBot()
        {
        };

        virtual std::vector<std::shared_ptr<GameCommandBase>>    getCommands(
            const std::shared_ptr<Player> pMyPlayer,
            const std::shared_ptr<Player> pOtherPlayer
            );
    };
}