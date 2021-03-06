//#include "stdafx.h"

#include "BotWarz/Bot.h"
#include "BotWarz/SpeedLevel.h"
#include "BotWarz/Command/Accelerate.h"

#include "CppUnitTest.h"

#include <memory>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace BotWarzTest
{
	TEST_CLASS(AccelerateTest)
	{
	public:
		
		TEST_METHOD(TestAccelerateCommand)
		{
            std::vector<BotWarz::SpeedLevel> vSpeedLevels;
            vSpeedLevels.push_back(BotWarz::SpeedLevel(10.0, 10.0));
            vSpeedLevels.push_back(BotWarz::SpeedLevel(20.0, 30.0));
            vSpeedLevels.push_back(BotWarz::SpeedLevel(30.0, 20.0));
    
            auto    bot = std::make_shared<BotWarz::Bot>(
                1, Geometry::Point(100.0,100.0), 0.0, 0.0
                );

            auto    command = std::make_shared<BotWarz::Command::Accelerate>(
                bot, vSpeedLevels
                );

            command->apply();
            Assert::AreEqual(10.0, bot->getSpeed());

            command->apply();
            Assert::AreEqual(20.0, bot->getSpeed());
        }

	};
}