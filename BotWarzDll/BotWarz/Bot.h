#pragma once

#include "./../dll.h"
#include "Geometry/Point.h"

#include <iostream>

namespace BotWarz {

    class  TESTABLE Bot
    {
    public:
        Bot( 
            unsigned i_nId,
            const Geometry::Point& i_Position = Geometry::Point(0.0, 0.0),
            double i_dAngleInDegrees = 0.0,
            double i_dSpeed = 0.0
            );

        virtual ~Bot();

        unsigned    getId() const;

        Geometry::Point getPosition() const;
        void    setPosition(const Geometry::Point& i_Point);

        Geometry::Point getFuturePosition( double i_dTimeDeltaInMilliseconds = 250.0 );

        double      getPositionX() const;
        double      getPositionY() const;

        double      getAngleInDegrees() const;
        void        setAngleInDegrees(double i_dAngleInDegrees);
        void        adjustAngleInDegrees(double i_dChaneOfAngleInDegrees);

        double      getSpeed() const;
        void        setSpeed(double i_dSpeed);


    private:
        unsigned    m_nId;
        Geometry::Point m_Position;
        double      m_dAngleInDegrees;
        double      m_dSpeed;
    };

}

std::ostream& operator << (std::ostream& out, const BotWarz::Bot& bot);


