#include "stdafx.h"
#include "CppUnitTest.h"

#include "BotWarz/Bot.h"
#include "BotWarz/SpeedLevel.h"
#include "BotWarz/Command/Steer.h"

#include <memory>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace BotWarzTest
{
	TEST_CLASS(SteerTest)
	{
	public:
		
		TEST_METHOD(TestSteerCommand)
		{
            std::vector<BotWarz::SpeedLevel> vSpeedLevels;
            vSpeedLevels.push_back(BotWarz::SpeedLevel(10.0, 10.0));
            vSpeedLevels.push_back(BotWarz::SpeedLevel(20.0, 30.0));
            vSpeedLevels.push_back(BotWarz::SpeedLevel(30.0, 20.0));

            auto    bot = std::make_shared<BotWarz::Bot>(
                1, Geometry::Point(100.0, 100.0), 0.0/*angle*/, 20.0/*speed*/
                );

            {
                bot->setAngleInDegrees(0.0);
                auto    command = std::make_shared<BotWarz::Command::Steer>(
                    bot,
                    +30.0,
                    vSpeedLevels
                    );

                command->apply();
                Assert::AreEqual(+30.0, bot->getAngleInDegrees());
            }

            {
                bot->setAngleInDegrees(0.0);
                auto    command = std::make_shared<BotWarz::Command::Steer>(
                    bot,
                    +360.0,
                    vSpeedLevels
                    );

                command->apply();
                Assert::AreEqual(+30.0, bot->getAngleInDegrees());
            }

            {
                bot->setAngleInDegrees(0.0);
                auto    command = std::make_shared<BotWarz::Command::Steer>(
                    bot,
                    -30.0, 
                    vSpeedLevels
                    );

                command->apply();
                Assert::AreEqual(-30.0, bot->getAngleInDegrees());
            }

        }

	};
}