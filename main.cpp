#include <iostream>
#include <filesystem>
#include <string>
#include <vector>
//#include <bits/stdc++.h>
#include <fstream>

namespace fs = std::filesystem;
std::string settingsPath = "settings.conf";
class paths{
    public:
        std::string Picturs;
        std::string Music;
        std::string Vidios;
        std::string Arcives;
};

void writeSettins()
{
    std::ofstream settings(settingsPath);
    settings << "Picture=\n$HOME/Pictures" << std::endl;
    settings << "Music=\n$HOME/Music" << std::endl;
    settings << "Video=\n$HOME/Videos" << std::endl;
    settings << "Arcive=\n$HOME/Documents/Compressed" << std::endl;
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
paths declarePaths(std::vector<std::string> listOfPaths)
{
    paths Paths;
    for (int i = 0; i < listOfPaths.size(); i+=2)
    {
        listOfPaths[i].pop_back();
        std::string type = listOfPaths[i];
        std::string path = listOfPaths[i+1];
        if(type == "Picture")
        {
            Paths.Picturs = path;
        }
        else if (type == "Music")
        {
            Paths.Music = path;
        }
        else if (type == "Video")
        {
            Paths.Vidios = path;
        }
        else if (type == "Arcive")
        {
            Paths.Arcives = path;
        }
    }
    return Paths;
}
int main()
{
    std::vector<std::string> listOfPaths = readSettings();
    paths Paths = declarePaths(listOfPaths);
    std::cout << Paths.Picturs << std::endl;
    return 0;
}
