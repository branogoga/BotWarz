#include "./GameFactory.h"

#include "Bot.h"
#include "Game.h"
#include "jsoncpp/include/json/json.h"
#include "Player.h"
#include "SpeedLevel.h"
#include "World.h"

#include <algorithm>
#include <memory>

namespace BotWarz
{

    GameFactory::GameFactory(const std::string& i_szNickName)
        : m_szNickName(i_szNickName)
    {
    }


    GameFactory::~GameFactory()
    {
    }

    std::shared_ptr<Game>   GameFactory::createFromJson(const Json::Value& jsonGame)
    {
        return createGame(jsonGame);
    }

    std::shared_ptr<BotWarz::World> GameFactory::createWorld(const Json::Value& jsonWorld)
    {
        const char* jsonKeyWorldWidth = "width";
        const char* jsonKeyWorldHeight = "height";

        auto pWorld = std::make_shared<BotWarz::World>(
            jsonWorld[jsonKeyWorldWidth].asUInt(),
            jsonWorld[jsonKeyWorldHeight].asUInt()
            );

        return pWorld;
    }

    BotWarz::SpeedLevel     GameFactory::createSpeedLevel(const Json::Value& jsonSpeedLevel)
    {
        const char* jsonKeySpeedLevelSpeed = "speed";
        const char* jsonKeySpeedLevelMaxAngle = "maxAngle";

        return BotWarz::SpeedLevel(
            jsonSpeedLevel[jsonKeySpeedLevelSpeed].asDouble(),
            jsonSpeedLevel[jsonKeySpeedLevelMaxAngle].asDouble()
            );
    }

    std::vector<BotWarz::SpeedLevel>    GameFactory::createSpeedLevels(const Json::Value& jsonSpeedLevels)
    {
        if (!jsonSpeedLevels.isArray())
        {
            throw std::invalid_argument("Speed level must be an array.");
        }

        std::vector<BotWarz::SpeedLevel>    vSpeedLevels;
        for each (auto  jsonSpeedLevel in jsonSpeedLevels)
        {
            vSpeedLevels.push_back(
                createSpeedLevel(jsonSpeedLevel)
                );
        }

        std::sort(
            vSpeedLevels.begin(),
            vSpeedLevels.end()
            );

        return vSpeedLevels;
    }


    std::shared_ptr<BotWarz::Bot>    GameFactory::createBot(const Json::Value& jsonBot)
    {
        const char* jsonKeyBotId = "id";
        const char* jsonKeyBotPositionX = "x";
        const char* jsonKeyBotPositionY = "y";
        const char* jsonKeyBotAngle = "angle";
        const char* jsonKeyBotSpeed = "speed";

        auto bot = std::make_shared<BotWarz::Bot>(jsonBot[jsonKeyBotId].asUInt());
        bot->setPosition(
            Geometry::Point(
            jsonBot[jsonKeyBotPositionX].asDouble(),
            jsonBot[jsonKeyBotPositionY].asDouble()
            )
            );
        bot->setAngleInDegrees(jsonBot[jsonKeyBotAngle].asDouble());
        bot->setSpeed(jsonBot[jsonKeyBotSpeed].asDouble());

        return bot;
    }

    bool    GameFactory::isMyPlayer(const Json::Value& jsonPlayer)
    {
        const char* jsonKeyPlayerNickName = "nickname";
        return jsonPlayer[jsonKeyPlayerNickName].asString() == m_szNickName;
    }

    std::shared_ptr<BotWarz::Player>    GameFactory::createPlayer(const Json::Value& jsonPlayer)
    {
        const char* jsonKeyPlayerNickName = "nickname";
        const char* jsonKeyPlayerBots = "bots";

        auto pPlayer = std::make_shared<BotWarz::Player>(
            jsonPlayer[jsonKeyPlayerNickName].asString()
            );

        pPlayer->setBots(
            createBots(jsonPlayer[jsonKeyPlayerBots])
            );

        return pPlayer;
    }

    std::shared_ptr<BotWarz::Game> GameFactory::createGame(const Json::Value& jsonGame)
    {
        const char* jsonKeyGameTime = "time";
        const char* jsonKeyBotRadius = "botRadius";
        const char* jsonKeyWorld = "world";
        const char* jsonKeySpeedLevels = "speedLevels";
        const char* jsonKeyPlayers = "players";

        auto pWorld = createWorld(jsonGame[jsonKeyWorld]);
        auto vSpeedLevels = createSpeedLevels(jsonGame[jsonKeySpeedLevels]);

        auto pGame = std::make_shared<BotWarz::Game>(
            pWorld,
            vSpeedLevels,
            jsonGame[jsonKeyBotRadius].asDouble()
            );
        pGame->setTime(jsonGame[jsonKeyGameTime].asDouble());

        std::shared_ptr<BotWarz::Player>    pMyPlayer;
        std::shared_ptr<BotWarz::Player>    pOtherPlayer;

        Json::Value jsonPlayers = jsonGame[jsonKeyPlayers];
        for each(auto jsonPlayer in jsonPlayers)
        {
            auto pPlayer = createPlayer(jsonPlayer);
            if (isMyPlayer(jsonPlayer))
            {
                pGame->setMyPlayer(pPlayer);
            }
            else
            {
                pGame->setOtherPlayer(pPlayer);
            }
        }

        return pGame;
    }


    std::vector<std::shared_ptr<BotWarz::Bot>>   GameFactory::createBots(const Json::Value& jsonBots)
    {
        std::vector<std::shared_ptr<BotWarz::Bot>>   vBots;
        for each (auto  jsonBot in jsonBots)
        {
            vBots.push_back(
                createBot(jsonBot)
                );
        }

        return vBots;
    }

}//namespace BotWarz

