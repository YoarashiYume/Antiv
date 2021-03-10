
#include "../client/Messanger.hpp"
int main(int argc, char* argv[])
{
	/*Poco::Util::WinService winServ("Anti_Proc");
	
	winServ.setDescription("My Anti Process");
	//winServ.unregisterService();
	if (!winServ.isRegistered())
		winServ.registerService(*argv,"antiproc");
	//if (!winServ.isRunning())
	//	return 1;
	try
	{
		winServ.start();
	}
	catch (const Poco::SystemException& e)
	{
		std::cout << e.code();
		system("pause");
		return 0;
	}
	
	winServ.setStartup(Poco::Util::WinService::Startup::SVC_MANUAL_START);*/
	HANDLE hNamedPipe = CreateNamedPipe(
		L"\\\\.\\pipe\\NAME",
		PIPE_ACCESS_DUPLEX,
		PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
		PIPE_UNLIMITED_INSTANCES,
		4096, 4096, 5000, NULL);
	ConnectNamedPipe(hNamedPipe, NULL);
	Messanger p(hNamedPipe,1024);
	auto res = p.getMSG();
	system("pause");
	/*winServ.stop();
	winServ.unregisterService();*/
	
}