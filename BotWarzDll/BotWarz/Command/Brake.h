#pragma once

#include "./Base.h"

namespace BotWarz {
    namespace Command {

        class Brake : public Base
        {
        public:

            Brake(unsigned i_nBotId)
                : Base(i_nBotId)
            {
            }

            virtual ~Brake()
            {
            }


            virtual std::string getCommand() const
            {
                return "brake";
            }
        };

    }//namespace Command
}//namespace BotWarz
