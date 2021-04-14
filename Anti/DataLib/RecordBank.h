#pragma once

#include <vector>
#include <unordered_map>
#include <memory>
#include "SHA256.h"
#include "DataIO.h"
namespace DataIO
{
	class RecordBank
	{
	public:
		RecordBank(std::string const& _path);
		std::string findRecord(std::string str, uint32_t startOffset);//try to find record
		std::string checkCascade(std::string str, uint32_t startOffset);
		void updateData();
		void changeFile(std::string const& _path);
		uint64_t getLongestSign();
	private:
		std::unordered_map<uint64_t, std::vector<Record>> storage;//malware storage
		std::string path;
		uint64_t lSign;
		std::unique_ptr<DataReader> dr;
		SHA256 shaGen;
		void fillData();//strart filling
	};
}

