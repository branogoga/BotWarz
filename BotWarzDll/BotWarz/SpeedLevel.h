#pragma once



#include <iostream>

namespace BotWarz {

    class SpeedLevel
    {
    public:
        SpeedLevel(double i_dSpeed = 0.0, double i_dMaxAngle = 0.0);
        virtual ~SpeedLevel();

        bool operator < (const SpeedLevel & rhs) const;

        double    getSpeed() const;
        double    getMaxAngle() const;

    private:
        double    m_dSpeed;
        double    m_dMaxAngle;
    };

}//namespace BotWarz

std::ostream& operator << (std::ostream& out, const BotWarz::SpeedLevel& speedLevel);