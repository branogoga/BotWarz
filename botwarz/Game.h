#pragma once

#include <memory>
#include <vector>
#include <iostream>

namespace BotWarz {

    class World;
    class Player;
    class SpeedLevel;

    class Game
    {
    public:
        Game( 
            const std::shared_ptr<World> i_pWorld,
            const std::vector<SpeedLevel>& i_vSpeedLevels,
            double i_dBotRadiusInPixels = 20.0
            );
        virtual ~Game();

        void setTime(double i_dTimeInMilliseconds);
        double getTime() const;

        double getBotRadius() const;
        const std::vector<SpeedLevel>& getSpeedLevels() const;
        const std::shared_ptr<World> getWorld() const;

        std::shared_ptr<Player> getMyPlayer() const;
        void setMyPlayer(std::shared_ptr<Player> i_pPlayer );

        std::shared_ptr<Player> getOtherPlayer() const;
        void setOtherPlayer(std::shared_ptr<Player> i_pPlayer);

    private:
        double  m_dBotRadiusInPixels;
        double  m_dTimeInMilliseconds;
        const std::shared_ptr<World>  m_pWorld;
        const std::vector<SpeedLevel> m_vSpeedLevels;
        std::shared_ptr<Player>     m_pMyPlayer;
        std::shared_ptr< Player >   m_pOtherPlayer;
    };

}

std::ostream& operator << (std::ostream& out, const BotWarz::Game& game);
