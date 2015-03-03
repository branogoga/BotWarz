#pragma once

#include <string>
#include <vector>
#include <memory>

namespace BotWarz {

    class Bot;

    class Player
    {
    public:
        Player( const std::string& i_szNickName );
        virtual ~Player();

        std::string getNickName() const;

        std::vector<Bot>&    getBots();
        const std::vector<Bot>&    getBots() const;
        void setBots(std::vector<Bot> i_vBots);

    private:
        std::string m_szNickName;
        std::vector<Bot>   m_vBots;
    };

}

std::ostream& operator << (std::ostream& out, const BotWarz::Player& player);
