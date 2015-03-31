#pragma once

#pragma warning(push)
#pragma warning(disable: 4251 /* Shared_ptr going across Dll (Test) */ )

#include "./Bot.h"

#include <boost/noncopyable.hpp>

#include <memory>
#include <string>
#include <vector>

namespace BotWarz {

    class  TESTABLE Player : public boost::noncopyable
    {
    public:
        Player( const std::string i_szNickName );
        virtual ~Player();

        std::string getNickName() const;
        void    advance(const double i_dTimeStepInMilliseconds);

        std::vector<std::shared_ptr<Bot>>&    getBots();
        std::shared_ptr<Bot> getBot( unsigned i_nBotId );
        const std::vector<std::shared_ptr<Bot>>&    getBots() const;
        void setBots(const std::vector<std::shared_ptr<Bot>> i_vBots);

    private:
        std::string m_szNickName;
        std::vector<std::shared_ptr<Bot>>   m_vBots;
    };

}

DLL_API std::ostream& operator << (std::ostream& out, const BotWarz::Player& player);

#pragma warning(pop)