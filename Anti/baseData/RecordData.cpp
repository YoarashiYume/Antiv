#include "RecordData.hpp"

bool DataWriter::writeIn(Record const& rec)
{
	std::string reader{ };
	reader.resize(baseIndex.size());
	fileStream.open(path, std::ios::in | std::ios::out | std::ios::binary);
	if (!fileStream.is_open())
		return false;
	fileStream.read(reader.data(), reader.size());
	if (reader != baseIndex)
		return false;
	uint32_t count;
	fileStream.read(&reader[0], sizeof(count));
	std::memcpy(&count, &reader[0], sizeof(count));
	fileStream.close();
	fileStream.open(path, std::ios::in | std::ios::out | std::ios::binary);
	fileStream.seekp(baseIndex.size());
	++count;
	reader.resize(sizeof(count));
	std::memcpy(&reader[0], &count, sizeof(count));
	fileStream.write(reader.data(), sizeof(count));
	std::string recInf = Serializer::serialize(rec);
	fileStream.seekg(baseIndex.size() + sizeof(count) + (count - 1) * recInf.size());
	fileStream.write(recInf.data(), recInf.size());
	fileStream.close();
	return true;
}

DataWriter::DataWriter(std::string const& _path)
{
	fileStream.open(_path, std::ios::_Nocreate);
	if (!fileStream.is_open() || fileStream.fail())
	{
		path = "baseData.txt";
		createData();
	}
	else
		path = _path;
	fileStream.close();
}

void DataWriter::createData()
{
	std::ofstream fs(path, std::ios::binary);
	uint32_t count = 0;
	fs.write(baseIndex.data(), baseIndex.size());
	fs.write((char*)&count, sizeof(uint32_t));
	fs.close();
}

DataReader::DataReader(std::string const& _path)
{
	path = _path;
	fileStream.open(path, std::ios::out | std::ios::binary);
}

DataReader::~DataReader()
{
	fileStream.close();
}

bool DataReader::isFile()
{
	return (fileStream.is_open() && !fileStream.fail());
}

uint32_t DataReader::getInfo()
{
	std::string buf;
	buf.resize(baseIndex.size());
	fileStream.read(&buf[0], buf.size());
	if (buf != baseIndex)
	{
		fileStream.close();
		return 0;
	}
	offset += buf.size();
	fileStream.read(&buf[0], sizeof(uint32_t));
	offset += sizeof(uint32_t);
	std::memcpy(&countOfRecord, &buf[0], sizeof(uint32_t));
	return countOfRecord;
}

std::optional<Record> DataReader::readNext()
{
	if (fileStream.eof() || currentCount == countOfRecord)
		return std::nullopt;
	std::string buf;
	buf.resize(recordSize);
	fileStream.read(&buf[0], recordSize);
	offset += recordSize;
	return Serializer::deserializeRecord(buf);
}
