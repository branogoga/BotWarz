#pragma once

#include <string>

namespace Json {
    class Value;
}

namespace BotWarz {
    namespace Command {

        class Interface
        {
        public:

            Interface()
            {
            }

            virtual ~Interface()
            {
            }

            virtual unsigned getBotId() const = 0;
            virtual std::string getCommand() const = 0;
            virtual std::ostream& toStream(std::ostream& out) const = 0;
            virtual Json::Value toJson() const = 0;
        };


    }//namespace Command
}//namespace BotWarz



