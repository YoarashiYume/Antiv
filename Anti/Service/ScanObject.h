#pragma once
#include <filesystem>
enum class ObjectType
{
	ZIP,EXE,UNKNOWN
};
struct ScanObject
{
	std::filesystem::path filePath;
	ObjectType objType;
};