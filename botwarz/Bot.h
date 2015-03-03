#pragma once

#include <iostream>

namespace BotWarz {

    class Bot
    {
    public:
        Bot( unsigned i_nId );
        virtual ~Bot();

        unsigned    getId() const;

        double      getPositionX() const;
        void        setPositionX(double i_dPositionX);

        double      getPositionY() const;
        void        setPositionY(double i_dPositionY);

        double      getAngle() const;
        void        setAngle(double i_dAngle);

        double      getSpeed() const;
        void        setSpeed(double i_dSpeed);


    private:
        unsigned    m_nId;
        double      m_dPositionX;
        double      m_dPositionY;
        double      m_dAngle;
        double      m_dSpeed;
    };

}

std::ostream& operator << (std::ostream& out, const BotWarz::Bot& bot);


