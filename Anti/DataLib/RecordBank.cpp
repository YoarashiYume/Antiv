
#include "RecordBank.h"

DataIO::RecordBank::RecordBank(std::string const& _path)
{
	dr.reset(new DataReader());
	path = _path;
	dr.get()->setPath(_path);
	lSign = 0;
	fillData();
}

std::string DataIO::RecordBank::findRecord(std::string str, uint32_t startOffset)
{
	
	uint64_t sign;
	std::memcpy(&sign, str.data(), sizeof(uint64_t));//get 8 char in sign
	if (storage.find(sign)!=storage.end())//try to find same
	{
		auto options = storage.at(sign);
		for (auto& el : options)
			if (str.size() >= el.signSize)//compare length of full sign
			{
				std::string _str = str.substr(0, el.signSize);
				if (startOffset >= el.offsetStart && (startOffset + _str.size() <= el.offsetEnd))//compare offsets
					if (el.hash == shaGen.getSHA(_str))//compare sha256
						return el.name;//if all ok - return name(i forgot what i need)
			}

	}
	return {};//otherwise return empty
}

std::string DataIO::RecordBank::checkCascade(std::string str, uint32_t startOffset)
{
	/*use find*/
	std::string result;
	std::size_t stringOffset = 0;
	std::string temp(sizeof(uint64_t), 0);
	if (str.size() > storage.size())
	{
		for (auto& options : storage)
		{

			for (auto& el : options.second)
			{
				std::memcpy(temp.data(), &el.signature, sizeof(uint64_t));
				int64_t index = str.find(temp);
				if (index == std::string::npos)
					continue;
				if ((str.size() - index) >= el.signSize)//compare length of full sign
				{
					std::string _str = str.substr(index, el.signSize);
					if (startOffset + index >= el.offsetStart && (startOffset + index + _str.size() <= el.offsetEnd))//compare offsets
						if (el.hash == shaGen.getSHA(_str))//compare sha256
							return el.name;//if all ok - return name(i forgot what i need)
				}
			}
		}
	}
	else
	{
		while (str.length() - stringOffset > 8 && result.empty())
		{
			result = std::move(findRecord(str.substr(stringOffset), startOffset + stringOffset));
			++stringOffset;
		}
	}
	return result;
}

void DataIO::RecordBank::updateData()
{
	dr.get()->setPath(path);
	fillData();
}

void DataIO::RecordBank::changeFile(std::string const& _path)
{
	path = _path;
	storage.clear();
	updateData();
}

uint64_t DataIO::RecordBank::getLongestSign()
{
	return lSign;
}

void DataIO::RecordBank::fillData()
{
	while (true)
	{
		auto newRec = dr->readNext();//reading each transaction in file
		if (!newRec.has_value())
			break;
		if (storage.find(newRec.value().signature) == storage.end())
			storage.emplace(newRec.value().signature, std::vector{ newRec.value() });//if no such signature - create
		else
			storage.at(newRec.value().signature).push_back(newRec.value());//otherwise - ann record in vector
		lSign = lSign < newRec.value().signSize ? newRec.value().signSize : lSign;
	}
}
