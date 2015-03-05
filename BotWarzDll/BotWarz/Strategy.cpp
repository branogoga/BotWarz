#include "./Strategy.h"

#include "Bot.h"

#include <assert.h>

namespace BotWarz
{

    namespace {

        size_t  findClosestBot( const std::vector<std::shared_ptr<Bot>>& i_vBots, const Geometry::Point& i_pPoint )
        {
            std::vector<Geometry::Point>  vBotPositions;
            for each(auto bot in i_vBots)
            {
                vBotPositions.push_back(bot->getPosition());
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
            std::make_shared<GameCommandAccelerate>(bot->getId())
            );
    }

    return vCommands;
}

bool    isCollisionExpected(const std::shared_ptr<Bot> bot1, const std::shared_ptr<Bot> bot2)
{
    // Simply check intersection of two lines, if bots will not change direction nor speed.

    const double dTimeDelta = 250.0;

    const Geometry::Point bot1_start = bot1->getPosition();
    const Geometry::Point bot1_end = bot1->getFuturePosition(dTimeDelta);

    const Geometry::Point bot2_start = bot2->getPosition();
    const Geometry::Point bot2_end = bot2->getFuturePosition(dTimeDelta);

    return Geometry::doLinesIntersect(
        bot1_start, bot1_end,
        bot2_start, bot2_end
        );
}

double calculateMaxAttackAngleInDegrees( const double i_dBotRadius, const double i_dBotDistance )
{
    double x = 2 * i_dBotRadius + i_dBotDistance;
    double y = i_dBotRadius;
    return Geometry::convertAngleFromRadiansToDegrees(atan2(x, y));
}

std::vector<std::shared_ptr<GameCommandBase>>    AttackTheClosestBot::getCommands(
    const std::shared_ptr<Player> pMyPlayer,
    const std::shared_ptr<Player> pOtherPlayer
    )
{
    std::vector<std::shared_ptr<GameCommandBase>>    vCommands;

    const std::vector<std::shared_ptr<Bot>>& vMyBots = pMyPlayer->getBots();
    for each(auto myBot in vMyBots)
    {
        //
        // Find closest enemy Bot
        //
        const std::vector<std::shared_ptr<Bot>>& vEnemyBots = pOtherPlayer->getBots();

        size_t  closestEnemyBotIndex = findClosestBot(vEnemyBots, myBot->getPosition());
        const std::shared_ptr<Bot> closestEnemyBot = vEnemyBots[closestEnemyBotIndex];

        std::cout << " Bot # " << myBot->getId() << " attacking enemy # " << closestEnemyBot->getId() << std::endl;

        //
        // Calculate distance and angle
        //
        double dTargetAngleInDegrees = Geometry::angleInDegrees(myBot->getPosition(), closestEnemyBot->getPosition());
        // To Do: Count with Bot radius.
        double dChangeInAngleInDegrees = dTargetAngleInDegrees - myBot->getAngleInDegrees();

        // Achieve to Bots were aligned in attack position in given time
        double dAttackTimeInseconds = 0.5;
        const double dMaxAttackAngle = calculateMaxAttackAngleInDegrees(
            m_dBotRadius, 
            (myBot->getSpeed() + closestEnemyBot->getSpeed()) * dAttackTimeInseconds
            );

        // +TEST+
        //{
        //    if (dChangeInAngleInDegrees > 10.0)
        //    {
        //        assert(myBot->getSpeed() >= getMinimalSpeed());

        //        double  dEnemyBotDistanceBeforeChangeApplied = Geometry::distance(
        //            myBot->getFuturePosition(),
        //            closestEnemyBot->getPosition()
        //            );

        //        BotWarz::Bot copyOfMyBot = *myBot;
        //        copyOfMyBot.adjustAngleInDegrees(dChangeInAngleInDegrees);

        //        double  dEnemyBotDistanceAfterChangeApplied = Geometry::distance(
        //            copyOfMyBot.getFuturePosition(),
        //            closestEnemyBot->getPosition()
        //            );

        //        //assert(dEnemyBotDistanceBeforeChangeApplied > dEnemyBotDistanceAfterChangeApplied);
        //    }
        //}
        // -TEST-

        //
        // If stuck near wall, change the angle and accelerate
        //
        if (myBot->getSpeed() < getMinimalSpeed())
        {
            std::cout << "Bot #" << myBot->getId() << " stuck to wall." << std::endl;

            BotWarz::Bot copyOfMyBot = *myBot;
            copyOfMyBot.setSpeed(getMinimalSpeed());
            Geometry::Point futurePosition = copyOfMyBot.getFuturePosition();
            if (m_pWorld->isInside(futurePosition.x(), futurePosition.y(), m_dBotRadius))
            {
                vCommands.push_back(
                    std::make_shared<GameCommandAccelerate>(myBot->getId())
                    );
            }
            else
            {
                vCommands.push_back(
                    std::make_shared<GameCommandSteer>(myBot->getId(), getMaxAngle(getMinimalSpeed()))
                    );
            }
        }

        //
        // Attack!
        //
        bool    isAlignedInAttackPosition = (dChangeInAngleInDegrees < dMaxAttackAngle);
        std::cout << " Bot #" << myBot->getId() << " is aligned in attack position.";
        if (isAlignedInAttackPosition)
        {
            if (isMaximalSpeed(myBot->getSpeed()))
            {
                std::cout << "Steer! (" << dChangeInAngleInDegrees << " degrees )" << std::endl;
                vCommands.push_back(
                    std::make_shared<GameCommandSteer>(myBot->getId(), dChangeInAngleInDegrees)
                    );
                continue;
            }
            else
            {
                std::cout << " Accelerate!" << std::endl;
                vCommands.push_back(
                    std::make_shared<GameCommandAccelerate>(myBot->getId())
                    );
                continue;
            }
        }

        // Brake or steer?
        std::cout << "Bad position. ";

        if ((getMaxAngle(myBot->getSpeed()) < dChangeInAngleInDegrees) 
            && !isMinimalSpeed(myBot->getSpeed())
            && (myBot->getSpeed() < getMinimalSpeed()) // Stucked near the wall
            )
        {
            std::cout << " Break! " << std::endl;
            vCommands.push_back(
                std::make_shared<GameCommandBrake>(myBot->getId())
                );
            continue;
        }

        std::cout << "Steer! (" << dChangeInAngleInDegrees << " degrees )" << std::endl;
        vCommands.push_back(
            std::make_shared<GameCommandSteer>(myBot->getId(), dChangeInAngleInDegrees)
            );

        //// 3. Avoid collisions with own Bots
        //bool bIsCollisionExpected = false;
        //for each(auto bot in pMyPlayer->getBots())
        //{
        //    if (bot->getId() != myBot->getId())
        //    {
        //        if (isCollisionExpected(bot, myBot))
        //        {
        //            bIsCollisionExpected = true;
        //            break;
        //        }
        //    }
        //}

        //
        //// Find closest enemy Bot distance.
        ////
        //double  dClosestEnemyBotDistance = Geometry::distance(
        //    myBot->getPosition(),
        //    closestEnemyBot->getPosition()
        //    );

        //double dTimeDeltaInMilliseconds = 500.0;
        //double dMyBotTrajectoryLength = myBot->getSpeed() * dTimeDeltaInMilliseconds / 1000.0;
        //double dEnemyBotTrajectoryLength = closestEnemyBot->getSpeed() * dTimeDeltaInMilliseconds / 1000.0;

        // To Do: Count also Bot radius!

        // To Do: Is some enemy close and not minimal speed? Brake!
    }

    return vCommands;
}

double  AttackTheClosestBot::getMaxAngle(double i_dSpeed, const double i_dDefaultAngle) const
{
    for each(auto speedLevel in m_vSpeedLevels)
    {
        if (speedLevel.getSpeed() == i_dSpeed)
        {
            return speedLevel.getMaxAngle();
        }
    }

    return i_dDefaultAngle;
    //throw std::invalid_argument("Invalid speed level.");
}

bool    AttackTheClosestBot::isMinimalSpeed(double i_dSpeed) const
{
    for each(auto speedLevel in m_vSpeedLevels)
    {
        if (speedLevel.getSpeed() < i_dSpeed)
        {
            return false;
        }
    }

    return true;
}

double  AttackTheClosestBot::getMinimalSpeed() const
{
    double dMinimalSpeed = m_vSpeedLevels[0].getSpeed();
    for each(auto speedLevel in m_vSpeedLevels)
    {
        if (speedLevel.getSpeed() < dMinimalSpeed)
        {
            dMinimalSpeed = speedLevel.getSpeed();
        }
    }

    return dMinimalSpeed;
}

bool    AttackTheClosestBot::isMaximalSpeed(double i_dSpeed) const
{
    for each(auto speedLevel in m_vSpeedLevels)
    {
        if (speedLevel.getSpeed() > i_dSpeed)
        {
            return false;
        }
    }

    return true;
}

}//namespace BotWarz
