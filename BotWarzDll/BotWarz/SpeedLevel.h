#pragma once

#include "dll.h"

#include <iostream>
#include <vector>

namespace BotWarz {

    class TESTABLE SpeedLevel
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

    TESTABLE double  getMaxAngle(
        const std::vector<SpeedLevel>& vSpeedLevels,
        double i_dSpeed, 
        const double i_dDefaultAngle = 30.0
        );

    TESTABLE bool    isMinimalSpeed(
        const std::vector<SpeedLevel>& vSpeedLevels,
        double i_dSpeed
        );

    TESTABLE double  getMinimalSpeed(
        const std::vector<SpeedLevel>& vSpeedLevels
        );

    TESTABLE bool    isMaximalSpeed(
        const std::vector<SpeedLevel>& vSpeedLevels,
        double i_dSpeed
        );

    TESTABLE double  getMaximalSpeed(
        const std::vector<SpeedLevel>& vSpeedLevels
        );

    TESTABLE double accelerate(
        const double i_dCurrentSpeed,
        const std::vector<SpeedLevel>& i_vSpeedlevels
        );

    TESTABLE double brake(
        const double i_dCurrentSpeed,
        const std::vector<SpeedLevel>& i_vSpeedlevels
        );

}//namespace BotWarz

std::ostream& operator << (std::ostream& out, const BotWarz::SpeedLevel& speedLevel);