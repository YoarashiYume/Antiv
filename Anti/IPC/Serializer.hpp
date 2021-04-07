#pragma once
#ifdef MATHLIBRARY_EXPORTS
#define MATHLIBRARY_API __declspec(dllexport)
#else
#define MATHLIBRARY_API __declspec(dllimport)
#endif
#include <optional>
#include "Packages.hpp"

namespace Serializer
{

	/*serialize and deserialize different structure*/
	std::string serialize(Header obj);
	std::string serialize(Command serType, Package obj);
	std::optional<Header> deserializeHeader(std::string& msg);
	std::optional<Package> deserializePackage(std::string & msg);
	size_t countSize(std::vector<std::string> arr);
};


