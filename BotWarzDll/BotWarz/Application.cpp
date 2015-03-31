#include "stdafx.h"
#include "./Application.h"

#include "Bot.h"
#include "Game.h"
#include "GameFactory.h"
#include "Logger.h"
#include "Player.h"
#include "BotWarz\Message\Messages.h"
#include "BotWarz\Strategy\NoCommands.h"
#include "BotWarz\Strategy\AttackClosestBot.h"

#include "jsoncpp/include/json/json.h"

namespace BotWarz 
{
    class Application : public ApplicationInterface
    {
    public:
        Application(const char* i_szNickName = "", std::shared_ptr<Logger> i_pLogger = nullptr)
            : m_szNickName(i_szNickName)
            , m_pLogger(i_pLogger)
        {
        }

        virtual ~Application()
        {
        }

        virtual void    Initialize(const Json::Value& i_jsonGame)
        {
            GameFactory    gameFactory(m_szNickName);

            const char* jsonKeyGame = "game";
            Json::Value jsonGame = i_jsonGame[jsonKeyGame];
            m_pGame = gameFactory.createFromJson(jsonGame);

            m_pGameStrategy = createStrategy(m_pGame);
        }

        virtual void    Update(const Json::Value& json)
        {
            const char* jsonKeyPlay = "play";
            const char* jsonKeyTime = "time";
            const char* jsonKeyPlayers = "players";
            Json::Value jsonPlay = json[jsonKeyPlay];

            m_pGame->setTime( jsonPlay[jsonKeyTime].asDouble() );
            UpdatePlayers(jsonPlay[jsonKeyPlayers]);
        }

        void    Advance(const double i_dTimeStepInMilliseconds)
        {
            m_pGame->advance(i_dTimeStepInMilliseconds);
        }

        unsigned  GetId() const
        {
            return m_pGame->getId();
        }

        std::string GetEnemyNickname() const
        {
            return m_pGame->getOtherPlayer()->getNickName();
        }

        std::string GetPlayerNickname() const
        {
            return m_pGame->getMyPlayer()->getNickName();
        }

        std::string GetStrategyName() const
        {
            return m_pGameStrategy->getName();
        }


        bool    isMyPlayer(const Json::Value& jsonPlayer)
        {
            const char* jsonKeyPlayerNickName = "nickname";
            return jsonPlayer[jsonKeyPlayerNickName].asString() == m_szNickName;
        }

        void    UpdatePlayers(const Json::Value& jsonPlayers)
        {
            for each(auto jsonPlayer in jsonPlayers)
            {
                if (isMyPlayer(jsonPlayer))
                {
                    UpdatePlayer(m_pGame->getMyPlayer(), jsonPlayer);
                }
                else
                {
                    UpdatePlayer(m_pGame->getOtherPlayer(), jsonPlayer);
                }
            }
        }

        void    UpdatePlayer(std::shared_ptr<BotWarz::Player> io_pPlayer, const Json::Value& jsonPlayer)
        {
            const char* jsonKeyBots = "bots";
            Json::Value jsonBots = jsonPlayer[jsonKeyBots];

            BotWarz::GameFactory    gameFactory(m_szNickName);
            auto vBots = gameFactory.createBots(jsonBots);

            if (vBots.size() == 0)
            {
                return;
            }

            io_pPlayer->setBots(vBots);
        }

        void    UpdateBot(std::shared_ptr<BotWarz::Player> io_pPlayer, const Json::Value& jsonBot)
        {
            const char* jsonKeyBotId = "id";
            const char* jsonKeyBotPositionX = "x";
            const char* jsonKeyBotPositionY = "y";
            const char* jsonKeyBotAngle = "angle";
            const char* jsonKeyBotSpeed = "speed";

            unsigned nBotId = jsonBot[jsonKeyBotId].asUInt();
            std::shared_ptr<BotWarz::Bot> pBot = io_pPlayer->getBot(nBotId);

            pBot->setPosition(
                Geometry::Point(
                    jsonBot[jsonKeyBotPositionX].asDouble(),
                    jsonBot[jsonKeyBotPositionY].asDouble()
                    )
                );

            pBot->setAngleInDegrees(
                jsonBot[jsonKeyBotAngle].asDouble()
                );

            pBot->setSpeed(
                jsonBot[jsonKeyBotSpeed].asDouble()
                );
        }

        virtual const char* GetMove()
        {
            auto moveMessage = Message::MoveBots(m_pGame, m_pGameStrategy);
            if (moveMessage != boost::none)
            {
                m_szMoveMessage = *moveMessage;
                return m_szMoveMessage.c_str();
            }
            else
            {
                return nullptr;
            }
        }

    private:
        std::shared_ptr<BotWarz::Strategy::Interface> createStrategy(
            const std::shared_ptr<BotWarz::Game> i_pGame
            )
        {
            //return std::make_shared<BotWarz::Strategy::NoCommands>();

            return std::make_shared<BotWarz::Strategy::AttackClosestBot>(
                i_pGame->getSpeedLevels(),
                i_pGame->getBotRadius(),
                i_pGame->getWorld(),
                m_pLogger
                );
        }

        std::string m_szNickName;
        std::shared_ptr<Game>   m_pGame;
        std::shared_ptr<BotWarz::Strategy::Interface> m_pGameStrategy;
        std::shared_ptr<Logger> m_pLogger;

        std::string m_szMoveMessage;
    };

    ApplicationInterface*    createApplication(
        const char* i_szNickName,
        std::shared_ptr<Logger> i_pLogger
        )
    {
        return new Application(i_szNickName,i_pLogger);
    }

    void deleteApplication(ApplicationInterface* pApplication)
    {
        delete pApplication;
    }

    ApplicationInterface::ApplicationInterface(const char* /*i_szNickName*/, std::shared_ptr<Logger> /*i_pLogger = nullptr*/)
    {
    }


    ApplicationInterface::~ApplicationInterface()
    {
    }

}
