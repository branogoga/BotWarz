#include "stdafx.h"
#include "CppUnitTest.h"

#include "BotWarz/Bot.h"
#include "BotWarz/SpeedLevel.h"
#include "BotWarz/Command/Brake.h"

#include <memory>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace BotWarzTest
{
	TEST_CLASS(BrakeTest)
	{
	public:
		
        TEST_METHOD(TestBrakeCommand)
        {
            std::vector<BotWarz::SpeedLevel> vSpeedLevels;
            vSpeedLevels.push_back(BotWarz::SpeedLevel(10.0, 10.0));
            vSpeedLevels.push_back(BotWarz::SpeedLevel(20.0, 30.0));
            vSpeedLevels.push_back(BotWarz::SpeedLevel(30.0, 20.0));

            auto    bot = std::make_shared<BotWarz::Bot>(
                1, Geometry::Point(100.0, 100.0), 0.0, 30.0
                );

            auto    command = std::make_shared<BotWarz::Command::Brake>(
                bot->getId()
                );

            apply(bot, command, vSpeedLevels);
            Assert::AreEqual(20.0, bot->getSpeed());

            apply(bot, command, vSpeedLevels);
            Assert::AreEqual(10.0, bot->getSpeed());
        }

	};
}