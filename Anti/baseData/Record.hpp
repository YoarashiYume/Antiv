#pragma once
#include <string>
enum class FILETYPE :uint8_t
{
	UNKNOWN
};
const size_t nameSize = 10;
const size_t hashSize = 64;
const size_t recordSize = 103;
struct Record
{
	std::string name;
	uint8_t dangerLvl;
	uint32_t signSize;
	std::string hash;
	uint64_t offsetStart, offsetEnd, signature;
	FILETYPE type;
	Record() : name("unknown"),
		dangerLvl(0), signature(0), signSize(0), offsetStart(0), offsetEnd(0), type(FILETYPE::UNKNOWN) {};
};