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

}//namespace BotWarz

std::ostream& operator << (std::ostream& out, const BotWarz::SpeedLevel& speedLevel)
{
    out << " { speed: " << speedLevel.getSpeed() << ", maxAngle = " << speedLevel.getMaxAngle() << " } ";
    return out;
}

