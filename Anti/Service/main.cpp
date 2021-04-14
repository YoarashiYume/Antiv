#include <iostream>
#include "_service/AntimalwareService.h"
#include "_service/ServiceInitializer.h"
#include "_service/ServiceManager.h"
using namespace Antimalware::ServiceApp;
using namespace ServiceLib::ServiceManagement;

int wmain(int argc, wchar_t* argv[])
{
    std::wcout.imbue(std::locale(".866"));
    std::wcerr.imbue(std::locale(".866"));
    std::wcin.imbue(std::locale(".866"));

    if (argc - 1 == 0)
    {
        AntimalwareServiceFactory serviceFactory;
        InitService(serviceFactory);
    }
    else
    {
        ServiceManager sm{ u"NadyezhniyAntimalwareService", reinterpret_cast<char16_t*>(argv[0]) };
        if (wcscmp(argv[argc - 1], L"--install") == 0) {
            sm.InstallService();
        }
        else if (wcscmp(argv[argc - 1], L"--uninstall") == 0) {
            sm.UninstallService();
        }
        else if (wcscmp(argv[argc - 1], L"--start") == 0) {
            sm.RunService();
        }
    }
    return 0;
}