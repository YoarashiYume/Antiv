#define WRITE_IN_DATA
#include "Record.hpp"
#include "RecordData.hpp"
int main(int argc, char* argv[])
{
	DataWriter dr("SimpleFile.txt");
	Record r;
	r.name = "name;";
	r.dangerLvl = 10;
	r.signature = 456;
	r.signSize = 30;
	r.hash = 32;
	r.offsetStart = 12;
	r.offsetEnd = 20;
	auto res = Serializer::serialize(r);
	auto ss = Serializer::deserializeRecord(res);
	system("pause");
}