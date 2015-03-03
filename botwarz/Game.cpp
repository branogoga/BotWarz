#include "./Game.h"

#include "Player.h"
#include "SpeedLevel.h"
#include "World.h"

using namespace BotWarz;

Game::Game(
    const std::shared_ptr<World> i_pWorld,
    const std::vector<SpeedLevel>& i_vSpeedLevels,
    double i_dBotRadiusInPixels
    ) :
    m_pWorld(i_pWorld),
    m_vSpeedLevels(i_vSpeedLevels),
    m_dTimeInMilliseconds(0.0),
    m_dBotRadiusInPixels(i_dBotRadiusInPixels)
{
    if (m_vSpeedLevels.empty())
    {
        throw std::invalid_argument("At least one speed level must be present.");
    }
}

Game::~Game()
{
}

void Game::setTime(double i_dTimeInMilliseconds)
{
    m_dTimeInMilliseconds = i_dTimeInMilliseconds;
}

double Game::getTime() const
{
    return m_dTimeInMilliseconds;
}

double Game::getBotRadius() const
{
    return m_dBotRadiusInPixels;
}

const std::vector<SpeedLevel>& Game::getSpeedLevels() const
{
    return m_vSpeedLevels;
}

const std::shared_ptr<World> Game::getWorld() const
{
    return m_pWorld;
}

void Game::setMyPlayer(std::shared_ptr<Player> i_pPlayer)
{
    m_pMyPlayer = i_pPlayer;
}

std::shared_ptr<Player> Game::getMyPlayer() const
{
    return m_pMyPlayer;
}

void Game::setOtherPlayer(std::shared_ptr<Player> i_pPlayer)
{
    m_pOtherPlayer = i_pPlayer;
}

std::shared_ptr<Player> Game::getOtherPlayer() const
{
    return m_pOtherPlayer;
}

std::ostream& operator << (std::ostream& out, const BotWarz::Game& game)
{
    out << "Game = { " << std::endl;
    out << "  time = " << game.getTime() << std::endl;
    out << "  botRadius = " << game.getBotRadius() << std::endl;
    out << "  world = { " << *game.getWorld() << " } " << std::endl;
    out << "  myPlayer = " << *game.getMyPlayer();
    out << "  otherPlayer = " << *game.getOtherPlayer();
    out << "  speedLevels = [ " << std::endl;
    for each(auto speedLevel in game.getSpeedLevels())
    {
        out << speedLevel << std::endl;
    }
    out << "  ] " << std::endl;
    out << "} " << std::endl;

    return out;
}