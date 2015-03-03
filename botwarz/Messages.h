#pragma once

#include "Bot.h"
#include "jsoncpp/include/json/json.h"
#include "Player.h"
#include "Strategy.h"

#include <string>
#include <vector>

namespace Message
{
	std::string Connect(const char *name, const char *hash)
	{
		Json::Value root;
		root["login"]["nickname"] = name;
		root["login"]["hash"] = hash;

		Json::FastWriter writer;
		return writer.write(root);
	}

    std::unique_ptr<BotWarz::StrategyInterface> createStrategy()
    {
        return std::make_unique<BotWarz::AlwaysAccelerateStrategy>();
    }

    std::string MoveBots(
        const std::shared_ptr<BotWarz::Player>& pMyPlayer,
        const std::shared_ptr<BotWarz::Player>& pOtherPlayer
        )
    {
        const char* jsonKeyBots = "bots";

        // our tactics is to crush enemies before they notice something...
        auto  pStrategy = createStrategy();
        auto commands = pStrategy->getCommands(pMyPlayer, pOtherPlayer);

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

