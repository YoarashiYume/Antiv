#include "FileWorker.h"
#include "Messanger.hpp"
#include "RecordBank.h"
#include "schrodingerData.h"

HANDLE pipe,pipeBack;
Messanger* pipeIO,*pipeIOBack;
schrodingerData data;
FileWorker fw;
void movment(return_type& param)
{
	Command cmd = param.first;
	switch (cmd)
	{
	case Command::START_SCAN:
		/*magic plz*/
		break;
	case Command::STOP_SCAN:
		/*magic plz*/
		break;
	case Command::MOV_TO_QUAR:
		for (auto& el : param.second.first)
		{
			int callbackInfo = -1;
			if (fw.moveToQuar(data.getPathDistrust(el)))
				if (data.moveToQuaranList(el))
					callbackInfo = el;
			pipeIOBack->sendValue(Command::MOV_TO_QUAR, callbackInfo);
		}
		break;
	case Command::DELETE_FILE:
		for (auto& el : param.second.first)
		{
			int callbackInfo = -1;
			if (fw.removeFile(data.getPathDistrust(el)))
				if (data.itRemove(el))
					callbackInfo = el;
			pipeIOBack->sendValue(Command::DELETE_FILE, callbackInfo);
		}
		break;
	case Command::BACK_FROM_QUAR:
		for (auto& el : param.second.first)
		{
			int callbackInfo = -1;
			if (fw.recoverFile(data.getPathDistrust(el)))
				if (data.restorFromQuarantine(el))
					callbackInfo = el;
			pipeIOBack->sendValue(Command::BACK_FROM_QUAR, callbackInfo);
		}
		break;
	case Command::ADD_MONIT:
		/*magic plz*/
		break;
	case Command::REM_MONIT:
		/*magic plz*/
		break;
	case Command::SCHEDUL:
		/*magic plz*/
		break;
	default:
		break;
	}
}

int main(int argc, char* argv[])
{
	DataIO::RecordBank ass("D:\\Visual\\C++\\ZI\\antyTry\\baseData.bin");
	/*HANDLE hNamedPipe = CreateNamedPipe(
		L"\\\\.\\pipe\\AntimalwarePipe",
		PIPE_ACCESS_DUPLEX,
		PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
		PIPE_UNLIMITED_INSTANCES,
		4096, 4096, 5000, NULL);
	ConnectNamedPipe(hNamedPipe, NULL);
	Messanger p(hNamedPipe, 1024);
	Sleep(5000);
	HANDLE pipe = CreateFile(
		L"\\\\.\\pipe\\AntimalwarePipeBack", GENERIC_READ | GENERIC_WRITE,
		0, NULL, OPEN_EXISTING, 0, NULL);
	pipeIO = new Messanger(pipe, 1024);
	while (true)
	{
		auto res = p.getMSG();
		movment(res.value());
		int i = 0;
	}*/
	schrodingerData sd;
	std::string s = "first";
	sd.addDistruct(s);
	s = "Second";
	sd.addDistruct(s);
	s = "Third";
	sd.addDistruct(s);
	sd.moveToQuaranList(1);

	return 0;
}