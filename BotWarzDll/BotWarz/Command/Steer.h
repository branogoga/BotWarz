#pragma once

#include "./Base.h"

//#pragma warning(push)
//#pragma warning(disable: 4251 /* Shared_ptr going across Dll (Test) */ )

namespace BotWarz {
    namespace Command {

        class TESTABLE Steer : public Base
        {
        public:

            Steer(std::shared_ptr<Bot> i_pBot, double i_dAngle)
                : Base(i_pBot)
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

            void    apply(
                std::shared_ptr<Bot> bot
                )
            {
                bot->setAngleInDegrees(
                    Geometry::normalizeAngleInDegrees(
                        bot->getAngleInDegrees() + this->getAngle()
                    )
                    );
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

//#pragma warning(pop)