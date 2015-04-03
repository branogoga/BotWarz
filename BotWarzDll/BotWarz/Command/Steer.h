#pragma once

#include "./Base.h"
#include "Geometry/Angle.h"

#pragma warning(push)
#pragma warning(disable: 4251 /* Shared_ptr going across Dll (Test) */ )

namespace BotWarz {
    namespace Command {

        class TESTABLE Steer : public Base
        {
        public:

            Steer(std::shared_ptr<Bot> i_pBot, double i_dAngle, const std::vector<SpeedLevel>& i_vSpeedLevels)
                : Base(i_pBot)
                , m_dAngle(i_dAngle)
                , m_vSpeedLevels(i_vSpeedLevels)
            {
            }

            virtual ~Steer()
            {
            }

            virtual std::string getCommand() const
            {
                return "steer";
            }

            void    apply()
            {
                double dAngleToApply = __min(
                    this->getAngle(),
                    getMaxAngularSpeed(m_vSpeedLevels, m_pBot->getSpeed())
                    );

                m_pBot->setAngleInDegrees(
                    Geometry::normalizeAngleInDegrees(
                        m_pBot->getAngleInDegrees() + dAngleToApply
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
            std::vector<SpeedLevel> m_vSpeedLevels;
        };

    }//namespace Command
}//namespace BotWarz

//#pragma warning(pop)