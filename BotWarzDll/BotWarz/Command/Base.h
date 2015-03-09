#pragma once

#include "./Interface.h"

#include "jsoncpp/include/json/json.h"

#include <string>
#include <iostream>

namespace BotWarz {
    namespace Command {

        class Base : public Interface
        {
        public:

            Base(unsigned i_nBotId)
                : m_nBotId(i_nBotId)
            {
            }

            virtual ~Base()
            {
            }

            virtual unsigned    getBotId() const
            {
                return m_nBotId;
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


        private:
            unsigned   m_nBotId;
        };

    }
}

