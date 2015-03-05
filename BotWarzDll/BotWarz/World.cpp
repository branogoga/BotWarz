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

bool    World::isInside(const double i_dPointX, const double i_dPointY, const double i_dMargin) const
{
    return 
        (i_dPointX > i_dMargin) &&
        (i_dPointY > i_dMargin) &&
        (i_dPointX < getSizeX() - i_dMargin) &&
        (i_dPointY < getSizeY() - i_dMargin);

}

std::ostream& operator << (std::ostream& out, const BotWarz::World& world)
{
    out << "width: " << world.getSizeX() << ", height: " << world.getSizeY();
    return out;
}

