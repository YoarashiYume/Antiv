#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "ScanObject.h"
#include "RecordBank.h"
#include "FileWorker.h"
#include <memory>
#include <atomic>
#include <fstream>
#include <iostream>

namespace Engen
{
	std::vector<ScanObject> scanGen(std::vector<std::string>& _pathArrayStr);
	constexpr int mzHeaderConst = 0x5a4d;
	constexpr int zipHeaderConst = 0x04034b50;
	constexpr int bufSize = 1024;
	class ScanEngen
	{
	private:
		std::shared_ptr<FileWorker> fw;
		std::shared_ptr<DataIO::RecordBank> storage;
		std::atomic_bool isStopped;
		
		std::string scanEXE(ScanObject const& obj);
		uint64_t safeOffsetBack;
	public:
		ScanEngen(std::shared_ptr<DataIO::RecordBank> _storage, std::shared_ptr<FileWorker> _fw);
		void stopScan();
		void remuse();
		bool isStop();
		std::string scan(ScanObject const& obj);
	};

}