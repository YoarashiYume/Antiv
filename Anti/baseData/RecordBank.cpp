#include "RecordBank.hpp"

void RecordBank::fillData()
{
	while (true)
	{
		auto newRec = dr->readNext();//reading each transaction in file
		if (!newRec.has_value())
			break;
		if (!storage.contains(newRec.value().signature))
			storage.emplace(newRec.value().signature, std::vector{ newRec.value() });//if no such signature - create
		else
			storage.at(newRec.value().signature).push_back(newRec.value());//otherwise - ann record in vector
	}
	countOfRecord = dr->getInfo();//it just exists
}

RecordBank::RecordBank(std::string const& _path)
{
	dr = new DataReader(_path);
	fillData();
}

RecordBank::~RecordBank()
{
	delete dr;
}

std::string RecordBank::findRecord(std::string str, uint32_t startPoint)
{
	uint64_t sign;
	std::memcpy(&sign, str.data(), sizeof(uint64_t));//get 8 char in sign
	if (storage.contains(sign))//try to find same
	{
		auto options = storage.at(sign);
		for (auto &el : options)
		{
			if (str.size()==el.signSize)//compare length of full sign
				if (startPoint >= el.offsetStart && (startPoint + str.size() <= el.offsetEnd))//compare offsets
				{
					sha.update(str);
					if (el.hash == SHA256::toString(sha.digest()))//compare sha256
						return el.name;//if all ok - return name(i forgot what i need)
				}
					
		}
	}
	return {};//otherwise return empty
}
