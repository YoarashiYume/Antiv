#pragma once
#include <filesystem>
#include <vector>
#include <algorithm>
typedef std::vector<std::filesystem::path> patVec;
class schrodingerData
{
	patVec distrustList;
	patVec quarantinList;
public:
	void addDistruct(std::string& addr);
	void addDistruct(std::filesystem::path& addr);
	bool moveToQuaranList(std::size_t id);
	bool itRemove(std::size_t id);
	bool restorFromQuarantine(std::size_t id);
	std::filesystem::path getPathDistrust(std::size_t id);
	std::filesystem::path getPathQuarantin(std::size_t id);
private:
	bool swap(patVec& from, patVec& to, std::size_t index);
};

