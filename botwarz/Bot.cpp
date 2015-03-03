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

void        Bot::setPositionX(double i_dPositionX)
{
    m_dPositionX = i_dPositionX;
}

double      Bot::getPositionX() const
{
    return m_dPositionX;
}

void        Bot::setPositionY(double i_dPositionY)
{
    m_dPositionY = i_dPositionY;
}

double      Bot::getPositionY() const
{
    return m_dPositionY;
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
        << ", x = " << bot.getPositionX()
        << ", y = " << bot.getPositionY()
        << ", angle = " << bot.getAngle()
        << ", speed = " << bot.getSpeed() 
        << std::endl;

    return out;
}
