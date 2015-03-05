#include "stdafx.h"
#include "./Application.h"

#include "Bot.h"
#include "Game.h"
#include "GameFactory.h"
#include "BotWarz\Message\Messages.h"
#include "Player.h"

#include "jsoncpp/include/json/json.h"

namespace BotWarz 
{
    class Application : public ApplicationInterface
    {
    public:
        Application(const char* i_szNickName = "")
            : m_szNickName(i_szNickName)
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
            io_pPlayer->setBots(vBots);
            //for each(auto jsonBot in jsonBots)
            //{
            //    UpdateBot(io_pPlayer, jsonBot);
            //}

            //// To Do: Remove killed bots
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
            m_szMoveMessage = Message::MoveBots(m_pGame);
            return m_szMoveMessage.c_str();
        }

    private:
        std::string m_szNickName;
        std::shared_ptr<Game>   m_pGame;

        std::string m_szMoveMessage;
    };

    ApplicationInterface*    createApplication(const char* i_szNickName)
    {
        return new Application(i_szNickName);
    }

    void deleteApplication(ApplicationInterface* pApplication)
    {
        delete pApplication;
    }

    ApplicationInterface::ApplicationInterface(const char* /*i_szNickName*/)
    {
    }


    ApplicationInterface::~ApplicationInterface()
    {
    }

}
