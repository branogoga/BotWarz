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

            auto    bot = std::make_shared<BotWarz::Bot>(
                1, Geometry::Point(100.0, 100.0), 0.0, 0.0
                );

            {
                bot->setAngleInDegrees(0.0);
                auto    command = std::make_shared<BotWarz::Command::Steer>(
                    bot->getId(),
                    +30.0
                    );

                apply(bot, command, vSpeedLevels);
                Assert::AreEqual(+30.0, bot->getAngleInDegrees());
            }

            {
                bot->setAngleInDegrees(0.0);
                auto    command = std::make_shared<BotWarz::Command::Steer>(
                    bot->getId(),
                    +360.0
                    );

                apply(bot, command, vSpeedLevels);
                Assert::AreEqual(+0.0, bot->getAngleInDegrees());
            }

            {
                bot->setAngleInDegrees(0.0);
                auto    command = std::make_shared<BotWarz::Command::Steer>(
                    bot->getId(),
                    -30.0
                    );

                apply(bot, command, vSpeedLevels);
                Assert::AreEqual(-30.0, bot->getAngleInDegrees());
            }

        }

	};
}