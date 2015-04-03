#include "stdafx.h"
#include "CppUnitTest.h"

#include "BotWarz\SpeedLevel.h"

#include <functional>

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
            Assert::IsFalse(speedLevel2 < speedLevel1);
        }

        TEST_METHOD(TestGetMinimalSpeed)
        {
            std::vector<BotWarz::SpeedLevel> vSpeedLevels;
            vSpeedLevels.push_back(BotWarz::SpeedLevel(10.0, 10.0));
            vSpeedLevels.push_back(BotWarz::SpeedLevel(20.0, 30.0));
            vSpeedLevels.push_back(BotWarz::SpeedLevel(30.0, 20.0));
            Assert::AreEqual(10.0, BotWarz::getMinimalSpeed(vSpeedLevels));
        }

        TEST_METHOD(TestGetMinimalSpeedThrowsOnEmptyContainer)
        {
            auto function = [this] {
                std::vector<BotWarz::SpeedLevel> vSpeedLevels;
                BotWarz::getMinimalSpeed(vSpeedLevels);
            };
            Assert::ExpectException<std::invalid_argument>(
                function
                );
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

        TEST_METHOD(TestGetMaximalSpeed)
        {
            std::vector<BotWarz::SpeedLevel> vSpeedLevels;
            vSpeedLevels.push_back(BotWarz::SpeedLevel(10.0, 10.0));
            vSpeedLevels.push_back(BotWarz::SpeedLevel(20.0, 30.0));
            vSpeedLevels.push_back(BotWarz::SpeedLevel(30.0, 20.0));
            Assert::AreEqual(30.0, BotWarz::getMaximalSpeed(vSpeedLevels));
        }

        TEST_METHOD(TestGetMaximalSpeedThrowsOnEmptyContainer)
        {
            auto function = [this] {
                std::vector<BotWarz::SpeedLevel> vSpeedLevels;
                BotWarz::getMaximalSpeed(vSpeedLevels);
            };
            Assert::ExpectException<std::invalid_argument>(
                function
                );
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

        TEST_METHOD(TestGetMaxAngularSpeed)
        {
            std::vector<BotWarz::SpeedLevel> vSpeedLevels;
            vSpeedLevels.push_back(BotWarz::SpeedLevel(10.0, 10.0));
            vSpeedLevels.push_back(BotWarz::SpeedLevel(20.0, 30.0));
            vSpeedLevels.push_back(BotWarz::SpeedLevel(30.0, 50.0));
            Assert::AreEqual(10.0, BotWarz::getMaxAngularSpeed(vSpeedLevels, 10.0));
            Assert::AreEqual(30.0, BotWarz::getMaxAngularSpeed(vSpeedLevels, 20.0));
            Assert::AreEqual(50.0, BotWarz::getMaxAngularSpeed(vSpeedLevels, 30.0));
        }

        TEST_METHOD(TestGetMaxAngularSpeedThrowsOnNonExistingSpeed)
        {
            auto function = [this] {
                std::vector<BotWarz::SpeedLevel> vSpeedLevels;
                vSpeedLevels.push_back(BotWarz::SpeedLevel(10.0, 10.0));
                vSpeedLevels.push_back(BotWarz::SpeedLevel(20.0, 30.0));
                vSpeedLevels.push_back(BotWarz::SpeedLevel(30.0, 50.0));
                BotWarz::getMaxAngularSpeed(vSpeedLevels, 0.0);
            };
            Assert::ExpectException<std::invalid_argument>(
                function
                );
        }

        TEST_METHOD(TestAccelerate)
        {
            std::vector<BotWarz::SpeedLevel> vSpeedLevels;
            vSpeedLevels.push_back(BotWarz::SpeedLevel(10.0, 10.0));
            vSpeedLevels.push_back(BotWarz::SpeedLevel(20.0, 30.0));
            vSpeedLevels.push_back(BotWarz::SpeedLevel(30.0, 50.0));
            Assert::AreEqual(20.0, BotWarz::accelerate(10.0, vSpeedLevels));
            Assert::AreEqual(30.0, BotWarz::accelerate(20.0, vSpeedLevels));
            Assert::AreEqual(30.0, BotWarz::accelerate(30.0, vSpeedLevels));
            Assert::AreEqual(10.0, BotWarz::accelerate(0.0, vSpeedLevels));
            Assert::AreEqual(10.0, BotWarz::accelerate(123456.0, vSpeedLevels));
        }

        TEST_METHOD(TestBrake)
        {
            std::vector<BotWarz::SpeedLevel> vSpeedLevels;
            vSpeedLevels.push_back(BotWarz::SpeedLevel(10.0, 10.0));
            vSpeedLevels.push_back(BotWarz::SpeedLevel(20.0, 30.0));
            vSpeedLevels.push_back(BotWarz::SpeedLevel(30.0, 50.0));
            Assert::AreEqual(10.0, BotWarz::brake(20.0, vSpeedLevels));
            Assert::AreEqual(20.0, BotWarz::brake(30.0, vSpeedLevels));
            Assert::AreEqual(10.0, BotWarz::brake(10.0, vSpeedLevels));
            Assert::AreEqual(0.0, BotWarz::brake(123456.0, vSpeedLevels));
        }

        TEST_METHOD(TestIsSpeedValid)
        {
            std::vector<BotWarz::SpeedLevel> vSpeedLevels;
            vSpeedLevels.push_back(BotWarz::SpeedLevel(10.0, 10.0));
            vSpeedLevels.push_back(BotWarz::SpeedLevel(20.0, 30.0));
            vSpeedLevels.push_back(BotWarz::SpeedLevel(30.0, 50.0));
            Assert::IsTrue(BotWarz::isSpeedValid(20.0, vSpeedLevels));
            Assert::IsFalse(BotWarz::isSpeedValid(0.0, vSpeedLevels));
        }

        TEST_METHOD(TestGetClosestValidSpeed)
        {
            std::vector<BotWarz::SpeedLevel> vSpeedLevels;
            vSpeedLevels.push_back(BotWarz::SpeedLevel(10.0, 10.0));
            vSpeedLevels.push_back(BotWarz::SpeedLevel(20.0, 30.0));
            vSpeedLevels.push_back(BotWarz::SpeedLevel(30.0, 50.0));
            Assert::AreEqual(20.0, BotWarz::getClosestValidSpeed(20.0, vSpeedLevels));
            Assert::AreEqual(10.0, BotWarz::getClosestValidSpeed(0.0, vSpeedLevels));
        }

    };
}