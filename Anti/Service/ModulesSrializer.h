#pragma once
#include <filesystem>
#include <string>
#include <fstream>
#include "timeStruct.h"
typedef std::pair < std::string, timeStruct> timeInfo;
namespace ModulesSrializer
{
	void serializePathArr(std::vector<std::filesystem::path>& _vec,std::filesystem::path _where);
	void serializeStrArr(std::vector<std::string>& _vec, std::filesystem::path _where);
	void serializeTimeInfo(std::vector<timeInfo>& _vec, std::filesystem::path _where);
	std::vector<std::filesystem::path> derializePathArr(std::filesystem::path _from);
	std::vector<std::string> derializeStrArr(std::filesystem::path _from);
	std::vector<timeInfo> derializeTimeInfoArr(std::filesystem::path _from);

};

