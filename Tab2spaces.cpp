#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>

namespace fs = std::filesystem;

// 替换tab为指定数量的空格
std::string replaceTabWithSpaces(const std::string& line, int spaceCount)
{
    std::string result;
    for (char c : line)
    {
        if (c == '\t')
        {
            // 添加指定数量的空格
            for (int i = 0; i < spaceCount; ++i)
            {
                result += ' ';
            }
        }
        else
        {
            result += c;
        }
    }
    return result;
}

// 处理单个文件
void processFile(const std::string& filePath, int spaceCount)
{
    std::ifstream inFile(filePath);
    if (!inFile.is_open())
    {
        std::cerr << "Failed to open file: " << filePath << std::endl;
        return;
    }

    std::string line;
    std::string fileContent;
    while (std::getline(inFile, line))
    {
        // 替换tab为指定数量的空格
        std::string replacedLine = replaceTabWithSpaces(line, spaceCount);

        // 将替换后的内容添加到文件内容字符串中
        fileContent += replacedLine + '\n';
    }

    // 关闭文件流
    inFile.close();

    // 将替换后的内容覆写到原文件
    std::ofstream outFile(filePath);
    if (!outFile.is_open())
    {
        std::cerr << "Failed to open file for writing: " << filePath << std::endl;
        return;
    }

    outFile << fileContent;
    outFile.close();

    std::cout << "Processed: " << filePath << std::endl;
}

int main()
{
    std::string folderPath;
    int spaceCount = 4;  // 默认的空格数量

    std::cout << "Enter folder path: ";
    std::getline(std::cin, folderPath);

    std::cout << "Enter number of spaces for replacement (default is 4): ";
    std::string spaceCountStr;
    std::getline(std::cin, spaceCountStr);

    // 如果用户输入了空格数量，则使用用户输入的值
    if (!spaceCountStr.empty())
    {
        try
        {
            spaceCount = std::stoi(spaceCountStr);
        }
        catch (const std::exception&)
        {
            std::cerr << "Invalid input. Using default value of 4." << std::endl;
        }
    }

    // 处理文件夹下所有文本文件
    for (const auto& entry : fs::directory_iterator(folderPath))
    {
        const std::string& path = entry.path().string();
        if (fs::is_regular_file(entry))
        {
            // 处理文本文件
            std::string ext = fs::path(path).extension().string();
            if (ext == ".txt" || ext == ".cpp" || ext == ".h")
            {
                processFile(path, spaceCount);
            }
        }
    }

    std::cout << "Tab characters replaced with spaces." << std::endl;

    return 0;
}
