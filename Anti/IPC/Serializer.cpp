#include "pch.h"
#include "Serializer.hpp"

std::string Serializer::serialize(Header obj)//serialize Header obj
{
	std::string buf;
	std::size_t offset{ 0 };
	buf.resize(sizeof(obj.size) + sizeof(obj.countOfPackage) + sizeof(obj.command_type));
	std::memcpy(&buf[offset], &obj.size, sizeof(obj.size));
	offset += sizeof(obj.size);
	std::memcpy(&buf[offset], &obj.countOfPackage, sizeof(obj.countOfPackage));
	offset += sizeof(obj.countOfPackage);
	std::memcpy(&buf[offset], &obj.command_type, sizeof(obj.command_type));
	offset += sizeof(obj.command_type);
	return buf;
}

std::string Serializer::serialize(Command serType,Package obj)//serialize Package obj
{
	std::string buf;
	std::size_t offset{ 0 };
	Package::PTYPE type;
	switch (serType)
	{
	case Command::STOP_SCAN:
		buf.resize(sizeof(type));
		type = Package::PTYPE::NUL;//to stop scanning. we are not interested in the content
		std::memcpy(&buf[offset], &type, sizeof(type));
		break;
	case Command::SCHEDUL:
	case Command::ADD_MONIT:
	case Command::START_SCAN:
	{
		type = Package::PTYPE::STR;
		int32_t strSize = obj.strArr.size();
		buf.resize(countSize(obj.strArr) + obj.strArr.size() * sizeof(strSize) + sizeof(Command) + sizeof(strSize));
		/* serialize sequentially
			packet_type number_of_transmitted_lines (line_size line)* */
		std::memcpy(&buf[offset], &type, sizeof(Command));
		offset += sizeof(Command);
		std::memcpy(&buf[offset], &strSize, sizeof(strSize));
		offset += sizeof(strSize);
		for (auto& el : obj.strArr)
		{
			strSize = el.size() + 1;
			std::memcpy(&buf[offset], &strSize, sizeof(strSize));
			offset += sizeof(strSize);
			std::memcpy(&buf[offset], el.data(), el.size() + 1);
			offset += el.size() + 1;
		}
		break;
	}
	case Command::REM_MONIT:
	case Command::MOV_TO_QUAR://in this case, the packages will have the same content
	case Command::DELETE_FILE:
		uint32_t sizet = obj.valueArr.size();
		type = Package::PTYPE::VEC;
		buf.resize(obj.valueArr.size() * sizeof(uint32_t) + sizeof(Command) + sizeof(sizet));
		/*serialize sequentially
			packet_type number_of_transmitted numbers array_of_numbers */
		std::memcpy(&buf[offset], &type, sizeof(Command));
		offset += sizeof(Command);
		std::memcpy(&buf[offset], &sizet, sizeof(sizet));
		offset += sizeof(uint32_t);
		std::memcpy(&buf[offset], obj.valueArr.data(), obj.valueArr.size() * sizeof(VECTOR_TYPE));
		break;
	}
	return buf;
}


std::optional<Header> Serializer::deserializeHeader(std::string& msg)
{
	if (!msg.empty())
	{
		Header temp;
		std::memcpy(&temp, msg.data(), sizeof(Header));
		return temp;
	}
	return std::nullopt;
}

std::optional<Package> Serializer::deserializePackage(std::string& msg)
{
	if (!msg.empty())
	{
		Package temp;
		std::size_t offset{ 0 };
		Package::PTYPE type;
		std::memcpy(&type, msg.data() + offset, sizeof(Command));
		/*read the packet type*/
		offset += sizeof(Command);
		switch (type)//then read in order when serializing
		{
		case Package::PTYPE::NUL:
			break;
		case Package::PTYPE::STR:
			uint32_t arrSize;
			uint32_t elSize;
			std::memcpy(&arrSize, msg.data() + offset, sizeof(arrSize));
			offset += sizeof(arrSize);
			temp.strArr.resize(arrSize);
			for (size_t i = 0; i < arrSize; ++i)
			{
				std::memcpy(&elSize, msg.data() + offset, sizeof(elSize));
				offset += sizeof(elSize);
				temp.strArr.at(i).resize(elSize);
				std::memcpy(temp.strArr.at(i).data(), msg.data() + offset, elSize);
				offset += elSize;
			}
			break;
		case Package::PTYPE::VEC:
			uint32_t sizet;
			std::memcpy(&sizet, msg.data() + offset, sizeof(sizet));
			temp.valueArr.resize(sizet);
			offset += sizeof(sizet);
			std::memcpy(temp.valueArr.data(), msg.data() + offset, temp.valueArr.size() * sizeof(VECTOR_TYPE));
			break;
		}
		return temp;
	}
	return std::nullopt;
}


size_t Serializer::countSize(std::vector<std::string> arr)
{
	std::size_t size{ 0 };
	for (auto& el : arr)
		size += el.size() + 1;
	return size;
}
