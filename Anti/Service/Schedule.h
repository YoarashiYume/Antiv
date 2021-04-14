#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <chrono>
#include "ModulesSrializer.h"
#include "ScanEngen.h"
#include "timeStruct.h"
#include <algorithm>
#include "schrodingerData.h"
#include <memory>
#include <vector>
#include <mutex>
#include <thread>
class Schedule
{
	typedef std::pair < std::string, timeStruct> innerInfo;
private:
	std::mutex mutex;
	std::vector<innerInfo> schList;
	std::vector<std::string> detected;
	std::shared_ptr<Engen::ScanEngen> scEn;
	void getTime(timeStruct& ts);
	void tryToRestore();
public:
	Schedule(std::shared_ptr<Engen::ScanEngen> _scEn);
	std::vector<std::string> getList();
	bool start();
	bool addEl(std::string info);
	void clear();
	std::vector<std::string> isFindSmt();
	void saveData();
};

