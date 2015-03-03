#pragma once

#include "Point.h"

#include <iostream>

namespace BotWarz {

    class Bot
    {
    public:
        Bot( unsigned i_nId );
        virtual ~Bot();

        unsigned    getId() const;

        Geometry::Point getPosition() const;
        void    setPosition(const Geometry::Point& i_Point);

        double      getPositionX() const;
        double      getPositionY() const;

        double      getAngle() const;
        void        setAngle(double i_dAngle);

        double      getSpeed() const;
        void        setSpeed(double i_dSpeed);


    private:
        unsigned    m_nId;
        Geometry::Point m_Position;
        double      m_dAngle;
        double      m_dSpeed;
    };

}

std::ostream& operator << (std::ostream& out, const BotWarz::Bot& bot);


