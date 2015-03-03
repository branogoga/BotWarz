#include "./World.h"

using namespace BotWarz;

World::World(unsigned i_nSizeX, unsigned i_nSizeY) : 
    m_nSizeX(i_nSizeX), 
    m_nSizeY(i_nSizeY)
{
}


World::~World()
{
}

unsigned World::getSizeX() const
{
    return m_nSizeX;
}

unsigned World::getSizeY() const
{
    return m_nSizeY;
}

std::ostream& operator << (std::ostream& out, const BotWarz::World& world)
{
    out << "width: " << world.getSizeX() << ", height: " << world.getSizeY();
    return out;
}

