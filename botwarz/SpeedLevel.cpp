#include "./SpeedLevel.h"

#include <iostream>

using namespace BotWarz;

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

std::ostream& operator << (std::ostream& out, const BotWarz::SpeedLevel& speedLevel)
{
    out << " { speed: " << speedLevel.getSpeed() << ", maxAngle = " << speedLevel.getMaxAngle() << " } ";
    return out;
}

