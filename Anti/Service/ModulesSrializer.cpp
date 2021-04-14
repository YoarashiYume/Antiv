#include "ModulesSrializer.h"

void ModulesSrializer::serializePathArr(std::vector<std::filesystem::path>& _vec, std::filesystem::path _where)
{
    std::vector<std::string> vec;
    for (auto& el : _vec)
        vec.emplace_back(el.string());
    serializeStrArr(vec,_where);
}

void ModulesSrializer::serializeStrArr(std::vector<std::string>& vec, std::filesystem::path _where)
{
    std::ofstream stream(_where,std::ios::binary);
    std::uint64_t size = vec.size();
    stream.write((char*)&size, sizeof(size));
    for (auto& el : vec)
    {
        size = el.size();
        stream.write((char*)&size, sizeof(size));
        stream.write(el.data(), el.size());
    }
    stream.close();
}

void ModulesSrializer::serializeTimeInfo(std::vector<timeInfo>& _vec, std::filesystem::path _where)
{
    std::ofstream stream(_where, std::ios::binary);
    std::uint64_t size = _vec.size();
    stream.write((char*)&size, sizeof(size));
    for (auto& el : _vec)
    {
        stream.write((char*)&el.second.hour, sizeof(timeStruct::hour));
        stream.write((char*)&el.second.min, sizeof(timeStruct::min));
        size = el.first.size();
        stream.write((char*)&size, sizeof(size));
        stream.write(el.first.data(), size);
    }
    stream.close();
}

std::vector<std::filesystem::path> ModulesSrializer::derializePathArr(std::filesystem::path _from)
{
    auto vec_ = derializeStrArr(_from);
    std::vector<std::filesystem::path> vec;
    for (auto& el : vec_)
        vec.emplace_back(el);
    return std::move(vec);
}

std::vector<std::string> ModulesSrializer::derializeStrArr(std::filesystem::path _from)
{
    if (!std::filesystem::exists(_from))
        return{};
    std::vector<std::string> vec;
    std::ifstream stream(_from, std::ios::binary);
    uint64_t size,sizeArr;
    stream.read((char*)&sizeArr, sizeof(sizeArr));
    if (!sizeArr)
        return{};
    vec.resize(sizeArr);
    for (std::size_t i = 0;!stream.eof() && i < sizeArr;++i)
    {
        stream.read((char*)&size, sizeof(size));
        vec.at(i).resize(size);
        stream.read(vec.at(i).data(), size);
    }
    return std::move(vec);
}

std::vector<timeInfo> ModulesSrializer::derializeTimeInfoArr(std::filesystem::path _from)
{
    if (!std::filesystem::exists(_from))
        return{};
    std::vector<timeInfo> vec;
    std::ifstream stream(_from, std::ios::binary);
    uint64_t size, sizeArr;
    stream.read((char*)&sizeArr, sizeof(sizeArr));
    if (!sizeArr)
        return{};
    vec.resize(sizeArr);
    for (std::size_t i = 0; !stream.eof() && i < sizeArr; ++i)
    {
        stream.read((char*)&vec.at(i).second.hour, sizeof(timeStruct::hour));
        stream.read((char*)&vec.at(i).second.min, sizeof(timeStruct::min));
        stream.read((char*)&size, sizeof(size));
        vec.at(i).first.resize(size);
        stream.read(vec.at(i).first.data(), size);
    }
    return std::move(vec);
}
