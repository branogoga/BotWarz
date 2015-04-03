#pragma once

#include "StdAfx.h"


#include "boost/noncopyable.hpp"

#include <memory>
#include <vector>

namespace Json {
    class Value;
}

namespace BotWarz {

    class Bot;
    class Game;
    class Player;
    class SpeedLevel;
    class World;

    class  GameFactory : public boost::noncopyable
    {
    public:
        GameFactory(const std::string i_szNickName);
        virtual ~GameFactory();

        std::shared_ptr<Game>   createFromJson(const Json::Value& jsonGame);
        std::vector<std::shared_ptr<Bot>>   createBots(const Json::Value& jsonBots, const std::vector<SpeedLevel>& vSpeedLevels);

    private:
        std::shared_ptr<World> createWorld(const Json::Value& jsonWorld);
        std::vector<SpeedLevel>    createSpeedLevels(const Json::Value& jsonSpeedLevels);
        SpeedLevel     createSpeedLevel(const Json::Value& jsonSpeedLevel);
        std::shared_ptr<Bot>    createBot(const Json::Value& jsonBot, const std::vector<SpeedLevel>& vSpeedLevels);
        bool    isMyPlayer(const Json::Value& jsonPlayer);
        std::shared_ptr<Player>    createPlayer(const Json::Value& jsonPlayer, const std::vector<SpeedLevel>& vSpeedLevels);
        std::shared_ptr<Game> createGame(const Json::Value& jsonGame);

        const std::string     m_szNickName;
    };

}