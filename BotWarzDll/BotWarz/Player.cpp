#include "./Player.h"

#include "Bot.h"

#include <sstream>

using namespace BotWarz;

Player::Player( const std::string i_szNickName ) :
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

std::vector<std::shared_ptr<Bot>>&    Player::getBots()
{
    return m_vBots;
}

const std::vector<std::shared_ptr<Bot>>&    Player::getBots() const
{
    return m_vBots;
}

std::shared_ptr<Bot> Player::getBot(unsigned i_nBotId)
{
    for each(auto bot in m_vBots)
    {
        if (bot->getId() == i_nBotId)
        {
            return bot;
        }
    }

    throw std::invalid_argument("Bot with given Id does not exist.");
}


void Player::setBots(std::vector<std::shared_ptr<Bot>> i_vBots)
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
        out << *bot;
    }
    out << "  ] " << std::endl;
    out << "}" << std::endl;

    return out;
}

