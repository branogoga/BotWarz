#include "./Strategy.h"

#include "Bot.h"

namespace BotWarz
{

    namespace {

        size_t  findClosestBot( const std::vector<Bot>& i_vBots, const Geometry::Point& i_pPoint )
        {
            std::vector<Geometry::Point>  vBotPositions;
            for each(auto bot in i_vBots)
            {
                vBotPositions.push_back(bot.getPosition());
            }

            return Geometry::closestPointIndex(vBotPositions, i_pPoint);
        }

    }//anonymous namespace

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

std::vector<std::shared_ptr<GameCommandBase>>    AttackTheClosestBot::getCommands(
    const std::shared_ptr<Player> pMyPlayer,
    const std::shared_ptr<Player> pOtherPlayer
    )
{
    std::vector<std::shared_ptr<GameCommandBase>>    vCommands;

    for each(auto myBot in pMyPlayer->getBots())
    {
        // 1. Find closest enemy Bot
        const std::vector<Bot>& vEnemyBots = pOtherPlayer->getBots();

        size_t  closestEnemyBotIndex = findClosestBot(vEnemyBots, myBot.getPosition());
        const Bot& closestEnemyBot = vEnemyBots[closestEnemyBotIndex];

        // 2. Calculate distance and angle
        double dTargetAngle = Geometry::angle(myBot.getPosition(), closestEnemyBot.getPosition());
        double dChangeInAngle = dTargetAngle - myBot.getAngle();

        // 3. Find best speed & angle

        // 4. Create command
        vCommands.push_back(
            std::make_shared<GameCommandSteer>(myBot.getId(), dChangeInAngle)
            );
    }

    return vCommands;
}

}//namespace BotWarz
