#pragma once

#include "dll.h"

#include <memory>
#include <string>
#include <vector>

namespace BotWarz {

    class Player;

    namespace Command {
        class Interface;
    }

    namespace Strategy {

        class TESTABLE Interface
        {
        public:

            Interface()
            {
            }

            virtual ~Interface()
            {
            }

            virtual std::vector<std::shared_ptr<Command::Interface>>    getCommands(
                const std::shared_ptr<Player> pMyPlayer,
                const std::shared_ptr<Player> pOtherPlayer
                ) = 0;

            virtual std::string getName() const = 0;
        };


    }
}



