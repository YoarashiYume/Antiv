#pragma once
#include "Record.hpp"
#include "../client/Serializer.hpp"
#include <fstream>
#include <optional>
class DataWriter
{
public:
	bool writeIn(Record const& rec);
	DataWriter(std::string const& _path);
private:
	std::fstream fileStream;
	std::string path;
	uint32_t countOfRecords = 0;
	const std::string baseIndex{ "Nadyezhniy\0" };
	void createData();
};
class DataReader
{
public:
	DataReader(std::string const& _path);
	~DataReader();
	bool isFile();
	uint32_t getInfo();
	std::optional<Record>  readNext();
private:
	uint32_t currentCount = 0, countOfRecord = 0;
	const std::string baseIndex{ "Nadyezhniy\0" };
	uint64_t offset = 0;
	std::ifstream fileStream;
	std::string path;
};