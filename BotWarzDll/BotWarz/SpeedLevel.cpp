#include "./SpeedLevel.h"

#include <iostream>
#include <vector>

namespace BotWarz {

    SpeedLevel::SpeedLevel(double i_dSpeed, double i_dMaxAngle) :
        m_dSpeed(i_dSpeed),
        m_dMaxAngle(i_dMaxAngle)
    {
    }

    SpeedLevel::~SpeedLevel()
    {
    }

    double    SpeedLevel::getSpeed() const
    {
        return m_dSpeed;
    }

    double    SpeedLevel::getMaxAngle() const
    {
        return m_dMaxAngle;
    }

    bool SpeedLevel::operator < (const SpeedLevel & rhs) const 
    {
        return getSpeed() < rhs.getSpeed();
    }

    double  getMaxAngle(
        const std::vector<SpeedLevel>& vSpeedLevels,
        double i_dSpeed,
        const double i_dDefaultAngle
        )
    {
        for each(auto speedLevel in vSpeedLevels)
        {
            if (speedLevel.getSpeed() == i_dSpeed)
            {
                return speedLevel.getMaxAngle();
            }
        }

        return i_dDefaultAngle;
        //throw std::invalid_argument("Invalid speed level.");
    }

    bool    isMinimalSpeed(
        const std::vector<SpeedLevel>& vSpeedLevels,
        double i_dSpeed
        )
    {
        for each(auto speedLevel in vSpeedLevels)
        {
            if (speedLevel.getSpeed() < i_dSpeed)
            {
                return false;
            }
        }

        return true;
    }

    double  getMinimalSpeed(
        const std::vector<SpeedLevel>& vSpeedLevels
        )
    {
        double dMinimalSpeed = vSpeedLevels[0].getSpeed();
        for each(auto speedLevel in vSpeedLevels)
        {
            if (speedLevel.getSpeed() < dMinimalSpeed)
            {
                dMinimalSpeed = speedLevel.getSpeed();
            }
        }

        return dMinimalSpeed;
    }

    bool    isMaximalSpeed(
        const std::vector<SpeedLevel>& vSpeedLevels,
        double i_dSpeed
        )
    {
        for each(auto speedLevel in vSpeedLevels)
        {
            if (speedLevel.getSpeed() > i_dSpeed)
            {
                return false;
            }
        }

        return true;
    }

    double  getMaximalSpeed(
        const std::vector<SpeedLevel>& vSpeedLevels
        )
    {
        double dMaximalSpeed = vSpeedLevels[0].getSpeed();
        for each(auto speedLevel in vSpeedLevels)
        {
            if (speedLevel.getSpeed() > dMaximalSpeed)
            {
                dMaximalSpeed = speedLevel.getSpeed();
            }
        }

        return dMaximalSpeed;
    }

    namespace {
        std::vector<SpeedLevel>::const_iterator   findSpeed(
            const double i_dCurrentSpeed, 
            const std::vector<SpeedLevel>& i_vSpeedLevel
            )
        {
            std::vector<SpeedLevel>::const_iterator   it = i_vSpeedLevel.begin();
            while (it != i_vSpeedLevel.end())
            {
                if (it->getSpeed() == i_dCurrentSpeed)
                {
                    return it;
                }
                it++;
            }

            return i_vSpeedLevel.end();
        }
    }

    double accelerate(
        const double i_dCurrentSpeed,
        const std::vector<SpeedLevel>& i_vSpeedLevels
        )
    {
        std::vector<SpeedLevel>::const_iterator it = findSpeed(i_dCurrentSpeed, i_vSpeedLevels);
        if (it == i_vSpeedLevels.end())
        {
            // Value not found.
            return getMinimalSpeed(i_vSpeedLevels);
        }

        it++;
        
        if (it == i_vSpeedLevels.end())
        {
            // Already maximal speed.
            return i_dCurrentSpeed;
        }

        return it->getSpeed();
    }

    double brake(
        const double i_dCurrentSpeed,
        const std::vector<SpeedLevel>& i_vSpeedLevels
        )
    {
        std::vector<SpeedLevel>::const_iterator it = findSpeed(i_dCurrentSpeed, i_vSpeedLevels);
        if (it == i_vSpeedLevels.end())
        {
            // Value not found.
            return 0.0;
        }

        if (it == i_vSpeedLevels.begin())
        {
            // Already minimal speed.
            return i_dCurrentSpeed;
        }

        it--;

        return it->getSpeed();
    }



}//namespace BotWarz

std::ostream& operator << (std::ostream& out, const BotWarz::SpeedLevel& speedLevel)
{
    out << " { speed: " << speedLevel.getSpeed() << ", maxAngle = " << speedLevel.getMaxAngle() << " } ";
    return out;
}

