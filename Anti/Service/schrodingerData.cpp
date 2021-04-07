#include "schrodingerData.h"

void schrodingerData::addDistruct(std::string& addr)
{
	std::filesystem::path temp{ addr };
	addDistruct(temp);
}

void schrodingerData::addDistruct(std::filesystem::path& addr)
{
	this->distrustList.emplace_back(addr);
}

bool schrodingerData::moveToQuaranList(std::size_t id)
{
	return swap(distrustList, quarantinList, id);
}

bool schrodingerData::itRemove(std::size_t id)
{
	if (distrustList.size() > id)
	{
		distrustList.erase(distrustList.begin() + id);
		return true;
	}
	return false;
}

bool schrodingerData::restorFromQuarantine(std::size_t id)
{
	return swap(quarantinList,distrustList, id);
}

std::filesystem::path schrodingerData::getPathDistrust(std::size_t id)
{
	return id < distrustList.size() ? distrustList.at(id) : std::move(std::filesystem::path{});
}

std::filesystem::path schrodingerData::getPathQuarantin(std::size_t id)
{
	return id < distrustList.size() ? quarantinList.at(id) : std::move(std::filesystem::path{});
}

bool schrodingerData::swap(patVec& from, patVec& to, std::size_t index)
{
	if (from.size() > index)
	{
		to.emplace_back(from.at(index));
		from.erase(from.begin() + index);
		return true;
	}
	return false;
}

