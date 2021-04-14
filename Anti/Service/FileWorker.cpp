#include "FileWorker.h"

void FileWorker::breakPE(std::filesystem::path filePath)
{
    std::ifstream fs(qFolder, std::ios::binary);
    uint64_t header = 0;
    fs.read((char*)&header, sizeof(uint64_t));
    fs.close();
    header = ~header;
    std::fstream fi(qFolder, std::ios::in | std::ios::out | std::ios::binary);
    fi.seekp(0);
    fi.write((char*)&header, sizeof(uint64_t));
    fi.close();   
}


FileWorker::FileWorker() : FileWorker(std::filesystem::current_path().parent_path().concat("\\TempQuar\\"))
{}

FileWorker::FileWorker(std::filesystem::path filePath)
{
    qFolder = filePath;
    if (!std::filesystem::exists(filePath))
        std::filesystem::create_directories(filePath);
}

bool FileWorker::moveToQuar(std::filesystem::path from)
{
    std::lock_guard<std::mutex> lg(fileWork);
    if (!std::filesystem::is_block_file(from))
        if (std::filesystem::copy_file(from, qFolder.replace_filename( from.filename())))
        {
            if (std::filesystem::remove(from))
            {
                breakPE(qFolder);
                qFolder.remove_filename();
                return true;
            }
            else
            {
                std::filesystem::remove(qFolder);
                qFolder.remove_filename();
            }
        }
   
    return false;
}

bool FileWorker::removeFile(std::filesystem::path from)
{
    std::lock_guard<std::mutex> lg(fileWork);
    if (!std::filesystem::is_block_file(from))
        if (std::filesystem::remove(from))
            return true;
    return false;
}

bool FileWorker::recoverFile(std::filesystem::path from)
{
    std::lock_guard<std::mutex> lg(fileWork);
    if (!std::filesystem::is_block_file(qFolder.replace_filename(from.filename())))
    {
        breakPE(qFolder);
        if (std::filesystem::copy_file(qFolder, from))
        {
            std::filesystem::remove(qFolder);
            qFolder.remove_filename();
            return true;
        }
    }
    return false;
}

std::filesystem::path FileWorker::extractZip(std::filesystem::path filePath)
{
    std::lock_guard<std::mutex> lg(fileWork);
    int err;
    struct zip* hZip = zip_open(filePath.string().c_str(), 0, &err);
    std::filesystem::path _path = eFolder.string() + filePath.replace_extension("").filename().string();
    if (!std::filesystem::exists(_path))
        std::filesystem::create_directory(_path);
    if (hZip)
    {
        size_t totalIndex = zip_get_num_entries(hZip, 0);
        for (size_t i = 0; i < totalIndex; i++)
        {
            struct zip_stat st;
            zip_stat_init(&st);
            zip_stat_index(hZip, i, 0, &st);

            struct zip_file* zf = zip_fopen_index(hZip, i, 0);
            if (!zf)
            {
                zip_close(hZip);
                return {};
            }
            std::vector<char> buffer;
            std::filesystem::path fileP = _path.string() + '\\' + st.name;
            if (st.size==0)
            {
                std::filesystem::create_directory(fileP);
                continue;
            }
            std::ofstream fs(fileP.string(),std::ios::binary| std::ios::trunc | std::ios::out );
            uint64_t offset{ 0 };
            uint64_t readSize{ 1024 * 1024 };
            while (true)
            {
                if (offset >= st.size)
                    break;
                if (offset + readSize >= st.size)
                    readSize = st.size - offset;
                buffer.resize(readSize);
                zip_fread(zf, buffer.data(), readSize);
                fs.write(buffer.data(), buffer.size());
                offset += readSize;
                readSize= 1024 * 1024 ;
            }
            zip_fclose(zf);
            fs.close();
        }
        zip_close(hZip);
    }
    return _path;
}

bool FileWorker::clearZip(std::filesystem::path filePath)
{
    std::lock_guard<std::mutex> lg(fileWork);
    std::filesystem::path _path = eFolder.string() + filePath.replace_extension("").filename().string();
    if (std::filesystem::exists(_path))
        std::filesystem::remove_all(_path);
    else
        return false;
}
