#pragma once
#include <Windows.h>
#include "Serializer.hpp"
typedef std::pair<Command,std::pair<std::vector<VECTOR_TYPE>, std::vector<std::string>>> return_type;
typedef std::pair<Command, Package> decript_type;
class Messanger
{
private:
	HANDLE pipe;
	std::size_t msgSize;
	std::string createMSG(Command cmd, Package & pcg);//create message - header+package
	void sendTo(std::string &msg);
	std::optional <decript_type> decriptMSG(std::string& str);//decript part of message, to know size of msg
public:
	Messanger(HANDLE _pipe, size_t _msgSize) : pipe(_pipe), msgSize(_msgSize) {};//set pipe and maximum msg size
	void setPipe(HANDLE _pipe, size_t _msgSize);//same
	void sendStopMSG();//send msg to stop scanning
	void sendStartMSG(std::vector<std::string> stringArr);//send path file to scan
	void sendStartMSG(std::string str);
	void sendValue(Command cmd,std::vector<VECTOR_TYPE> vectorArr);//send files handle
	void sendValue(Command cmd, VECTOR_TYPE value);
	std::optional<return_type> getMSG();//read msg from pipe
};

