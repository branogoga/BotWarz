#include "./AttackClosestBot.h"
#include "./Strategy.h"

#include "BotWarz/Bot.h"
#include "BotWarz/Player.h"
#include "BotWarz/SpeedLevel.h"
#include "BotWarz/World.h"
#include "BotWarz/Command/Accelerate.h"
#include "BotWarz/Command/Brake.h"
#include "BotWarz/Command/Steer.h"
#include "Logger.h"

#include <assert.h>

namespace BotWarz {

    namespace Strategy {

        AttackClosestBot::AttackClosestBot(
            const std::vector<SpeedLevel>& i_vSpeedLevels,
            const double i_dBotRadius,
            const std::shared_ptr<World> i_pWorld,
            std::shared_ptr<Logger> i_pLogger
            ) 
            : m_vSpeedLevels(i_vSpeedLevels)
            , m_dBotRadius(i_dBotRadius)
            , m_pWorld(i_pWorld)
            , m_pLogger(i_pLogger)
        {
            m_enemyBotFinderPolicy = 
                //(std::make_unique<Strategy::FindMostReachableBotPolicy>(m_vSpeedLevels));
                (std::make_unique<Strategy::FindClosestBotPolicy>());

            m_chasingStrategyPolicy =
                std::make_unique<CurrentPositionChasingPolicy>();
                //std::make_unique<FuturePositionChasingPolicy>();
        }

        AttackClosestBot::~AttackClosestBot()
        {
        }

        bool canSteerAngleAtGivenSpeed(
            double i_dAngleToSteer,
            double i_dMySpeed,
            double i_dEnemySpeed,
            double i_dDistanceToTarget,
            const std::vector<SpeedLevel>&   i_vSpeedLevels
            )
        {
            double dTimeStep = 250.0;//ms
            double pixelsInOneStep = ((i_dMySpeed + i_dEnemySpeed) * dTimeStep / 1000.0);
            double  stepToReachDirectionInCurrentSpeed =
                //1.0;
                i_dDistanceToTarget / pixelsInOneStep;

            double maxSteerableAngle = stepToReachDirectionInCurrentSpeed * getMaxAngle(i_vSpeedLevels, i_dMySpeed);

            bool canSteer = (maxSteerableAngle >    fabs(i_dAngleToSteer));
            return canSteer;
        }

        std::shared_ptr<Command::Interface>
        avoidStaticBotCollisions(
            std::shared_ptr<Bot> myBot,
            std::shared_ptr<Bot> closestEnemyBot,
            const std::vector<std::shared_ptr<Bot>>& vMyBots,
            double m_dBotRadius,
            const std::vector<SpeedLevel>& vSpeedLevels,
            std::shared_ptr<Logger> pLogger
        )
        {
            //
            // Avoid static Bot collisions
            //
            for each(auto bot in vMyBots)
            {
                if (bot->getId() != myBot->getId())
                {
                    double distanceToMeToEnemyLine =
                        Geometry::pointToLineDistance(
                        bot->getPosition(),
                        myBot->getPosition(),
                        closestEnemyBot->getPosition()
                        );

                    bool    bStaysInBetweenMeAndEnemy =
                        (distanceToMeToEnemyLine < 1.2*m_dBotRadius);

                    if (bStaysInBetweenMeAndEnemy)
                    {
                        if (pLogger)
                        {
                            *pLogger << " Own bot #" << bot->getId() << " stays between attacking bot #" << myBot->getId() << " and enemy bot #" << closestEnemyBot->getId() << std::endl;
                        }

                        // Brake or steer.
                        // To Do: Find another target.
                        if (isMinimalSpeed(vSpeedLevels, myBot->getSpeed()))
                        {
                            double dAngle = getMaxAngle(vSpeedLevels, myBot->getSpeed());

                            if (pLogger)
                            {
                                *pLogger << " Steer " << dAngle << std::endl;
                            }

                            return std::make_shared<Command::Steer>(
                                myBot,
                                dAngle
                            );
                        }
                        else
                        {
                            if (pLogger)
                            {
                                *pLogger << " Brake. " << std::endl;
                            }

                            return std::make_shared<Command::Brake>(
                                myBot,
                                vSpeedLevels
                                );
                        }
                    }
                }
            }

            return nullptr; // No collision
        }


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

                size_t  closestEnemyBotIndex = m_enemyBotFinderPolicy->getBotIndex(myBot, vEnemyBots);
                const std::shared_ptr<Bot> closestEnemyBot = vEnemyBots[closestEnemyBotIndex];

                if (m_pLogger)
                {
                    *m_pLogger << " Bot # " << myBot->getId() << " attacking enemy # " << closestEnemyBot->getId() << std::endl;
                }

                // Calculate chasing target point
                Geometry::Point targetPosition = m_chasingStrategyPolicy->getDestinationPoint(closestEnemyBot);

                // Calculate distance and angle
                double dTargetAngleInDegrees = Geometry::angleInDegrees(myBot->getPosition(), targetPosition);
                double dChangeInAngleInDegrees = Geometry::normalizeAngleInDegrees(dTargetAngleInDegrees - myBot->getAngleInDegrees());

                if (m_pLogger)
                {
                    *m_pLogger << " Angle from current to enemy: " << dChangeInAngleInDegrees << std::endl;
                }

                //
                // If stuck near wall, change the angle and accelerate
                //
                if (Strategy::isStuckedNearTheWall(
                    myBot, m_pWorld, m_vSpeedLevels, m_dBotRadius
                    ))
                {
                    if (m_pLogger)
                    {
                        *m_pLogger << " Bot #" << myBot->getId() << " is stucked near the wall." << std::endl;
                    }

                    // Turned to the wall
                    int sign = (dChangeInAngleInDegrees >= 0.0) ? +1 : -1;

                    double dAngle = sign * getMaxAngle(
                        m_vSpeedLevels,
                        getMinimalSpeed(m_vSpeedLevels)
                        );

                    if (m_pLogger)
                    {
                        *m_pLogger << " Steer " << dAngle << " degrees." << std::endl;
                    }

                    vCommands.push_back(
                        std::make_shared<Command::Steer>(
                            myBot,
                            dAngle  
                        )
                        );
                    continue;
                }

                //if (myBot->getSpeed() < getMinimalSpeed(m_vSpeedLevels))
                //{
                //    std::cout << " Accelerate!" << std::endl;
                //    vCommands.push_back(
                //        std::make_shared<Command::Accelerate>(
                //        myBot,
                //        m_vSpeedLevels
                //        )
                //        );
                //    continue;
                //}

                ////
                //// Avoid collisions with own Bots
                ////
                //for each(auto bot in pMyPlayer->getBots())
                //{
                //    if (bot->getId() != myBot->getId())
                //    {
                //        const double dTimeDelta = 500.0;
                //        if (isCollisionExpected(*bot, *myBot, dTimeDelta))
                //        {
                //            std::cout << "Possible collision of bot #" << bot->getId() << "with own bot #" << myBot->getId() << "!";

                //            const Geometry::Point bot1_start = bot->getPosition();
                //            const Geometry::Point bot1_end = bot->getFuturePosition(dTimeDelta);
                //            const Geometry::Point bot2_start = myBot->getPosition();
                //            const Geometry::Point bot2_end = myBot->getFuturePosition(dTimeDelta);

                //            double dOrientedAngle = Geometry::lineAngleInDegrees(bot1_start, bot1_end, bot2_start, bot2_end);
                //            //double sign = (fabs(dOrientedAngle) > 90.0) ? -1.0 : +1.0;
                //            double sign = (rand() % 2 == 0) ? -1.0 : +1.0;

                //            double dAngle = sign * getMaxAngle(m_vSpeedLevels, myBot->getSpeed());
                //            std::cout << "Steer! (" << dAngle << " degrees )" << std::endl;
                //            vCommands.push_back(
                //                std::make_shared<Command::Steer>(myBot, dAngle)
                //                );

                //            continue;
                //        }
                //    }
                //}

                //
                // Avoid own static Bot collisions
                //
                std::shared_ptr<Command::Interface> pAvoidCollisionCommand =
                    avoidStaticBotCollisions(
                    myBot, closestEnemyBot, vMyBots, m_dBotRadius, m_vSpeedLevels, m_pLogger
                    );
                if (pAvoidCollisionCommand)
                {
                    vCommands.push_back(pAvoidCollisionCommand);
                    continue;
                }

                //
                // Attack!
                //

                // Achieve to Bots were aligned in attack position in given time
                //double dAttackTimeInseconds = 0.5;

                //double dMySpeed = __max(myBot->getSpeed(), getMinimalSpeed(m_vSpeedLevels));
                //double dEnemySpeed = __max(closestEnemyBot->getSpeed(), getMinimalSpeed(m_vSpeedLevels));

                double dDistanceToTarget = Geometry::distance(targetPosition, myBot->getPosition());
                const double dMaxAttackAngle = calculateMaxAttackAngleInDegrees(
                    m_dBotRadius,
                    //(dMySpeed + dEnemySpeed / 2.0) * dAttackTimeInseconds
                    dDistanceToTarget
                    );

                if (m_pLogger)
                {
                    *m_pLogger << " Max attack angle = " << dMaxAttackAngle << std::endl;
                }

                bool isAlignedInAttackPosition = fabs(dChangeInAngleInDegrees) < dMaxAttackAngle;
                if (isAlignedInAttackPosition
                    && (!isMaximalSpeed(m_vSpeedLevels,myBot->getSpeed())))
                {
                    // If enemy Bot is turned in attack position and is close enought, do not send any command.
                    // Rather save time, wait for collision and react sooner in next round, so possibly can won 
                    // the next match.
                    if (Strategy::isBotAlignedWithAttackZone(myBot, closestEnemyBot))
                    {
                        continue;
                    }

                    if (m_pLogger)
                    {
                        *m_pLogger << " Aligned in attack position. Accelerate!" << std::endl;
                    }

                    vCommands.push_back(
                        std::make_shared<Command::Accelerate>(
                        myBot,
                        m_vSpeedLevels
                        )
                        );
                    continue;
                }

                bool bCanSteer = canSteerAngleAtGivenSpeed(
                    dChangeInAngleInDegrees,
                    myBot->getSpeed(),
                    closestEnemyBot->getSpeed(),
                    dDistanceToTarget,
                    m_vSpeedLevels
                    );

                if (m_pLogger)
                {
                    *m_pLogger << " Distance to target = " << dDistanceToTarget << std::endl;
                }

                if (!bCanSteer
                    && !isMinimalSpeed(m_vSpeedLevels, myBot->getSpeed())
                    && (myBot->getSpeed() > getMinimalSpeed(m_vSpeedLevels)) // Stucked near the wall
                    )
                {
                    if (m_pLogger)
                    {
                        *m_pLogger << " Can`t steer at this speed. Brake." << std::endl;
                    }

                    vCommands.push_back(
                        std::make_shared<Command::Brake>(
                            myBot,
                            m_vSpeedLevels
                            )
                        );
                    continue;
                }

                if (m_pLogger)
                {
                    *m_pLogger << " Steer " << dChangeInAngleInDegrees << "degrees." << std::endl;
                }

                vCommands.push_back(
                    std::make_shared<Command::Steer>(myBot, dChangeInAngleInDegrees)
                    );
            }

            return vCommands;
        }

        std::string AttackClosestBot::getName() const
        {
            return "AttackClosestBot-" 
                + m_enemyBotFinderPolicy->getName() + "-"
                + m_chasingStrategyPolicy->getName()
                ;
        }

    }//namespace Strategy
}//namespace Botwarz