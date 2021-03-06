#include "stdafx.h"

#include "./Strategy.h"

#include "BotWarz/Bot.h"
#include "BotWarz/Player.h"
#include "BotWarz/SpeedLevel.h"
#include "BotWarz/World.h"
#include "Geometry/Angle.h"
#include "Geometry/Line.h"

#include <assert.h>

namespace BotWarz {

    namespace Strategy {

        size_t  findClosestBot(const std::vector<std::shared_ptr<Bot>>& i_vBots, const Geometry::Point& i_pPoint)
        {
            std::vector<Geometry::Point>  vBotPositions;
            for each(auto bot in i_vBots)
            {
                vBotPositions.push_back(bot->getPosition());
            }

            return Geometry::closestPointIndex(vBotPositions, i_pPoint);
        }

        size_t  findMostReachableBot(
            const std::vector<std::shared_ptr<BotWarz::Bot>>& i_vBots,
            const std::shared_ptr<BotWarz::Bot> myBot,
            const std::vector<BotWarz::SpeedLevel>& i_vSpeedLevels
            )
        {
            unsigned nMinimalNumberOfStepsToReachBot = INT32_MAX;
            size_t nIndexWithMinimalStepsToReachBot = 0;
            unsigned nIndex = 0;
            for each(auto bot in i_vBots)
            {
                unsigned numberOfStepsToBot = numberOfStepsToReachPoint(myBot, bot->getPosition(), i_vSpeedLevels);
                if (numberOfStepsToBot < nMinimalNumberOfStepsToReachBot)
                {
                    nMinimalNumberOfStepsToReachBot = numberOfStepsToBot;
                    nIndexWithMinimalStepsToReachBot = nIndex;
                }
                nIndex++;
            }

            return (size_t)nIndexWithMinimalStepsToReachBot;
        }

        unsigned    numberOfStepsToReachPoint(
            const std::shared_ptr<Bot> myBot,
            const Geometry::Point& pointToReach,
            const std::vector<SpeedLevel>& i_vSpeedLevels,
            const double i_dTimeDeltaInMilliseconds
            )
        {
            // 1. Break

            // 2. Rotate
            double dTargetAngleInDegrees = Geometry::angleInDegrees(myBot->getPosition(), pointToReach);
            double dChangeInAngleInDegrees = Geometry::normalizeAngleInDegrees(dTargetAngleInDegrees - myBot->getAngleInDegrees());

            double dMaxAngle = getMaxAngularSpeed(
                i_vSpeedLevels,
                myBot->getSpeed()
                );
            unsigned nNumberOfStepsToRotate = (unsigned)ceil(fabs(dChangeInAngleInDegrees) / dMaxAngle);

            // 3. Accelerate

            double dDistanceToTarget = Geometry::distance(pointToReach, myBot->getPosition());
            assert(dDistanceToTarget >= 0.0);

            //unsigned nNumberOfStepsToAccelerate = (unsigned)ceil(dDistanceToTarget / myBot->getSpeed());
            unsigned nNumberOfStepsToAccelerate = 0;

            double dCurrentSpeed = myBot->getSpeed();
            double dDistanceToGo = dDistanceToTarget;
            while (dDistanceToGo > 0.0)
            {
                nNumberOfStepsToAccelerate++;
                dDistanceToGo -= (dCurrentSpeed*(i_dTimeDeltaInMilliseconds/1000.0));
                dCurrentSpeed = accelerate(dCurrentSpeed, i_vSpeedLevels);
            }

            // Result
            return nNumberOfStepsToRotate 
                + nNumberOfStepsToAccelerate;
        }

        bool    isCollisionExpected(
            const Bot& bot1, 
            const Bot& bot2, 
            const double i_dTimeDeltaInMilliseconds
            )
        {
            // Simply check intersection of two lines, if bots will not change direction nor speed.
            const Geometry::Line trajectoryBot1(bot1.getPosition(), bot1.getFuturePosition(i_dTimeDeltaInMilliseconds));
            const Geometry::Line trajectoryBot2(bot2.getPosition(), bot2.getFuturePosition(i_dTimeDeltaInMilliseconds));

            return Geometry::doLinesIntersect(
                trajectoryBot1, trajectoryBot2
                );
        }

        double calculateMaxAttackAngleInDegrees(const double i_dBotRadius, const double i_dBotDistance)
        {
            // If bots are too close ...
            const double dPrecision = 1E-04;
            if (i_dBotDistance < dPrecision)
            {
                return 180.0; 
            }

            // Normal case ...
            double x = i_dBotDistance;
            double y = i_dBotRadius;
            return Geometry::convertAngleFromRadiansToDegrees(atan2(y,x))/2.0;
        }

        bool   isStuckedNearTheWall(
            const std::shared_ptr<BotWarz::Bot> i_pBot,
            const std::shared_ptr<BotWarz::World> i_pWorld,
            const std::vector<BotWarz::SpeedLevel>& i_vspeedLevels,
            double i_dBotRadius
            )
        {
            bool bIsStuckedNearTheWall = false;
            BotWarz::Bot copyOfMyBot = *i_pBot;
            copyOfMyBot.setSpeed(getMinimalSpeed(i_vspeedLevels));
            Geometry::Point futurePosition = copyOfMyBot.getFuturePosition();
            if (!i_pWorld->isInside(futurePosition.x(), futurePosition.y(), i_dBotRadius))
            {
                bIsStuckedNearTheWall = true;
            }

            return bIsStuckedNearTheWall;
        }

        bool   isBotAlignedWithAttackZone(
            const std::shared_ptr<BotWarz::Bot> i_pBot1,
            const std::shared_ptr<BotWarz::Bot> i_pBot2
            )
        {
            double dTargetAngleInDegrees = Geometry::angleInDegrees(i_pBot2->getPosition(), i_pBot1->getPosition());
            double dChangeInAngleInDegrees = Geometry::normalizeAngleInDegrees(dTargetAngleInDegrees - i_pBot2->getAngleInDegrees());
            double dBotsDistance = Geometry::distance(i_pBot1->getPosition(), i_pBot2->getPosition());
            double dTimeStepInMilliseconds = 250.0;
            double botsWillChangeDistance = (i_pBot1->getSpeed() + i_pBot2->getSpeed())*(dTimeStepInMilliseconds/1000.0);

            return (fabs(dChangeInAngleInDegrees) < 45.0) && (botsWillChangeDistance > dBotsDistance);
        }



        //
        // FindEnemyBotPolicyInterface
        //
        FindEnemyBotPolicyInterface::FindEnemyBotPolicyInterface()
        {
        }

        FindEnemyBotPolicyInterface::~FindEnemyBotPolicyInterface()
        {
        }

        //
        // FindClosestBotPolicy
        //
        FindClosestBotPolicy::FindClosestBotPolicy()
        {
        }

        FindClosestBotPolicy::~FindClosestBotPolicy()
        {
        }

        size_t FindClosestBotPolicy::getBotIndex(
            std::shared_ptr<Bot> myBot,
            const std::vector < std::shared_ptr<Bot>>& i_vBots
            )
        {
            return findClosestBot(
                i_vBots, myBot->getPosition()
                );
        }

        //
        // FindMostReachableBotPolicy
        //
        FindMostReachableBotPolicy::FindMostReachableBotPolicy(
            const std::vector<BotWarz::SpeedLevel>& i_vSpeedLevels
            ) : m_vSpeedLevels(i_vSpeedLevels)
        {
        }

        FindMostReachableBotPolicy::~FindMostReachableBotPolicy()
        {
        }

        size_t FindMostReachableBotPolicy::getBotIndex(
            std::shared_ptr<Bot> myBot,
            const std::vector < std::shared_ptr<Bot>>& i_vBots
            )
        {
            return findMostReachableBot(
                i_vBots, myBot, m_vSpeedLevels
                );
        }        

        //
        // ChasingPolicyInterface
        //
        ChasingPolicyInterface::ChasingPolicyInterface()
        {
        }

        ChasingPolicyInterface::~ChasingPolicyInterface()
        {
        }

        //
        // CurrentPositionChasingPolicy
        //
        CurrentPositionChasingPolicy::CurrentPositionChasingPolicy()
        {
        }

        CurrentPositionChasingPolicy::~CurrentPositionChasingPolicy()
        {
        }

        Geometry::Point CurrentPositionChasingPolicy::getDestinationPoint(const std::shared_ptr<Bot> i_pBot)
        {
            return i_pBot->getPosition();
        }

        //
        // FuturePositionChasingPolicy
        //
        FuturePositionChasingPolicy::FuturePositionChasingPolicy(
            double i_dTimeDeltaInMilliseconds
            ) :
            m_dTimeDeltaInMilliseconds(i_dTimeDeltaInMilliseconds)
        {
        }

        FuturePositionChasingPolicy::~FuturePositionChasingPolicy()
        {
        }

        Geometry::Point FuturePositionChasingPolicy::getDestinationPoint(const std::shared_ptr<Bot> i_pBot)
        {
            return i_pBot->getFuturePosition(m_dTimeDeltaInMilliseconds);
        }


    }//namespace Strategy
}//namespace Botwarz

