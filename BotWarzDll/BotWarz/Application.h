#pragma once

#include "dll.h"
#include "Logger.h"

#include "boost/noncopyable.hpp"

#include <string>

namespace Json {
    class Value;
}

namespace BotWarz {

    class DLL_API ApplicationInterface
    {
    public:
        ApplicationInterface( const char* i_szNickName = "", std::shared_ptr<Logger> i_pLogger = nullptr );
        virtual ~ApplicationInterface();

        virtual void    Initialize( const Json::Value& i_jsonGame ) = 0;
        virtual void    Update(const Json::Value& i_jsonPlay) = 0;
        virtual void    Advance(const double i_dTimeStepInMilliseconds) = 0;

        virtual const char* GetMove() = 0;

        virtual unsigned  GetId() const = 0;
        virtual std::string GetPlayerNickname() const = 0;
        virtual std::string GetEnemyNickname() const = 0;
        virtual std::string GetStrategyName() const = 0;
    };

    DLL_API ApplicationInterface* createApplication(
        const char* i_szNickName,
        std::shared_ptr<Logger> i_pLogger = nullptr
        );
    DLL_API void    deleteApplication(ApplicationInterface* pApplication);

}//namespace Application