#pragma once
#include <filesystem>
#include "ScanEngen.h"
#include <memory>
#include <unordered_map>
#include <vector>
#include <thread>
#include <mutex>
#include <chrono>
#include "schrodingerData.h"
#include <atomic>
#include "ModulesSrializer.h"

class Monitor
{
private:
	std::shared_ptr<Engen::ScanEngen> scEn;
	std::shared_ptr<schrodingerData> data;
	std::vector<std::filesystem::path> monitorFile;
	std::unordered_map<std::string, std::filesystem::file_time_type> fileMonitoring;
	bool contains(std::string path);
	std::mutex mutex;
	std::atomic_bool findMutex;
	void tryToRestore();
public:
	Monitor(std::shared_ptr<Engen::ScanEngen> _scEn, std::shared_ptr<schrodingerData> _data);
	std::vector<std::string> getList();
	bool addFile(std::filesystem::path _path);
	bool removeFile(std::size_t index);
	void start();
	bool isFoundSmt();
	void saveData();
};

