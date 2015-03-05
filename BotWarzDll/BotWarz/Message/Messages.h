#pragma once

#include "BotWarz/Bot.h"
#include "BotWarz/Game.h"
#include "BotWarz/Player.h"
#include "BotWarz/Strategy.h"
#include "jsoncpp/include/json/json.h"

#include <string>
#include <vector>

namespace Message
{
    std::unique_ptr<BotWarz::StrategyInterface> createStrategy( const std::shared_ptr<BotWarz::Game> i_pGame )
    {
        //return std::make_unique<BotWarz::AlwaysAccelerateStrategy>();

        return std::make_unique<BotWarz::AttackTheClosestBot>(
            i_pGame->getSpeedLevels(),
            i_pGame->getBotRadius(),
            i_pGame->getWorld()
            );
    }

    std::string MoveBots(
        const std::shared_ptr<BotWarz::Game>& pGame
        )
    {
        const char* jsonKeyBots = "bots";

        // our tactics is to crush enemies before they notice something...
        auto  pStrategy = createStrategy(pGame);
        auto commands = pStrategy->getCommands(pGame->getMyPlayer(), pGame->getOtherPlayer());

        // serialize to Json
        Json::Value root;
        root[jsonKeyBots] = Json::Value(Json::arrayValue);

        //std::cout << "Sengind MoveBots command:" << std::endl;
        for each(auto command in commands)
        {
            //std::cout << (*command);
            Json::Value jsonCommand = command->toJson();
            root[jsonKeyBots].append(jsonCommand);
        }
        //std::cout << std::endl;

        Json::FastWriter writer;
        return writer.write(root);
    }
};

