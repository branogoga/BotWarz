#pragma once

#include "jsoncpp/include/json/json.h"
#include "sha1/sha1.h"

#include "BotWarz/Application.h"

#include "Consts.h"
#include "Messages.h"
#include "TCPClient.h"
#include "Timer.h"
#include "Utils.h"

#include <string>
#include <memory>
#include <assert.h>

class Application
{
    const DWORD REQUIRED_FRAME_TIME_IN_MILISECONDS = 200;
    const DWORD SAFETY_MARGIN = 5;

	const DWORD FRAME_TIME = REQUIRED_FRAME_TIME_IN_MILISECONDS + SAFETY_MARGIN;

public:

    Application()
        : m_client(SERVER_NAME, SERVER_PORT)
    {
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

            Timer timer;

            // loop for one game
            bool is_finished = false;
            while (!is_finished)
            {
                // send command on server
                std::string szMoveMessage = pGame->GetMove();
                m_client.Send(szMoveMessage);

                //std::cout << "Time: " << timer.getTimeInMilliseconds() << " ms."
                //    << " - Sending MOVE command.";

                DWORD end_time = GetTickCount() + FRAME_TIME;

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
                        end_time = GetTickCount() + FRAME_TIME;
                    }

                    //if (!json["play"].isNull())
                    //{
                        pGame->Update(json);
                    //}

                    if (!json["result"].isNull())
                    {
                        is_finished = true;
                        std::cout << json["result"]["status"] << std::endl;
                        break;
                    }

                        //std::cout << "Time: " << timer.getTimeInMilliseconds() << " ms."
                    //    << " - Game UPDATEd.";


                    // update wait time and break if 
                    wait_time = end_time - GetTickCount();
                    if (wait_time < 0)
                        break;
                }
            }
        }
	}

private:

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
};