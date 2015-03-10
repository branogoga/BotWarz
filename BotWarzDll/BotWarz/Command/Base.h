#pragma once

#include "./Interface.h"

#include "dll.h"

#include "jsoncpp/include/json/json.h"

#include <string>
#include <iostream>

#pragma warning(push)
#pragma warning(disable: 4251 /* Shared_ptr going across Dll (Test) */ )

namespace BotWarz {
    namespace Command {

        class TESTABLE Base : public Interface
        {
        public:

            Base(std::shared_ptr<Bot> i_pBot)
                : m_pBot(i_pBot)
            {
            }

            virtual ~Base()
            {
            }

            virtual unsigned    getBotId() const
            {
                return m_pBot->getId();
            }

            virtual std::string getCommand() const = 0;

            virtual std::ostream& toStream(std::ostream& out) const
            {
                out << "Command = { id: " << getBotId() << " cmd: " << getCommand() << " } ";
                return out;
            }

            virtual Json::Value toJson() const
            {
                const char* jsonKeyCommand = "cmd";
                const char* jsonKeyBotId = "id";

                Json::Value cmd;
                cmd[jsonKeyCommand] = getCommand();
                cmd[jsonKeyBotId] = getBotId();

                return cmd;
            }


        protected:
            std::shared_ptr<Bot>   m_pBot;
        };

    }
}

#pragma warning(pop)