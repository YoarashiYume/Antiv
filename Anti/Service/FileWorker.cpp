#include "FileWorker.h"

bool FileWorker::moveToQuar(std::filesystem::path from)
{
    std::lock_guard<std::mutex> lg(fileWork);
    if (!std::filesystem::is_block_file(from))
        if (std::filesystem::copy_file(from, qFolder.replace_filename( from.filename())))
        {
            if (std::filesystem::remove(from))
            {
                qFolder.remove_filename();
                /*magic plz*/
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
        if (std::filesystem::copy_file(qFolder,from))
        {
            std::filesystem::remove(qFolder);
            qFolder.remove_filename();
            /*magic plz*/
            return true;
        }
    return false;
}
