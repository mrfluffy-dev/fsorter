#include <iostream>
#include <filesystem>
#include <string>
#include <vector>
//#include <bits/stdc++.h>
#include <fstream>
std::string musicTypes[] = {".mp3",".wav"};
std::string pictureType[] = {".jpg","jpeg","png"};
namespace fs = std::filesystem;
std::string settingsPath = "settings.conf";
std::string home = getenv("HOME");
class typeAndPaths{
    public:
        std::string type;
        std::string path;
        std::vector<std::string> extentions;
};

void writeSettins()
{
    std::ofstream settings(settingsPath);
    settings << "Picture=\n"+ home +"/Pictures\n.jpg,.jpeg,.png" << std::endl;
    settings << "Music=\n"+home+"/Music\n.mp3,.wav" << std::endl;
    settings << "Video=\n"+home+"/Videos\n.mp4" << std::endl;
    settings << "Arcive=\n"+home+"/Documents/Compressed\n.zip,.rar,.7z" << std::endl;
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
    settings.close();
    return listOfPaths;
}
std::vector<typeAndPaths> declarePaths(std::vector<std::string> listOfPaths)
{
    typeAndPaths Paths;
    std::vector<typeAndPaths> paths;
    for (int i = 0; i < listOfPaths.size(); i+=3)
    {
        listOfPaths[i].pop_back();
        Paths.type = listOfPaths[i];
        Paths.path = listOfPaths[i+1];
        std::string stringExtentions = listOfPaths[i+2];
        std::vector<std::string> extentions;
        char temp;
        std::string tempWord;
        int counter = 0;
        for (int i = 0; i < stringExtentions.size(); i++) {
            temp = stringExtentions[i];
            if(temp != ',')
            {

                tempWord.push_back(temp);
            }
            else
            {
                extentions.push_back(tempWord);
                tempWord = "";
                counter++;
            }
        }
        Paths.extentions = extentions;
        paths.push_back(Paths);
    }
    return paths;
}
void checkSettingsPaths(std::vector<typeAndPaths> Paths)
{
    for (int i = 0; i < Paths.size(); i++)
    {
        if(fs::exists(Paths[i].path))
        {
            std::cout << "Yes\n";
        }
        else
        {
            bool valid = false;
            while (!valid) {
                char awnser;
                std::cout << "would you like to create y=yes, n=no : " << Paths[i].path << "\t";
                std::cin >> awnser;
                std::cout << '\n';
                if(tolower(awnser) == 'y')
                {
                    fs::create_directory(Paths[i].path);
                    valid = true;
                }
                else if (tolower(awnser) == 'n')
                {
                    std::cout << "Directory was not created\n";
                    valid = true;
                }
                else
                {
                    std::cout << "pleas provide valid awnser" << std::endl;
                }
            }
        }
    }
}

int main()
{
    std::vector<std::string> listOfPaths = readSettings();
    std::vector<typeAndPaths> Paths = declarePaths(listOfPaths);
    checkSettingsPaths(Paths);
    return 0;
}
