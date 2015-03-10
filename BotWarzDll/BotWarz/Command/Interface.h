#pragma once

#include "dll.h"

#include <memory>
#include <string>

namespace Json {
    class Value;
}

namespace BotWarz {

    class Bot;

    namespace Command {

        class TESTABLE Interface
        {
        public:

            Interface()
            {
            }

            virtual ~Interface()
            {
            }

            virtual void    apply() = 0;

            virtual unsigned getBotId() const = 0;
            virtual std::string getCommand() const = 0;
            virtual std::ostream& toStream(std::ostream& out) const = 0;
            virtual Json::Value toJson() const = 0;
        };

    }//namespace Command
}//namespace BotWarz



