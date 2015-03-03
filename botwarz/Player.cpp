#include "./Player.h"

#include "Bot.h"

#include <sstream>

using namespace BotWarz;

Player::Player( const std::string& i_szNickName ) :
    m_szNickName(i_szNickName)
{
}


Player::~Player()
{
}

std::string Player::getNickName() const
{
    return m_szNickName;
}

std::vector<Bot>&    Player::getBots() 
{
    return m_vBots;
}

const std::vector<Bot>&    Player::getBots() const
{
    return m_vBots;
}

void Player::setBots(std::vector<Bot> i_vBots)
{
    m_vBots = i_vBots;
}

std::ostream& operator << (std::ostream& out, const BotWarz::Player& player)
{
    out << "player = { " << std::endl;
    out << "  nickname = " << player.getNickName() << std::endl;
    out << "  bots = [ " << std::endl;
    for each(auto bot in player.getBots())
    {
        out << bot;
    }
    out << "  ] " << std::endl;
    out << "}" << std::endl;

    return out;
}

