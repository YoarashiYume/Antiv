#include "Messanger.hpp"

std::string Messanger::createMSG(Command cmd, Package & pcg)
{
	std::string msg = Serializer::serialize(cmd,pcg);
	Header head(cmd, msg.size() + 10);
	head.countOfPackage = ceil((double)head.size / msgSize);//counting count of sending 
	return (Serializer::serialize(head) + msg);
}

bool Messanger::sendTo(std::string& msg)
{
	std::size_t countOfPackage = Serializer::deserializeHeader(msg).value().countOfPackage;
	std::size_t offset{ 0 };
	DWORD count = 0;
	for (size_t i = 0; i < countOfPackage; ++i)
	{
		WriteFile(pipe, &msg[offset], msgSize, &count, 0);
		if (count == 0)
			return false;
		offset += msgSize;
	}
	return true;
}

std::optional <decript_type> Messanger::decriptMSG(std::string& str)
{
	auto tempHeader = Serializer::deserializeHeader(str);
	std::string last = str.substr(10);
	auto tempPackage{ Serializer::deserializePackage(last) };
	if (!tempHeader.has_value() || !tempPackage.has_value())
		return std::nullopt;
	return std::make_pair(tempHeader.value().command_type, tempPackage.value());
}

void Messanger::setPipe(HANDLE _pipe, size_t _msgSize)
{
	pipe = _pipe;
	msgSize = _msgSize;
}

bool Messanger::sendStopMSG()
{
	Package p;
	std::string msg = createMSG(Command::STOP_SCAN, p);
	return sendTo(msg);
}

bool Messanger::sendStartMSG(std::vector<std::string> stringArr)
{
	Package p;
	p.strArr = stringArr;
	std::string msg = createMSG(Command::START_SCAN, p);
	return sendTo(msg);
}

bool Messanger::sendStartMSG(std::string str)
{
	std::vector<std::string> temp{ str };
	return sendStartMSG(temp);
}

bool Messanger::sendValue(Command cmd, std::vector<VECTOR_TYPE> vectorArr)
{
	Package p;
	p.valueArr = vectorArr;
	std::string msg = createMSG(cmd, p);
	return sendTo(msg);
}

bool Messanger::sendValue(Command cmd, VECTOR_TYPE value)
{
	std::vector<VECTOR_TYPE> temp{ value };
	return sendValue(cmd,temp);
}

bool Messanger::sendCharArray(Command cmd, std::vector<std::string> stringArr)
{
	Package p;
	p.strArr = stringArr;
	std::string msg = createMSG(cmd, p);
	return sendTo(msg);
}

bool Messanger::sendCharArray(Command cmd, std::string str)
{
	std::vector<std::string> temp{ str };
	return sendCharArray(cmd, temp);
}

std::optional<return_type> Messanger::getMSG()
{
	std::string answer;
	DWORD count = 0;
	std::size_t offset{ 0 };
	answer.resize(msgSize);
	ReadFile(pipe, answer.data(), msgSize, &count, 0);
	if (count==0)
		return std::nullopt;
	Header temp = Serializer::deserializeHeader(answer).value();
	answer.resize(temp.size);
	offset += msgSize;
	for (size_t i = 1; i < temp.countOfPackage; ++i)
	{
		ReadFile(pipe, &answer[offset], msgSize, NULL, 0);
		offset += msgSize;
	}
	auto result = decriptMSG(answer);
	if (!result.has_value())
		return std::nullopt;
	return std::make_pair(result.value().first, std::make_pair(result.value().second.valueArr, result.value().second.strArr));
}
