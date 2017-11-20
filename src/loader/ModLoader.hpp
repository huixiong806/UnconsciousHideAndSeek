#pragma once
#include <vector>
#include <string>
#include <io.h>
#include <Json.hpp>
class ModLoader
{
private:
public:
	static std::string getModName(std::string path)
	{
		using json = nlohmann::json;
		json info;
		std::ifstream file(path + "/info.json");
		file >> info;
		return info["name"];
	}
	
};