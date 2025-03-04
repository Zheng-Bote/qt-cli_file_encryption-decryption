#pragma once

#include <filesystem>

namespace rz_snippets {

struct fileStruct
{
    std::string srcFile;
    std::string targetFile;
    bool doEncrypt{false};
    bool doDecrypt{false};
    std::string encExtension{".aes"};
    std::string pwd{""};
};

std::tuple<bool, std::string> isFile(const std::filesystem::path &pathToFile)
{
    if (std::filesystem::is_regular_file(pathToFile)) {
        return std::make_tuple(true, "is a regular file");
    }
    return std::make_tuple(false, "not a regular file");
}

std::tuple<bool, std::string> existFile(const std::filesystem::path &pathToFile)
{
    if (std::filesystem::exists(pathToFile)) {
        return std::make_tuple(true, "file exist");
    }
    return std::make_tuple(false, "file doesn't exist");
}

std::string removeFileExtension(const std::string &pathToFile)
{
    return pathToFile.substr(0, pathToFile.size() - 4);
}

}; // namespace rz_snippets
