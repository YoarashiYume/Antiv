#pragma once
#include <vector>
#include <string>
typedef uint32_t VECTOR_TYPE;
/*
List of commands
Start scanning
End of scan
Moving to quarantine
Deleting a file
*/
enum class Command : uint16_t
{
	START_SCAN,
	STOP_SCAN,
	MOV_TO_QUAR,
	DELETE_FILE
};
struct Package
{
	enum class PTYPE : uint16_t //Package type - empty, string or value
	{
		NUL,
		STR,
		VEC
	};
	std::vector<VECTOR_TYPE> valueArr;// value array
	std::vector<std::string> strArr;//string array
};

struct Header
{
	uint32_t size; //message size
	uint32_t countOfPackage;//count of package(mean while sending)
	Command command_type;//comand in this package
	Header() :command_type(Command::STOP_SCAN),
		size(0),
		countOfPackage(0) {};
	Header(Command _cmd, uint32_t _size) :
		command_type(_cmd),
		size(_size),
		countOfPackage(0) {};
};