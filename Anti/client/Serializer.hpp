#pragma once
#include <optional>
#include "Packages.hpp"
#include "../baseData/Record.hpp"

class Serializer
{
public:
	/*serialize and deserialize different structure*/
	static std::string serialize(Header obj);
	static std::string serialize(Command serType, Package obj);
	static std::string serialize(Record obj);
	static std::optional<Header> deserializeHeader(std::string& msg);
	static std::optional<Package> deserializePackage(std::string & msg);
	static std::optional<Record> deserializeRecord(std::string& msg);
private:
	static size_t countSize(std::vector<std::string> arr);
};


