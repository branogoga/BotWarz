#include "./Strategy.h"

#include "Bot.h"

namespace BotWarz
{

std::ostream& operator<<(std::ostream& out, const GameCommandBase& command)
{
    return command.toStream(out);
}

std::vector<std::shared_ptr<GameCommandBase>>    AlwaysAccelerateStrategy::getCommands(
    const std::shared_ptr<Player> pMyPlayer,
    const std::shared_ptr<Player> pOtherPlayer
    )
{
    std::vector<std::shared_ptr<GameCommandBase>>    vCommands;

    for each(auto bot in pMyPlayer->getBots())
    {
        vCommands.push_back(
            std::make_shared<GameCommandAccelerate>(bot.getId())
            );
    }

    return vCommands;
}

}//namespace BotWarz
