#include "stdafx.h"

#include "./Strategy.h"

#include "BotWarz/Bot.h"
#include "BotWarz/Player.h"
#include "BotWarz/SpeedLevel.h"

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

        bool    isCollisionExpected(
            const Bot& bot1, 
            const Bot& bot2, 
            const double i_dTimeDeltaInMilliseconds
            )
        {
            // Simply check intersection of two lines, if bots will not change direction nor speed.
            const Geometry::Point bot1_start = bot1.getPosition();
            const Geometry::Point bot1_end = bot1.getFuturePosition(i_dTimeDeltaInMilliseconds);

            const Geometry::Point bot2_start = bot2.getPosition();
            const Geometry::Point bot2_end = bot2.getFuturePosition(i_dTimeDeltaInMilliseconds);

            return Geometry::doLinesIntersect(
                bot1_start, bot1_end,
                bot2_start, bot2_end
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
            return Geometry::convertAngleFromRadiansToDegrees(atan2(y,x));
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
        CurrentPositionChasingPolicy::CurrentPositionChasingPolicy(const std::shared_ptr<Bot> i_pBot)
            : m_pBot(i_pBot)
        {
        }

        CurrentPositionChasingPolicy::~CurrentPositionChasingPolicy()
        {
        }

        Geometry::Point CurrentPositionChasingPolicy::getDestinationPoint()
        {
            return m_pBot->getPosition();
        }

        //
        // FuturePositionChasingPolicy
        //
        FuturePositionChasingPolicy::FuturePositionChasingPolicy(
            const std::shared_ptr<Bot> i_pBot,
            double i_dTimeDeltaInMilliseconds
            ) :
            m_pBot(i_pBot),
            m_dTimeDeltaInMilliseconds(i_dTimeDeltaInMilliseconds)
        {
        }

        FuturePositionChasingPolicy::~FuturePositionChasingPolicy()
        {
        }

        Geometry::Point FuturePositionChasingPolicy::getDestinationPoint()
        {
            return m_pBot->getFuturePosition(m_dTimeDeltaInMilliseconds);
        }


    }//namespace Strategy
}//namespace Botwarz

