#include "Schedule.h"

void Schedule::getTime(timeStruct& ts)
{
	std::time_t t = std::time(0); 
	std::tm* now = std::localtime(&t);
	ts.hour = now->tm_hour;
	ts.min = now->tm_min;
}


Schedule::Schedule(std::shared_ptr<Engen::ScanEngen> _scEn)
{
	scEn = _scEn;
	tryToRestore();
}

std::vector<std::string> Schedule::getList()
{
	std::vector<std::string> vec;
	for (auto& el : schList)
		vec.emplace_back(el.first + " " + std::to_string(el.second.hour) + ":" + std::to_string(el.second.min));
	return vec;
}

bool Schedule::start()
{
	innerInfo firstEl;
	timeStruct tm;
	while (true)
	{
		std::this_thread::sleep_for(std::chrono::seconds(60));
		mutex.lock();
		if (schList.size() == 0)
		{
			mutex.unlock();
			continue;
		}
		getTime(tm);
		if (!(firstEl == schList.front()))
			firstEl = schList.front();
		if (firstEl.second > tm)
		{
			mutex.unlock();
			continue;
		}
		std::vector<std::string> vecStr = { firstEl.first };
		auto vec = Engen::scanGen(vecStr);
		for (auto& el : vec)
			if (!scEn->scan(el).empty())
				detected.emplace_back(el.filePath.string());
		schList.erase(schList.begin());
		mutex.unlock();
	}
	return false;
}

bool Schedule::addEl(std::string info)
{
	std::lock_guard<std::mutex> lg(mutex);
	std::string buf = info.substr(info.size() - 5);
	std::string path = info.substr(0, info.size() - 6);
	timeStruct tm;
	tm.setTime(std::stoi(buf.substr(0, 2)), std::stoi(buf.substr(3, 2)));
	schList.emplace_back(std::make_pair( path,tm ));
	std::sort(schList.begin(), schList.end(),
		[](innerInfo& el1, innerInfo& el2)
		{ return el1.second < el2.second; });
	return true;
}

void Schedule::clear()
{
	schList.clear();
}

std::vector<std::string> Schedule::isFindSmt()
{
	std::lock_guard<std::mutex> lg(mutex);
	auto tempVec = detected;
	detected.clear();
	return tempVec;
}
void Schedule::tryToRestore()
{
	detected = ModulesSrializer::derializeStrArr(std::filesystem::current_path().string() + "\\Det.bin");
	schList = ModulesSrializer::derializeTimeInfoArr(std::filesystem::current_path().string() + "\\Schedule.bin");
}

void Schedule::saveData()
{
	ModulesSrializer::serializeStrArr(detected, std::filesystem::current_path().string() + "\\Det.bin");
	ModulesSrializer::serializeTimeInfo(schList, std::filesystem::current_path().string() + "\\Schedule.bin");
}
