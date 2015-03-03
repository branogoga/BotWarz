#pragma once

#include <iostream>

namespace BotWarz {

    class SpeedLevel
    {
    public:
        SpeedLevel(double i_dSpeed, double i_dMaxAngle);
        virtual ~SpeedLevel();

        double    getSpeed() const;
        double    getMaxAngle() const;

    private:
        double    m_dSpeed;
        double    m_dMaxAngle;
    };

}

std::ostream& operator << (std::ostream& out, const BotWarz::SpeedLevel& speedLevel);