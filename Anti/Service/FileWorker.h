#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <filesystem>
#include <fstream>
#include <zip.h>
#include <mutex>
class FileWorker
{
	std::mutex fileWork;
	std::filesystem::path qFolder = "D:\\Visual\\C++\\ZI\\antyTry\\TempQuar\\";
	int mzHeaderConst = 0x5a4d;
	int zipHeaderConst = 0x04034b50;
	const std::string rep =  "#######";
	void breakPE(std::filesystem::path filePath);
	std::filesystem::path eFolder = "D:\\Visual\\C++\\ZI\\antyTry\\TempExtract\\";
public:
	FileWorker();
	FileWorker(std::filesystem::path filePath);
	bool moveToQuar(std::filesystem::path filePath);
	bool removeFile(std::filesystem::path filePath);
	bool recoverFile(std::filesystem::path filePath);
	std::filesystem::path extractZip(std::filesystem::path filePath);
	bool clearZip(std::filesystem::path filePath);
};

