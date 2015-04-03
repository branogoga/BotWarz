#include "./AttackClosestBot.h"
#include "./Strategy.h"

#include "BotWarz/Bot.h"
#include "BotWarz/Game.h"
#include "BotWarz/Player.h"
#include "BotWarz/SpeedLevel.h"
#include "BotWarz/World.h"
#include "BotWarz/Command/Accelerate.h"
#include "BotWarz/Command/Brake.h"
#include "BotWarz/Command/Steer.h"
#include "Geometry/Angle.h"
#include "Geometry/Line.h"
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
                (std::make_unique<Strategy::FindMostReachableBotPolicy>(m_vSpeedLevels));
                //(std::make_unique<Strategy::FindClosestBotPolicy>());

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

            double maxSteerableAngle = stepToReachDirectionInCurrentSpeed * getMaxAngularSpeed(i_vSpeedLevels, i_dMySpeed);

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
                        Geometry::Line(
                            myBot->getPosition(),
                            closestEnemyBot->getPosition()
                            )
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
                            double dAngle = getMaxAngularSpeed(vSpeedLevels, myBot->getSpeed());

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

                std::shared_ptr<Command::Interface>    pCommand = chaseBot(
                    myBot,
                    closestEnemyBot,
                    pMyPlayer,
                    m_pLogger
                    );

                if (pCommand != nullptr)
                {
                    vCommands.push_back( pCommand );
                }
            }

            return vCommands;
        }

        std::shared_ptr<Command::Interface> AttackClosestBot::chaseBot(
            std::shared_ptr<Bot> myBot,
            std::shared_ptr<Bot> enemyBot,
            const std::shared_ptr<Player> i_pMyPlayer,
            std::shared_ptr<Logger> pLogger
            )
        {
            if (pLogger)
            {
                *pLogger << " Bot # " << myBot->getId() << " attacking enemy # " << enemyBot->getId() << std::endl;
            }

            // Calculate chasing target point
            Geometry::Point targetPosition = m_chasingStrategyPolicy->getDestinationPoint(enemyBot);

            // Calculate distance and angle
            double dTargetAngleInDegrees = Geometry::angleInDegrees(myBot->getPosition(), targetPosition);
            double dChangeInAngleInDegrees = Geometry::normalizeAngleInDegrees(dTargetAngleInDegrees - myBot->getAngleInDegrees());

            if (pLogger)
            {
                *pLogger << " Angle from current to enemy: " << dChangeInAngleInDegrees << std::endl;
            }

            //
            // If stuck near wall, change the angle and accelerate
            //
            if (Strategy::isStuckedNearTheWall(
                myBot, m_pWorld, m_vSpeedLevels, m_dBotRadius
                ))
            {
                if (pLogger)
                {
                    *pLogger << " Bot #" << myBot->getId() << " is stucked near the wall." << std::endl;
                }

                // Turned to the wall
                int sign = (dChangeInAngleInDegrees >= 0.0) ? +1 : -1;

                double dAngle = sign * getMaxAngularSpeed(
                    m_vSpeedLevels,
                    getMinimalSpeed(m_vSpeedLevels)
                    );

                if (pLogger)
                {
                    *pLogger << " Steer " << dAngle << " degrees." << std::endl;
                }

                return std::make_shared<Command::Steer>(
                    myBot,
                    dAngle
                    );
            }

            //
            // Avoid own static Bot collisions
            //
            std::shared_ptr<Command::Interface> pAvoidCollisionCommand =
                avoidStaticBotCollisions(
                myBot, enemyBot, i_pMyPlayer->getBots(), m_dBotRadius, m_vSpeedLevels, m_pLogger
                );
            if (pAvoidCollisionCommand)
            {
                return pAvoidCollisionCommand;
            }

            //
            // Attack!
            //

            // Achieve to Bots were aligned in attack position in given time
            double dDistanceToTarget = Geometry::distance(targetPosition, myBot->getPosition());
            const double dMaxAttackAngle = calculateMaxAttackAngleInDegrees(
                m_dBotRadius,
                dDistanceToTarget
                );

            if (pLogger)
            {
                *pLogger << " Max attack angle = " << dMaxAttackAngle << std::endl;
            }

            bool isAlignedInAttackPosition = fabs(dChangeInAngleInDegrees) < dMaxAttackAngle;
            if (isAlignedInAttackPosition
                && (!isMaximalSpeed(m_vSpeedLevels, myBot->getSpeed())))
            {
                // If enemy Bot is turned in attack position and is close enought, do not send any command.
                // Rather save time, wait for collision and react sooner in next round, so possibly can won 
                // the next match.
                if (Strategy::isBotAlignedWithAttackZone(myBot, enemyBot))
                {
                    return nullptr;
                }

                if (pLogger)
                {
                    *pLogger << " Aligned in attack position. Accelerate!" << std::endl;
                }

                return std::make_shared<Command::Accelerate>(
                    myBot,
                    m_vSpeedLevels
                    );
            }

            bool bCanSteer = canSteerAngleAtGivenSpeed(
                dChangeInAngleInDegrees,
                myBot->getSpeed(),
                enemyBot->getSpeed(),
                dDistanceToTarget,
                m_vSpeedLevels
                );

            if (pLogger)
            {
                *pLogger << " Distance to target = " << dDistanceToTarget << std::endl;
            }

            if (!bCanSteer
                && !isMinimalSpeed(m_vSpeedLevels, myBot->getSpeed())
                && (myBot->getSpeed() > getMinimalSpeed(m_vSpeedLevels)) // Stucked near the wall
                )
            {
                if (pLogger)
                {
                    *pLogger << " Can`t steer at this speed. Brake." << std::endl;
                }

                return std::make_shared<Command::Brake>(
                    myBot,
                    m_vSpeedLevels
                    );
            }

            if (pLogger)
            {
                *pLogger << " Steer " << dChangeInAngleInDegrees << "degrees." << std::endl;
            }

            return std::make_shared<Command::Steer>(myBot, dChangeInAngleInDegrees);
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