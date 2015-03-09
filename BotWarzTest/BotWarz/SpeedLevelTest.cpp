#include "stdafx.h"
#include "CppUnitTest.h"

#include "BotWarz\SpeedLevel.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace BotWarzTest
{
	TEST_CLASS(SpeedLevelTest)
	{
	public:
		
		TEST_METHOD(TestOperatorLess)
		{
            BotWarz::SpeedLevel speedLevel1(10.0, 20.0);
            BotWarz::SpeedLevel speedLevel2(20.0, 10.0);

            Assert::IsTrue( speedLevel1 < speedLevel2 );
            //assert( speedLevel2 > speedLevel1 );
        }

        TEST_METHOD(TestGetMinimalSpeed)
        {
            std::vector<BotWarz::SpeedLevel> vSpeedLevels;
            vSpeedLevels.push_back(BotWarz::SpeedLevel(10.0, 10.0));
            vSpeedLevels.push_back(BotWarz::SpeedLevel(20.0, 30.0));
            vSpeedLevels.push_back(BotWarz::SpeedLevel(30.0, 20.0));
            Assert::AreEqual(10.0, BotWarz::getMinimalSpeed(vSpeedLevels));
        }

        TEST_METHOD(TestIsMinimalSpeed)
        {
            std::vector<BotWarz::SpeedLevel> vSpeedLevels;
            vSpeedLevels.push_back(BotWarz::SpeedLevel(10.0, 10.0));
            vSpeedLevels.push_back(BotWarz::SpeedLevel(20.0, 30.0));
            vSpeedLevels.push_back(BotWarz::SpeedLevel(30.0, 20.0));
            Assert::IsTrue(BotWarz::isMinimalSpeed(vSpeedLevels, 10.0));
            Assert::IsFalse(BotWarz::isMinimalSpeed(vSpeedLevels, 20.0));
            Assert::IsFalse(BotWarz::isMinimalSpeed(vSpeedLevels, 30.0));
            Assert::IsTrue(BotWarz::isMinimalSpeed(vSpeedLevels, 0.0));
            Assert::IsFalse(BotWarz::isMinimalSpeed(vSpeedLevels, 123.4));
        }

        TEST_METHOD(TestIsMaximalSpeed)
        {
            std::vector<BotWarz::SpeedLevel> vSpeedLevels;
            vSpeedLevels.push_back(BotWarz::SpeedLevel(10.0, 10.0));
            vSpeedLevels.push_back(BotWarz::SpeedLevel(20.0, 30.0));
            vSpeedLevels.push_back(BotWarz::SpeedLevel(30.0, 20.0));
            Assert::IsFalse(BotWarz::isMaximalSpeed(vSpeedLevels, 10.0));
            Assert::IsFalse(BotWarz::isMaximalSpeed(vSpeedLevels, 20.0));
            Assert::IsTrue(BotWarz::isMaximalSpeed(vSpeedLevels, 30.0));
            Assert::IsFalse(BotWarz::isMaximalSpeed(vSpeedLevels, 0.0));
            Assert::IsTrue(BotWarz::isMaximalSpeed(vSpeedLevels, 123.4));
        }

        TEST_METHOD(TestGetMaxAngle)
        {
            std::vector<BotWarz::SpeedLevel> vSpeedLevels;
            vSpeedLevels.push_back(BotWarz::SpeedLevel(10.0, 10.0));
            vSpeedLevels.push_back(BotWarz::SpeedLevel(20.0, 30.0));
            vSpeedLevels.push_back(BotWarz::SpeedLevel(30.0, 50.0));
            Assert::AreEqual(10.0, BotWarz::getMaxAngle(vSpeedLevels, 10.0, -1.0));
            Assert::AreEqual(30.0, BotWarz::getMaxAngle(vSpeedLevels, 20.0, -1.0));
            Assert::AreEqual(50.0, BotWarz::getMaxAngle(vSpeedLevels, 30.0, -1.0));
            Assert::AreEqual(-1.0, BotWarz::getMaxAngle(vSpeedLevels, 0.0, -1.0));
            Assert::AreEqual(-1.0, BotWarz::getMaxAngle(vSpeedLevels, 123.4, -1.0));
        }
    };
}