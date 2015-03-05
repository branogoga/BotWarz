#include "./Bot.h"

#include "Geometry/Point.h"

using namespace BotWarz;

Bot::Bot( unsigned i_nId,
    const Geometry::Point& i_Position,
    double i_dAngleInDegrees,
    double i_dSpeed
    ):
    m_nId(i_nId),
    m_Position(i_Position),
    m_dAngleInDegrees(i_dAngleInDegrees),
    m_dSpeed(i_dSpeed)
{
}

Bot::~Bot()
{
}

unsigned    Bot::getId() const
{
    return m_nId;
}

Geometry::Point Bot::getPosition() const
{
    return m_Position;
}

void    Bot::setPosition(const Geometry::Point& i_Position)
{
    m_Position = i_Position;
}

Geometry::Point Bot::getFuturePosition(double i_dTimeDeltaInMilliseconds)
{
    double  directionX = cos(Geometry::convertAngleFromDegreesToRadians(getAngleInDegrees()));
    double  directionY = sin(Geometry::convertAngleFromDegreesToRadians(getAngleInDegrees()));

    double  dTimeDeltaInSeconds = (i_dTimeDeltaInMilliseconds / 1000.0);
    double  distanceX = directionX * m_dSpeed * dTimeDeltaInSeconds;
    double  distanceY = directionY * m_dSpeed * dTimeDeltaInSeconds;

    return Geometry::Point(
        m_Position.x() + distanceX, 
        m_Position.y() + distanceY
        );
}

double      Bot::getPositionX() const
{
    return m_Position.x();
}

double      Bot::getPositionY() const
{
    return m_Position.y();
}

void        Bot::setAngleInDegrees(double i_dAngleInDegrees)
{
    m_dAngleInDegrees = i_dAngleInDegrees;
}

void        Bot::adjustAngleInDegrees(double i_dChangeOfAngleInDegrees)
{
    m_dAngleInDegrees += i_dChangeOfAngleInDegrees;
}

double      Bot::getAngleInDegrees() const
{
    return m_dAngleInDegrees;
}

void        Bot::setSpeed(double i_dSpeed)
{
    m_dSpeed = i_dSpeed;
}

double      Bot::getSpeed() const
{
    return m_dSpeed;
}

std::ostream& operator << (std::ostream& out, const BotWarz::Bot& bot)
{
    out << " id = " << bot.getId()
        << ", position = " << bot.getPosition()
        << ", angle = " << bot.getAngleInDegrees()
        << ", speed = " << bot.getSpeed() 
        << std::endl;

    return out;
}
