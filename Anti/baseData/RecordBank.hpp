#pragma once
#include <map>
#include <vector>
#include "RecordData.hpp"
#include "SHA256.h"
class RecordBank
{
private:
	std::map<uint64_t, std::vector<Record>> storage;//malware storage
	DataReader* dr;//can read only
	uint32_t countOfRecord;//it just exists
	SHA256 sha;
	void fillData();//strart filling
public:
	RecordBank(std::string const& _path);
	~RecordBank();
	std::string findRecord(std::string str,uint32_t startPoint);//try to find record
};

