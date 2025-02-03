#include <deque>
#include <string>
#include <fstream>
#include <iostream>

namespace FileUtils
{
    inline std::deque<std::string> loadFile(std::string_view fileName)
    {
        std::deque<std::string> fileContents{};

        std::ifstream file{ fileName };

        if (!file)
        {
            return { "" };
        }

        std::string line{};
        while (std::getline(file, line))
            fileContents.push_back(line);

        return fileContents;
    }
}
