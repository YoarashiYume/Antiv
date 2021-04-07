#pragma once

#include <vector>
#include <map>
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
	private:
		std::map<uint64_t, std::vector<Record>> storage;//malware storage
		std::string path;
		std::unique_ptr<DataReader> dr;
		SHA256 shaGen;
		void fillData();//strart filling
	};
}

