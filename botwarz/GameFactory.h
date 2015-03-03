#pragma once

#include <memory>

namespace Json {
    class Value;
}

namespace BotWarz {

    class Game;

    class GameFactory
    {
    public:
        GameFactory();
        virtual ~GameFactory();

        std::shared_ptr<Game>   createFromJson(const Json::Value& jsonGame);
    };

}