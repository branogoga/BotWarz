#pragma once

#include "./Base.h"

#pragma warning(push)
#pragma warning(disable: 4251 /* Shared_ptr going across Dll (Test) */ )

namespace BotWarz {
    namespace Command {

        class TESTABLE Accelerate : public Base
        {
        public:
            Accelerate(
                std::shared_ptr<Bot> i_pBot,
                const std::vector<SpeedLevel>& i_vSpeedLevels
                )
                : Base(i_pBot)
                , m_vSpeedLevels(i_vSpeedLevels)
            {
            }

            virtual ~Accelerate()
            {
            }

            virtual std::string getCommand() const
            {
                return "accelerate";
            }

            void    apply()                
            {
                m_pBot->setSpeed(
                    accelerate(m_pBot->getSpeed(), m_vSpeedLevels)
                    );
            }

        private:
            std::vector<SpeedLevel> m_vSpeedLevels;
        };

    }//namespace Command
}//namespace BotWarz

#pragma warning(pop)