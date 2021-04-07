#include "pch.h"
#include "DataIO.h"


void DataIO::DataReader::setPath(std::string _path)
{
	if (!isCorrectData(_path))
		return;
	path = _path;
	reopen(0);
	offset = 0;
}

std::optional<DataIO::Record> DataIO::DataReader::readNext()
{
	if (stream.eof() || !stream.is_open())
		if (!reopen(offset + std::strlen(DataIO::dataIndex) + sizeof(uint32_t)))
			return std::nullopt;
	std::string buf;
	buf.resize(recordSize + 1);
	if (offset == 0)
		stream.seekg(std::strlen(DataIO::dataIndex) + sizeof(uint32_t));
	stream.read(&buf[0], recordSize + 1);
	offset += recordSize + 1;
	if (buf.at(0) == '\0')
	{
		offset -= recordSize + 1;
		return std::nullopt;
	}
	auto temp = this->deserializeRecord(buf);
	if (!temp.has_value())
	{
		offset -= recordSize + 1;
		reopen(offset + std::strlen(DataIO::dataIndex) + sizeof(uint32_t));
	}
	return temp;
}

DataIO::DataReader::DataReader()
{
}

DataIO::DataReader::~DataReader()
{
	stream.close();
}
std::optional<DataIO::Record> DataIO::DataReader::deserializeRecord(std::string& msg)
{
	if (msg.size() < DataIO::recordSize)
		return std::nullopt;
	//then read in order when serializing
	std::string buf;
	std::size_t offset{ 0 };
	auto deserFunc = [&](uint32_t size, auto&& _where) {
		std::memcpy(&_where, msg.data() + offset, size);
		offset += size;
	};
	DataIO::Record temp;
	temp.name.resize(DataIO::nameSize);
	temp.hash.resize(DataIO::hashSize);
	deserFunc(DataIO::nameSize, *temp.name.data());
	deserFunc(sizeof(temp.dangerLvl), temp.dangerLvl);
	deserFunc(sizeof(temp.signature), temp.signature);
	deserFunc(sizeof(temp.signSize), temp.signSize);
	deserFunc(DataIO::hashSize, *temp.hash.data());
	deserFunc(sizeof(temp.offsetStart), temp.offsetStart);
	deserFunc(sizeof(temp.offsetEnd), temp.offsetEnd);
	return temp;
}

bool DataIO::DataReader::reopen(std::size_t _offset)
{
	stream.close();
	stream.open(path, std::ios::out | std::ios::binary);
	stream.seekg(_offset);
	return !stream.eof() && stream.is_open();
}
std::string DataIO::createData()
{
	std::string path = std::filesystem::current_path().string() + "\\baseData.bin";
	uint64_t count = 0;
	std::ofstream outFile(path, std::ios::binary | std::ios::trunc);
	outFile.write(DataIO::dataIndex,std::strlen(DataIO::dataIndex));
	outFile.write((char*)&count, sizeof(count));
	outFile.close();
	return path;
}

bool DataIO::isCorrectData(std::string& _path)
{
	std::ifstream ch(_path);
	if (ch.is_open())
	{
		std::string reader;
		reader.resize(std::strlen(DataIO::dataIndex));
		ch.read(reader.data(), reader.size());
		ch.close();
		return std::strcmp(reader.data(), dataIndex) == 0;
	}
	return false;
}



DataIO::DataWriter::DataWriter(){}

DataIO::DataWriter::~DataWriter()
{
}

std::string DataIO::DataWriter::serialize(DataIO::Record obj)
{
	std::string buf{};
	std::size_t offset{ 0 };
	auto serFunc = [&](uint32_t size, auto&& what) {
		std::memcpy(&buf[offset], &what, size);
		offset += size;
	};
	buf.resize(DataIO::nameSize + DataIO::hashSize + sizeof(uint8_t) + sizeof(uint32_t) + 3 * sizeof(uint64_t) + sizeof(DataIO::FILETYPE));
	/*serialize sequentially
			malware_name dangerLevel PartOfSignature signatureLength SHA256 offsets */
	obj.name.resize(DataIO::nameSize);
	serFunc(DataIO::nameSize, *obj.name.data());
	serFunc(sizeof(obj.dangerLvl), obj.dangerLvl);
	serFunc(sizeof(obj.signature), obj.signature);
	serFunc(sizeof(obj.signSize), obj.signSize);
	serFunc(DataIO::hashSize, *obj.hash.data());
	serFunc(sizeof(obj.offsetStart), obj.offsetStart);
	serFunc(sizeof(obj.offsetEnd), obj.offsetEnd);
	return buf;
}

bool DataIO::DataWriter::writeInRec(Record& rec)
{
	std::string reader{ };
	reader.resize(std::strlen(DataIO::dataIndex));
	std::fstream stream(path, std::ios::in | std::ios::out | std::ios::binary);
	if (!stream.is_open())
		return false;
	stream.read(reader.data(), reader.size());
	if (std::strcmp(reader.data(), dataIndex) != 0)
		return false;
	uint32_t count;
	stream.read(&reader[0], sizeof(count));
	std::memcpy(&count, &reader[0], sizeof(count));
	stream.close();
	stream.open(path, std::ios::in | std::ios::out | std::ios::binary);
	stream.seekp(std::strlen(DataIO::dataIndex));
	++count;
	reader.resize(sizeof(count));
	std::memcpy(&reader[0], &count, sizeof(count));
	stream.write(reader.data(), sizeof(count));
	std::string recInf = this->serialize(rec);
	stream.seekg(std::strlen(DataIO::dataIndex) + sizeof(count) + (count - 1) * recInf.size());
	stream.write(recInf.data(), recInf.size());
	stream.close();
	return true;
}



bool DataIO::DataWriter::writeIn(std::string _sign, std::string _malvareName, uint32_t _startOffset, uint32_t _endOffset, FILETYPE _type)
{
	Record temp;
	temp.name = _malvareName.substr(0, 10);
	temp.dangerLvl = 0;
	temp.offsetEnd = _endOffset;
	temp.offsetStart = _startOffset;
	temp.type = _type;
	temp.signSize = _sign.length();
	temp.hash = sha.getSHA(_sign);
	std::memcpy(&temp.signature, _sign.data(), sizeof(temp.signature));
	return this->writeInRec(temp);
}

void DataIO::DataWriter::setPath(std::string _path)
{
	path = _path;
}
