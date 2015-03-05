#pragma once

#include "./Bot.h"

#include "boost/noncopyable.hpp"

#include <memory>
#include <string>
#include <vector>

namespace BotWarz {

    //template class DLL_API std::shared_ptr<Bot>;
    //template class DLL_API std::vector<std::shared_ptr<Bot>>;

    class  Player : public boost::noncopyable
    {
    public:
        Player( const std::string& i_szNickName );
        virtual ~Player();

        std::string getNickName() const;

        std::vector<std::shared_ptr<Bot>>&    getBots();
        std::shared_ptr<Bot> getBot( unsigned i_nBotId );
        const std::vector<std::shared_ptr<Bot>>&    getBots() const;
        void setBots(std::vector<std::shared_ptr<Bot>> i_vBots);

    private:
        std::string m_szNickName;
        std::vector<std::shared_ptr<Bot>>   m_vBots;
    };

}

DLL_API std::ostream& operator << (std::ostream& out, const BotWarz::Player& player);