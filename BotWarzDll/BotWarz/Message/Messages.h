#pragma once

#include "BotWarz/Bot.h"
#include "BotWarz/Game.h"
#include "BotWarz/Player.h"
#include "BotWarz/Command/Interface.h"
#include "BotWarz/Strategy/Interface.h"
#include "BotWarz/Strategy/AttackClosestBot.h"
#include "jsoncpp/include/json/json.h"

#include <string>
#include <vector>

namespace Message
{
    std::unique_ptr<BotWarz::Strategy::Interface> createStrategy( const std::shared_ptr<BotWarz::Game> i_pGame )
    {
        return std::make_unique<BotWarz::Strategy::AttackClosestBot>(
            i_pGame->getSpeedLevels(),
            i_pGame->getBotRadius(),
            i_pGame->getWorld()
            );
    }

    std::string MoveBots(
        const std::shared_ptr<BotWarz::Game>& pGame
        )
    {
        static unsigned nCommandId = 0;
        const char* jsonKeyBots = "bots";
        const char* jsonKeyCmdId = "cmdId";

        // our tactics is to crush enemies before they notice something...
        auto  pStrategy = createStrategy(pGame);
        auto commands = pStrategy->getCommands(pGame->getMyPlayer(), pGame->getOtherPlayer());

        // serialize to Json
        Json::Value root;
        root[jsonKeyCmdId] = nCommandId++;
        root[jsonKeyBots] = Json::Value(Json::arrayValue);

        //std::cout << "Sengind MoveBots command:" << std::endl;
        for each(auto command in commands)
        {
            //std::cout << (*command);
            Json::Value jsonCommand = command->toJson();
            root[jsonKeyBots].append(jsonCommand);
        }
        //std::cout << std::endl;

        // Apply commands
        for each(auto command in commands)
        {
            command->apply();
        }

        // Serialize to string
        Json::FastWriter writer;
        return writer.write(root);
    }
};

