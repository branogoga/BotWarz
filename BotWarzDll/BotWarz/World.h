#pragma once

#include "dll.h"

#include <iostream>

namespace BotWarz {

    class TESTABLE World
    {
    public:
        World( unsigned i_nSizeX = 900, unsigned i_nSizeY = 600 );
        virtual ~World();

        unsigned getSizeX() const;
        unsigned getSizeY() const;

        bool    isInside(const double i_dPointX, const double i_dPointY, const double i_dMargin = 20.0) const;

    private:
        unsigned    m_nSizeX;
        unsigned    m_nSizeY;
    };

}

std::ostream& operator << (std::ostream& out, const BotWarz::World& world);