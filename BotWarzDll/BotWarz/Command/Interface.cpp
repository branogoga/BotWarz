#include "./Interface.h"

#include "jsoncpp/include/json/json.h"

namespace BotWarz {
    namespace Command {

        Json::Value toJson(Interface& command)
        {
            const char* jsonKeyCommand = "cmd";
            const char* jsonKeyBotId = "id";

            Json::Value cmd;
            cmd[jsonKeyCommand] = command.getCommand();
            cmd[jsonKeyBotId] = command.getBotId();

            return cmd;
        }

    }//namespace Command
}//namespace BotWarz

