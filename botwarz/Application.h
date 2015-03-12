#pragma once

#include "jsoncpp/include/json/json.h"
#include "sha1/sha1.h"

#include "BotWarz/Application.h"

#include "Consts.h"
#include "Messages.h"
#include "TCPClient.h"
#include "Timer.h"
#include "Utils.h"

#include <assert.h>
#include <memory>
#include <string>
#include <stdio.h>

class Application
{
public:

    Application()
        : m_client(SERVER_NAME, SERVER_PORT)
        , m_FrameTimeSafetyMarginInMiliseconds(5)
        , m_nNumberOfCommandsWithoutTimeViolation(0)
        , m_szInputLogFilename("Logs/in.txt")
        , m_szOutputLogFilename("Logs/out.txt")
    {
        m_pLogger = std::make_shared<Logger>();
        m_client.setLogger(m_pLogger);
    }

    ~Application()
    {
        m_ResultLog.close();
    }

    DWORD   GetFrameTime() const
    {
        return m_RequiredFrameTimeInMiliseconds + m_FrameTimeSafetyMarginInMiliseconds;
    }

	void Execute(const char *token, const char *player_name)
	{
        Json::Reader reader;
        Json::Value json;

        // handshake
		std::string msg = m_client.ReceiveLine();
        CheckStatusAndPrintMessage(msg.c_str(), "socket_connected");

        reader.parse(msg, json);
		std::string hash = GenerateHashValue(json["random"].asString().c_str(), token);

        // send login info
        m_client.Send(Message::Connect(player_name, hash.c_str()));
        msg = m_client.ReceiveLine();
        CheckStatusAndPrintMessage(msg.c_str(), "login_ok");

        // main loop
        WHILE_TRUE
        {
            m_pLogger->open(m_szInputLogFilename, m_szOutputLogFilename);

            // get game data info
            msg = m_client.ReceiveLine();

            reader.parse(msg, json);

            auto applicationDeleter = [](BotWarz::ApplicationInterface* pApplication) {
                BotWarz::deleteApplication(pApplication);
            };
            std::unique_ptr<BotWarz::ApplicationInterface, decltype(applicationDeleter)> pGame(
                BotWarz::createApplication(NICKNAME),
                applicationDeleter
            );
            pGame->Initialize(json);
            int lastGameUpdateTime = GetTickCount();

            Timer timer;

            // loop for one game
            bool is_finished = false;
            while (!is_finished)
            {
                pGame->Advance( GetTickCount() - lastGameUpdateTime );
                lastGameUpdateTime = GetTickCount();

                // send command on server
                std::string szMoveMessage = pGame->GetMove();
                m_client.Send(szMoveMessage);

                std::cout << " FrameTime: " << GetFrameTime() << " ms " << std::endl;
                if (m_nNumberOfCommandsWithoutTimeViolation > 100)
                {
                    m_FrameTimeSafetyMarginInMiliseconds-= 5;
                }
                m_nNumberOfCommandsWithoutTimeViolation++;

                //std::cout << "Time: " << timer.getTimeInMilliseconds() << " ms."
                //    << " - Sending MOVE command.";

                DWORD end_time = GetTickCount() + GetFrameTime();

                int wait_time = end_time - GetTickCount();
                while (m_client.WaitForMessage(wait_time < 0 ? 0 : wait_time))
                {
                    msg = m_client.ReceiveLine();

                    // we just check if game is not finished and if yes, then break loop
                    reader.parse(msg, json);

                    if (!json["status"].isNull())
                    {
                        std::cout << "Status:" << json["status"] << std::endl;
                        std::cout << "Message:" << json["msg"] << std::endl;

                        // Penalty. We can not send next command sooner than 200ms from now.
                        end_time = GetTickCount() + GetFrameTime();

                        const unsigned frameSafetyMarginIncrement = 30;
                        const unsigned minAcceptableNumberOfCommandsWithoutTimeViolation = 200;
                        if (m_nNumberOfCommandsWithoutTimeViolation < minAcceptableNumberOfCommandsWithoutTimeViolation)
                        {
                            m_FrameTimeSafetyMarginInMiliseconds += frameSafetyMarginIncrement;
                        }

                        m_nNumberOfCommandsWithoutTimeViolation = 0;
                    }

                    //if (!json["play"].isNull())
                    //{
                        lastGameUpdateTime = GetTickCount();
                        pGame->Update(json);
                    //}

                    Json::Value jsonResult = json["result"];
                    if (!jsonResult.isNull())
                    {
                        is_finished = true;

                        unsigned resultTime = jsonResult["time"].asUInt();
                        std::string resultStatus = jsonResult["status"].asString();

                        Json::Value jsonWinner = jsonResult["winner"];
                        std::string resultWinnerNickname = jsonWinner["nickname"].asString();
                        unsigned    resultWinnerNumberOfBots = jsonWinner["bots"].size();

                        Json::Value jsonLooser = jsonResult["looser"];
                        std::string resultLooserNickname = "-";
                        unsigned    resultLooserNumberOfBots = 0;
                        if (!jsonLooser.isNull())
                        {
                            resultLooserNickname = jsonLooser["nickname"].asString();
                            resultLooserNumberOfBots = jsonLooser["bots"].size();
                        }

                        std::cout << resultStatus << std::endl;

                        // Write to result log
                        char csvSeparator = ',';
                        m_ResultLog.open("Logs/results.csv", std::ios_base::app);
                        m_ResultLog
                            << getCurrentTimeAsString() << csvSeparator
                            << pGame->GetPlayerNickname() << csvSeparator
                            << pGame->GetEnemyNickname() << csvSeparator
                            << resultTime << csvSeparator
                            << (pGame->GetPlayerNickname()==resultWinnerNickname) ? "win" : "loose" << csvSeparator
                            << resultWinnerNickname << csvSeparator
                            << resultWinnerNumberOfBots << csvSeparator
                            << resultLooserNickname << csvSeparator
                            << resultLooserNumberOfBots << csvSeparator
                            << std::endl;
                        m_ResultLog.close();

                        break;
                    }

                        //std::cout << "Time: " << timer.getTimeInMilliseconds() << " ms."
                    //    << " - Game UPDATEd.";


                    // update wait time and break if 
                    wait_time = end_time - GetTickCount();
                    if (wait_time < 0)
                        break;  // Send commands again
                }
            }

            // Rename the log files from the game after game ends.
            m_pLogger->close();

            std::string logFileName = getGameLogFilename(pGame->GetEnemyNickname());

            std::string  inLogFileName = "Logs/" + logFileName + "-in.txt";
            std::rename(m_szInputLogFilename.c_str(), inLogFileName.c_str());

            std::string  outLogFileName = "Logs/" + logFileName + "-out.txt";
            std::rename(m_szOutputLogFilename.c_str(), outLogFileName.c_str());
        }
	}

private:

    std::string getCurrentTimeAsString()
    {
        time_t rawtime;
        struct tm timeinfo;
        char buffer[80];

        time(&rawtime);
        localtime_s(&timeinfo, &rawtime);

        strftime(buffer, 80, "%Y-%m-%d-%I-%M-%S", &timeinfo);
        std::string str(buffer);
        return str;
    }

    std::string getGameLogFilename( 
        const std::string& enemyNickname
        )
    {
        return getCurrentTimeAsString() + "-" + enemyNickname;
    }

    void CheckStatusAndPrintMessage(const char *msg, const char* status)
    {
        Json::Reader reader;
        Json::Value json;
        reader.parse(msg, json);
        if (json["status"].asString() != status)
        {
            throw std::runtime_error(std::string("Expected status \"") + status + "\". Actual message " + msg);
        }

        std::cout << json["msg"].asString() << std::endl;
    }

	std::string GenerateHashValue(const char *random, const char *token)
	{
		std::string text = random;
        text += token;

		unsigned char buffer[20];
		sha1::calc(text.c_str(), text.size(), buffer);

        char ret[41];
		sha1::toHexString(buffer, ret);

		return ret;
	}

	TCPClient m_client;
    std::shared_ptr<Logger>  m_pLogger;
    std::ofstream   m_ResultLog;
    const std::string m_szInputLogFilename;
    const std::string m_szOutputLogFilename;

    const DWORD m_RequiredFrameTimeInMiliseconds = 200;
    DWORD m_FrameTimeSafetyMarginInMiliseconds;
    unsigned    m_nNumberOfCommandsWithoutTimeViolation;
};