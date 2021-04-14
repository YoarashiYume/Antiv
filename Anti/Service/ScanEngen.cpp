#include "ScanEngen.h"

void Engen::ScanEngen::remuse()
{
	isStopped.store(false);
}

std::string Engen::ScanEngen::scanEXE(ScanObject const& obj)
{
	uint64_t offset{0};
	uint64_t fSize = 0;
	std::ifstream stream(obj.filePath,std::ios::binary);
	fSize = std::filesystem::file_size(obj.filePath);
	std::string buf(bufSize, 0);
	std::string res;
	do
	{
		stream.read(buf.data(), bufSize);
		res = storage->checkCascade(buf, offset);		
		if (!res.empty())
			return res;
		offset += bufSize - this->safeOffsetBack;
		stream.seekg(offset);
	} while (!stream.eof() && offset < fSize);
	return {};
}


Engen::ScanEngen::ScanEngen(std::shared_ptr<DataIO::RecordBank> _storage, std::shared_ptr<FileWorker> _fw)
{
	storage = _storage;
	fw = _fw;
	safeOffsetBack = storage->getLongestSign();
	isStopped.store(false);
}

void Engen::ScanEngen::stopScan()
{
	isStopped.store(true);
}

bool Engen::ScanEngen::isStop()
{
	return isStopped.load();
}

std::string Engen::ScanEngen::scan(ScanObject const& obj)
{
	if (isStopped.load())
		return {};
	switch (obj.objType)
	{
	case ObjectType::EXE:
		return scanEXE(obj);
		break;
	case ObjectType::ZIP:
	{
		std::string result;
		std::vector<std::string> extractFolder = { fw->extractZip(obj.filePath).string() };
		if (!extractFolder.front().empty())
		{
			auto objVec = Engen::scanGen(extractFolder);
			for (auto& el : objVec)
			{
				result = scan(el);
				if (!result.empty())
					break;
			}
		}
		fw->clearZip(obj.filePath);
		return result;
		break;
	}
	default:
		return {};
		break;
	}
}


std::vector<ScanObject> Engen::scanGen(std::vector<std::string>& _pathArrayStr)
{
	std::vector<ScanObject> res;
	std::ifstream fs;
	uint16_t mzHeader = 0;
	uint32_t zipHeader = 0;
	for (uint64_t i = 0; i < _pathArrayStr.size(); ++i)
	{
		auto& el = _pathArrayStr.at(i);
		fs.open(el);
		if (!fs.is_open())
		{
			fs.close();
			if (std::filesystem::is_directory(el))
			{
				for (auto& p : std::filesystem::directory_iterator(el))
					_pathArrayStr.emplace_back(p.path().string());
			}
			continue;
		}
		fs.read((char*)&mzHeader, sizeof(uint16_t));
		fs.seekg(0);
		fs.read((char*)&zipHeader, sizeof(uint32_t));
		ScanObject sObj;
		sObj.filePath = el;
		if (mzHeader == mzHeaderConst)
			sObj.objType = ObjectType::EXE;
		else if (zipHeaderConst == zipHeader)
			sObj.objType = ObjectType::ZIP;
		else
			sObj.objType = ObjectType::UNKNOWN;
		res.emplace_back(sObj);
		fs.close();
	}
	return res;
}
