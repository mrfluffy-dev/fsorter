#include <iostream>
#include <filesystem>
#include <string>
#include <vector>
//#include <bits/stdc++.h>
#include <fstream>

namespace fs = std::filesystem;
std::string settingsPath = "settings.conf";
std::string musicPath()
{
    std::string musicFolder = "";
    return musicFolder;
}

std::string photoPath()
{
    std::string photoFolder = "";
    return photoFolder;
}

std::string videoPath()
{
    std::string videoFolder = "";
    return videoFolder;
}

std::string arcivePath()
{
    std::string arciveFolder = "";
    return arciveFolder;
}
void writeSettins()
{
    std::ofstream settings(settingsPath);
    settings << "Pictures=\n$HOME/Pictures" << std::endl;
    settings << "Music=\n$HOME/Music" << std::endl;
    settings.close();

    
}
std::vector<std::string> readSettings()
{

    std::ifstream settings(settingsPath);
    std::vector<std::string> listOfPaths;
    std::string setting;
    // creates a default settins file
    if(!settings)
    {
        writeSettins();
    }
    if(settings)
    {
        while(getline(settings, setting))
        {
            listOfPaths.push_back(setting);
        }
    }
    return listOfPaths;
}

int main()
{
    std::vector<std::string> listOfPaths = readSettings();
    for (int i; i < listOfPaths.size(); i++) {
        std::string stringItem ="echo " + listOfPaths[1];
        const char* item = stringItem.c_str();
        system(item);
    }
    return 0;
}
