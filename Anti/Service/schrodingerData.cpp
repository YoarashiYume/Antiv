#include "schrodingerData.h"

schrodingerData::schrodingerData()
{
	tryToRestore();
}

std::vector<std::string> schrodingerData::getDist()
{
	std::vector<std::string> tempArr;
	distrustList.erase(std::unique(distrustList.begin(), distrustList.end()), distrustList.end());
	for (auto& el : distrustList)
		tempArr.emplace_back(el.string());
	return tempArr;
}

std::vector<std::string> schrodingerData::getQuar()
{
	std::vector<std::string> tempArr;
	quarantinList.erase(std::unique(quarantinList.begin(), quarantinList.end()), quarantinList.end());
	for (auto& el : quarantinList)
		tempArr.emplace_back(el.string());
	return tempArr;
}

void schrodingerData::addDistruct(std::string& addr)
{
	std::filesystem::path temp{ addr };
	addDistruct(temp);
}

void schrodingerData::addDistruct(std::filesystem::path& addr)
{
	if (std::find_if(distrustList.begin(), distrustList.end(), [&](std::filesystem::path& el) {return el == addr; })==distrustList.end())
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
	return id < quarantinList.size() ? quarantinList.at(id) : std::move(std::filesystem::path{});
}

void schrodingerData::saveData()
{
	ModulesSrializer::serializePathArr(distrustList, std::filesystem::current_path().string() + "\\Distr.bin");
	ModulesSrializer::serializePathArr(quarantinList, std::filesystem::current_path().string() + "\\Quar.bin");
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

void schrodingerData::tryToRestore()
{
	this->distrustList = ModulesSrializer::derializePathArr(std::filesystem::current_path().string() + "\\Distr.bin");
	patVec tempQuar = ModulesSrializer::derializePathArr(std::filesystem::current_path().string() + "\\Quar.bin");
	patVec recover;
	auto pat = std::filesystem::current_path().parent_path().concat("\\TempQuar\\");

	if (std::filesystem::exists(pat))
		for (auto& p : std::filesystem::directory_iterator(pat))
			recover.emplace_back(p.path());
	for (auto& el : recover)
	{
		auto res = std::find_if(tempQuar.begin(), tempQuar.end(), [el](std::filesystem::path a) {return a.filename() == el.filename(); });
		if (res != tempQuar.end())
			this->quarantinList.emplace_back(*res);
	}


}

