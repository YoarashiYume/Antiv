#pragma once
#include <filesystem>
#include <fstream>
#include <optional>
#include "SHA256.h"
namespace DataIO
{
	constexpr char dataIndex[] = "Nadyezhniy";
	constexpr const size_t nameSize = 10;
	constexpr const size_t hashSize = 64;
	constexpr const size_t recordSize = 103;
	
	std::string createData();
	bool isCorrectData(std::string& _path);
	
	enum class FILETYPE :uint8_t
	{
		UNKNOWN,
		ZIP,
		EXE
	};
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

	class DataReader
	{
	public:
		void setPath(std::string _path);
		std::optional<DataIO::Record> readNext();
		DataReader();
		~DataReader();
	protected:
		std::optional<DataIO::Record> deserializeRecord(std::string& msg);
		bool reopen(std::size_t _offset);
		std::ifstream stream;
		std::string path;
		uint64_t offset = 0;
	};
	class DataWriter
	{
	public:
		DataWriter();
		~DataWriter();
		void setPath(std::string _path);
		bool writeIn(std::string _sign, std::string _malvareName, uint32_t _startOffset, uint32_t _endOffset, FILETYPE _type);
	private:
		std::string serialize(DataIO::Record obj);
		bool writeInRec(Record& rec);
		std::fstream stream;
		std::string path;
		uint32_t countOfRecords = 0;	
		SHA256 sha;
	};
	
}

