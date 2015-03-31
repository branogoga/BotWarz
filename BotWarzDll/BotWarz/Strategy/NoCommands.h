#pragma once

#include "./Interface.h"

#include <boost/noncopyable.hpp>

#include <vector>
#include <memory>

#pragma warning(push)
#pragma warning(disable: 4251 /* Shared_ptr going across Dll (Test) */ )

class Logger;

namespace BotWarz {

    namespace Strategy {

        class TESTABLE NoCommands : public Interface, boost::noncopyable
        {
        public:

            NoCommands()
            {
            }

            virtual ~NoCommands()
            {
            }

            virtual std::vector<std::shared_ptr<Command::Interface>>    getCommands(
                const std::shared_ptr<Player> pMyPlayer,
                const std::shared_ptr<Player> pOtherPlayer
                )
            {
                std::vector<std::shared_ptr<Command::Interface>> commands;
                return commands;
            }

            virtual std::string getName() const
            {
                return "NoCommands";
            }

        private:
        };

    }//namespace Strategy
}//namespace BotWarz

#pragma warning(pop)