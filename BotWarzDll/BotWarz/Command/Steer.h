#pragma once

#include "./Base.h"

namespace BotWarz {
    namespace Command {

        class Steer : public Base
        {
        public:

            Steer(unsigned i_nBotId, double i_dAngle)
                : Base(i_nBotId)
                , m_dAngle(i_dAngle)
            {
            }

            virtual ~Steer()
            {
            }

            virtual std::string getCommand() const
            {
                return "steer";
            }

            double getAngle() const
            {
                return m_dAngle;
            }

            virtual     Json::Value toJson() const
            {
                const char* jsonKeyAngle = "angle";

                auto cmd = __super::toJson();
                cmd[jsonKeyAngle] = getAngle();
                return cmd;
            }

            std::ostream& toStream(std::ostream& out) const
            {
                out << "Command = { id: " << getBotId() << " cmd: " << getCommand() << " angle: " << getAngle() << " } ";
                return out;
            }

        private:
            double  m_dAngle;
        };

    }//namespace Command
}//namespace BotWarz
