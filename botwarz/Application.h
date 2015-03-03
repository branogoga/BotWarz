#pragma once

#include "jsoncpp/include/json/json.h"
#include "sha1/sha1.h"

#include "Consts.h"
#include "Game.h"
#include "GameFactory.h"
#include "Messages.h"
#include "TCPClient.h"

#include <string>
#include <memory>

class Application
{
    const DWORD REQUIRED_FRAME_TIME_IN_MILISECONDS = 200;
    const DWORD SAFETY_MARGIN = 30;

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
        while (true)
        {
            // get game data info
            msg = m_client.ReceiveLine();

            reader.parse(msg, json);
            InitializeGame(json);

            // loop for one game
            bool is_finished = false;
            while (!is_finished)
            {
                // send command on server
                std::string szMoveMessage = Message::MoveBots(
                    m_pGame->getMyPlayer(),
                    m_pGame->getOtherPlayer()
                    );

                m_client.Send(szMoveMessage);

                DWORD end_time = GetTickCount() + FRAME_TIME;

                int wait_time = end_time - GetTickCount();
                while (m_client.WaitForMessage(wait_time < 0 ? 0 : wait_time))
                {
                    msg = m_client.ReceiveLine();

                    // HERE YOU CAN UPDATE YOU GAME STATE AND PARSE ERRORS OR RESULT MESSAGE

                    // we just check if game is not finished and if yes, then break loop
                    reader.parse(msg, json);
                    if (!json["result"].isNull())
                    {
                        is_finished = true;
                        std::cout << json["result"]["status"] << std::endl;
                        break;
                    }

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

    void    InitializeGame( const Json::Value& json )
    {
        BotWarz::GameFactory    gameFactory;

        const char* jsonKeyGame = "game";
        Json::Value jsonGame = json[jsonKeyGame];
        m_pGame = gameFactory.createFromJson(jsonGame);

        std::cout << *m_pGame;
    }


	TCPClient m_client;
    std::shared_ptr<BotWarz::Game>   m_pGame;
    /*TMP*/std::vector<int> my_bots_indices;/*TMP*/
};