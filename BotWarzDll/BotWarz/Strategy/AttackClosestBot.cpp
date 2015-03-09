#include "./AttackClosestBot.h"
#include "./Strategy.h"

#include "BotWarz/Bot.h"
#include "BotWarz/Player.h"
#include "BotWarz/SpeedLevel.h"
#include "BotWarz/World.h"
#include "BotWarz/Command/Accelerate.h"
#include "BotWarz/Command/Brake.h"
#include "BotWarz/Command/Steer.h"

#include <assert.h>

namespace BotWarz {

    namespace Strategy {

        std::vector<std::shared_ptr<Command::Interface>>    
        AttackClosestBot::getCommands(
            const std::shared_ptr<Player> pMyPlayer,
            const std::shared_ptr<Player> pOtherPlayer
            )
        {
            std::vector<std::shared_ptr<Command::Interface>>    vCommands;

            const std::vector<std::shared_ptr<Bot>>& vMyBots = pMyPlayer->getBots();
            for each(auto myBot in vMyBots)
            {
                //
                // Find closest enemy Bot
                //
                const std::vector<std::shared_ptr<Bot>>& vEnemyBots = pOtherPlayer->getBots();

                std::unique_ptr<Strategy::FindEnemyBotPolicyInterface> pEnemyBotFinder =
                    //std::make_unique<Strategy::FindClosestBotPolicy>();
                    std::make_unique<Strategy::FindMostReachableBotPolicy>(m_vSpeedLevels);
                size_t  closestEnemyBotIndex = pEnemyBotFinder->getBotIndex(myBot, vEnemyBots);
                const std::shared_ptr<Bot> closestEnemyBot = vEnemyBots[closestEnemyBotIndex];

                std::cout << " Bot # " << myBot->getId() << " attacking enemy # " << closestEnemyBot->getId() << std::endl;

                // Calculate chasing target point
                std::unique_ptr<ChasingPolicyInterface> pChasingStrategy =
                    std::make_unique<CurrentPositionChasingPolicy>(closestEnemyBot);
                //std::make_unique<FuturePositionChasingPolicy>(closestEnemyBot);

                Geometry::Point targetPosition = pChasingStrategy->getDestinationPoint();

                // Calculate distance and angle
                //double dDistanceToTarget = Geometry::distance( targetPosition, myBot->getPosition());
                double dTargetAngleInDegrees = Geometry::angleInDegrees(myBot->getPosition(), targetPosition);
                double dChangeInAngleInDegrees = Geometry::normalizeAngleInDegrees(dTargetAngleInDegrees - myBot->getAngleInDegrees());

                //
                // If stuck near wall, change the angle and accelerate
                //
                if (myBot->getSpeed() < getMinimalSpeed(m_vSpeedLevels))
                {
                    std::cout << "Bot #" << myBot->getId() << " stuck to wall." << std::endl;

                    BotWarz::Bot copyOfMyBot = *myBot;
                    copyOfMyBot.setSpeed(getMinimalSpeed(m_vSpeedLevels));
                    Geometry::Point futurePosition = copyOfMyBot.getFuturePosition();

                    // If I will not hit the wall, so I`m turned out of the wall, but still zero speed ...
                    if (m_pWorld->isInside(futurePosition.x(), futurePosition.y(), m_dBotRadius))
                    {
                        vCommands.push_back(
                            std::make_shared<Command::Accelerate>(myBot->getId())
                            );
                    }
                    else
                    {
                        // Turned to the wall
                        int sign = (dChangeInAngleInDegrees >= 0.0) ? +1 : -1;

                        double dAngle = sign * getMaxAngle(
                            m_vSpeedLevels,
                            getMinimalSpeed(m_vSpeedLevels)
                            );

                        vCommands.push_back(
                            std::make_shared<Command::Steer>(
                                myBot->getId(),
                                dAngle  
                            )
                            );
                        break;
                    }
                }

                ////
                //// Avoid collisions with own Bots
                ////
                //for each(auto bot in pMyPlayer->getBots())
                //{
                //    if (bot->getId() != myBot->getId())
                //    {
                //        if (isCollisionExpected(*bot, *myBot, 250.0))
                //        {
                //            std::cout << "Possible collision of bot #" << bot->getId() << "with own bot #" << myBot->getId() << "!";

                //            double dAngle = getMaxAngle(m_vSpeedLevels, myBot->getSpeed());
                //            std::cout << "Steer! (" << dAngle << " degrees )" << std::endl;
                //            vCommands.push_back(
                //                std::make_shared<Command::Steer>(myBot->getId(), dAngle)
                //                );

                //            break;
                //        }
                //    }
                //}

                //
                // Attack!
                //

                // Achieve to Bots were aligned in attack position in given time
                double dAttackTimeInseconds = 0.5;
                const double dMaxAttackAngle = calculateMaxAttackAngleInDegrees(
                    m_dBotRadius,
                    (myBot->getSpeed() + closestEnemyBot->getSpeed()) * dAttackTimeInseconds
                    );

                //const   double dTimeDeltaInMilliseconds = 200.0;
                bool    isAlignedInAttackPosition = (fabs(dChangeInAngleInDegrees) < dMaxAttackAngle);
                std::cout << " Bot #" << myBot->getId() << " is aligned in attack position.";
                if (isAlignedInAttackPosition)
                {
                    //double dCloseEnoughtDistance = 5 * myBot->getSpeed()*(dTimeDeltaInMilliseconds / 1000.0);
                    if (isMaximalSpeed(m_vSpeedLevels, myBot->getSpeed()) 
                        //&& (dDistanceToTarget < dCloseEnoughtDistance)
                        )
                    {
                        std::cout << "Steer! (" << dChangeInAngleInDegrees << " degrees )" << std::endl;
                        vCommands.push_back(
                            std::make_shared<Command::Steer>(myBot->getId(), dChangeInAngleInDegrees)
                            );
                        continue;
                    }
                    else
                    {
                        std::cout << " Accelerate!" << std::endl;
                        vCommands.push_back(
                            std::make_shared<Command::Accelerate>(myBot->getId())
                            );
                        continue;
                    }
                }

                // Brake or steer?
                std::cout << "Bad position. ";

                if ((getMaxAngle(m_vSpeedLevels, myBot->getSpeed()) < dChangeInAngleInDegrees)
                    && !isMinimalSpeed(m_vSpeedLevels, myBot->getSpeed())
                    && (myBot->getSpeed() < getMinimalSpeed(m_vSpeedLevels)) // Stucked near the wall
                    )
                {
                    std::cout << " Break! " << std::endl;
                    vCommands.push_back(
                        std::make_shared<Command::Brake>(myBot->getId())
                        );
                    continue;
                }

                std::cout << "Steer! (" << dChangeInAngleInDegrees << " degrees )" << std::endl;
                vCommands.push_back(
                    std::make_shared<Command::Steer>(myBot->getId(), dChangeInAngleInDegrees)
                    );
            }

            return vCommands;
        }

    }//namespace Strategy
}//namespace Botwarz