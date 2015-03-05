#pragma once

#include "jsoncpp/include/json/json.h"

namespace Message
{
	std::string Connect(const char *name, const char *hash)
	{
		Json::Value root;
		root["login"]["nickname"] = name;
		root["login"]["hash"] = hash;

		Json::FastWriter writer;
		return writer.write(root);
	}
};

