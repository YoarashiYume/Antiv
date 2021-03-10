#include "Messanger.hpp"
int main(int argc, char* argv[])
{
	HANDLE h_pipe = CreateFile(
		L"\\\\.\\pipe\\NAME", GENERIC_READ | GENERIC_WRITE,
		0, NULL, OPEN_EXISTING, 0, NULL);
	Messanger p(h_pipe,1024);
	p.sendStartMSG("fsdfs");
	system("pause");
	
}
