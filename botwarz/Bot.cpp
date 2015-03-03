#include "./Bot.h"

using namespace BotWarz;

Bot::Bot( unsigned i_nId ) :
    m_nId( i_nId )
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

double      Bot::getPositionX() const
{
    return m_Position.x();
}

double      Bot::getPositionY() const
{
    return m_Position.y();
}

void        Bot::setAngle(double i_dAngle)
{
    m_dAngle = i_dAngle;
}

double      Bot::getAngle() const
{
    return m_dAngle;
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
        << ", angle = " << bot.getAngle()
        << ", speed = " << bot.getSpeed() 
        << std::endl;

    return out;
}
