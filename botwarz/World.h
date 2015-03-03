#pragma once

#include <iostream>

namespace BotWarz {

    class World
    {
    public:
        World( unsigned i_nSizeX = 900, unsigned i_nSizeY = 600 );
        virtual ~World();

        unsigned getSizeX() const;
        unsigned getSizeY() const;

    private:
        unsigned    m_nSizeX;
        unsigned    m_nSizeY;
    };

}

std::ostream& operator << (std::ostream& out, const BotWarz::World& world);