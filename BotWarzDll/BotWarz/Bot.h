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

        void    advance(const double i_dTimeStepInMilliseconds);

        unsigned    getId() const;

        Geometry::Point getPosition() const;
        void    setPosition(const Geometry::Point& i_Point);

        Geometry::Point getFuturePosition( const double i_dTimeDeltaInMilliseconds = 250.0 ) const;

        double      getPositionX() const;
        double      getPositionY() const;

        double      getAngleInDegrees() const;
        void        setAngleInDegrees(double i_dAngleInDegrees);
        void        adjustAngleInDegrees(double i_dChaneOfAngleInDegrees);

        double      getSpeed() const;
        void        setSpeed(double i_dSpeed);

        unsigned    getChasedBotId() const;
        void        setChasedBotId(unsigned i_ChasedBotId);

    private:
        unsigned    m_nId;
        Geometry::Point m_Position;
        double      m_dAngleInDegrees;
        double      m_dSpeed;
        unsigned    m_nChasedBotId;
    };

}

std::ostream& operator << (std::ostream& out, const BotWarz::Bot& bot);