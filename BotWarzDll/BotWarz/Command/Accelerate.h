#pragma once

#include "./Base.h"

namespace BotWarz {
    namespace Command {

        class Accelerate : public Base
        {
        public:
            Accelerate(unsigned i_nBotId)
                : Base(i_nBotId)
            {
            }

            virtual ~Accelerate()
            {
            }

            virtual std::string getCommand() const
            {
                return "accelerate";
            }
        };

    }//namespace Command
}//namespace BotWarz


