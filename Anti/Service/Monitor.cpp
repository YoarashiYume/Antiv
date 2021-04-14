#include "Monitor.h"

bool Monitor::contains(std::string path)
{
    return fileMonitoring.find(path) != fileMonitoring.end();
}

Monitor::Monitor(std::shared_ptr<Engen::ScanEngen> _scEn, std::shared_ptr<schrodingerData> _data)
{
    scEn = _scEn;
    data = _data;
    findMutex.store(false);
    tryToRestore();
}

std::vector<std::string> Monitor::getList()
{
    std::lock_guard<std::mutex> lg(mutex);
    std::vector<std::string> vec;
    for (auto& el : monitorFile)
        vec.emplace_back(el.string());
    return std::move(vec);
}

bool Monitor::addFile(std::filesystem::path _path)
{
    std::lock_guard<std::mutex> lg(mutex);
    bool isFile = true;
    for (auto& el : monitorFile)
        if (el == _path) isFile = false;
    if (isFile)
    {
        monitorFile.emplace_back(_path);
        if (!contains(_path.string()))
            fileMonitoring[_path.string()] = std::filesystem::last_write_time(_path);
    }
    return isFile;
}

bool Monitor::removeFile(std::size_t index)
{
    if (monitorFile.size() < index)
        return false;
    std::lock_guard<std::mutex> lg(mutex);
    monitorFile.erase(monitorFile.begin() + index);
    fileMonitoring.clear();
    for (auto &el : monitorFile)
        fileMonitoring[el.string()] = std::filesystem::last_write_time(el);
    return true;
}

void Monitor::start()
{
    while (true)
    {
        std::this_thread::sleep_for(std::chrono::seconds(5));
        mutex.lock();
        auto it = fileMonitoring.begin();
        while (it != fileMonitoring.end())
        {
            if (!std::filesystem::exists(it->first)) 
                it = fileMonitoring.erase(it);
            else
                ++it;
        }
        for (auto& el : monitorFile)
        for (auto& file : std::filesystem::recursive_directory_iterator(el)) 
        {
            auto current_file_last_write_time = std::filesystem::last_write_time(file);

            // File creation
            if (!contains(file.path().string())) 
            {
                fileMonitoring[file.path().string()] = current_file_last_write_time;

                std::vector<std::string> strV = { file.path().string() };
                std::vector<ScanObject> scO = Engen::scanGen(strV);
                std::string res;
                bool isFind = false;
                for (auto& el : scO)
                {
                    res = scEn->scan(el);
                    if (!res.empty())
                    {
                        data->addDistruct(el.filePath);
                        isFind = true;
                    }
                }
                if (isFind)
                    findMutex.store(true);
                
            }
            else {
                if (fileMonitoring[file.path().string()] != current_file_last_write_time) 
                {
                    fileMonitoring[file.path().string()] = current_file_last_write_time;
                    std::vector<std::string> strV = { file.path().string() };
                    std::vector<ScanObject> scO = Engen::scanGen(strV);
                    std::string res;
                    bool isFind = false;
                    for (auto& el : scO)
                    {
                        res = scEn->scan(el);
                        if (!res.empty())
                        {
                            data->addDistruct(el.filePath);
                            isFind = true;
                        }
                    }
                    if (isFind)
                        findMutex.store(true);
                    
               // File modification
                }
            }
        }
        mutex.unlock();
    }
}

bool Monitor::isFoundSmt()
{
    std::lock_guard<std::mutex> lg(mutex);
    bool res = findMutex;
    findMutex.store(false);
    return res;
}

void Monitor::saveData()
{
    std::lock_guard<std::mutex> lg(mutex);
    ModulesSrializer::serializePathArr(monitorFile, std::filesystem::current_path().string() + "\\Monit.bin");
}
void Monitor::tryToRestore()
{
    this->monitorFile =ModulesSrializer::derializePathArr(std::filesystem::current_path().string() + "\\Monit.bin");
    for (auto& el : monitorFile)
        fileMonitoring[el.string()]= std::filesystem::last_write_time(el);
}