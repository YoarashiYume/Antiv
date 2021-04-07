#pragma once
#include <filesystem>
#include <mutex>
class FileWorker
{
	std::mutex fileWork;
	std::filesystem::path qFolder = "D:\\Visual\\C++\\ZI\\antyTry\\TempQuar\\";
public:
	bool moveToQuar(std::filesystem::path from);
	bool removeFile(std::filesystem::path from);
	bool recoverFile(std::filesystem::path from);
};

