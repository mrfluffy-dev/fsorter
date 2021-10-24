#include <iostream>
#include <filesystem>
#include <string>
#include <vector>
#include <fstream>
// making use of https://marzer.github.io/tomlplusplus/ to handle toml files
#include "libs/toml.hpp"
using namespace std::string_view_literals;

std::string musicTypes[] = {".mp3",".wav"};
std::string pictureType[] = {".jpg","jpeg","png"};
namespace fs = std::filesystem;
std::string home = getenv("HOME");
std::string settingsPath = home+"/.config/fsorter/settings.toml";
std::string sortingPath = fs::current_path();


//createn of the typeAndPath object
class typeAndPaths{
    public:
        std::string type;
        std::string path;
        std::vector<std::string> extensions;
};

//this is just a basic function that will create a basic settings.toml file if it does not exist (it is called by readSettings in the case settings.conf does not exist)
void writeSettins()
{
    std::ofstream settings(settingsPath);
    settings << "[Picture]" << std::endl;
    settings << "path = " << "\"" << home << "/Pictures/\"" << std::endl;
    settings << "extensions = [\".jpg\",\".jpeg\",\".png\"]" << std::endl;
    settings << "[Music]" << std::endl;
    settings << "path = " << "\"" << home << "/Music/\"" << std::endl;
    settings << "extensions = [\".mp3\",\".wav\"]" << std::endl;
    settings << "[Video]" << std::endl;
    settings << "path = " << "\"" << home << "/Videos/\"" << std::endl;
    settings << "extensions = [\".mp4\"]" << std::endl;
    settings << "[Arcive]" << std::endl;
    settings << "path = " << "\"" << home << "/Documents/Compressed/\"" << std::endl;
    settings << "extensions = [\".zip\",\".rar\",\".7z\"]";
    settings.close();
}

//Reads all the lines in settings.toml and saves them in a vector line by line.
std::vector<typeAndPaths> readSettings()
{
    std::vector<typeAndPaths> paths;
    typeAndPaths Paths;
    if(!fs::exists(settingsPath))
    {
        fs::create_directory(home + "/.config/fsorter/");
    }
    std::ifstream settingsFile(settingsPath);
    std::vector<std::string> listOfPaths;
    std::string setting;
    // creates a default settins file
    if(!settingsFile)
    {
        writeSettins();
    }
    if(settingsFile)
    {
        settingsFile.close();
        toml::table tbl;
        try
        {
            tbl = toml::parse_file(settingsPath);
        }
        catch (const toml::parse_error& err)
        {
            std::cerr
            << "Error parsing file '" << *err.source().path
            << "':\n" << err.description()
            << "\n  (" << err.source().begin << ")\n";
            exit(0);
        }
        for(auto it = tbl.begin(); it != tbl.end(); ++it)
        {
            Paths.type = it->first;
            Paths.path = tbl[it->first]["path"].ref<std::string>();
            std::vector<std::string> extensions;
            for(int i = 0 ; i < tbl[it->first]["extensions"].as_array()->size(); i++)
            {
                std::string ext = tbl[it->first]["extensions"][i].ref<std::string>();
                extensions.push_back(ext);
            }
            Paths.extensions = extensions;
            paths.push_back(Paths);
        }
    }
    settingsFile.close();
    return paths;
}



//this will check if the Folder that is mentiond in the object Paths.path (typeAndPath) exists and if not will prompt the user if they want to create the directory or not
//if the user says yes the directory will be created.
void checkSettingsPaths(std::vector<typeAndPaths> Paths)
{
    for (int i = 0; i < Paths.size(); i++)
    {
        if(!fs::exists(Paths[i].path))
        {
            bool valid = false;
            while (!valid) {
                char answer;
                std::cout << "Would you like to create (y/n) : " << Paths[i].path << "? \t";
                std::cin >> answer;
                std::cout << '\n';
                if(tolower(answer) == 'y')
                {
                    fs::create_directory(Paths[i].path);
                    std::cout << "Directory " << Paths[i].path << " was created.\n";
                    valid = true;
                }
                else if (tolower(answer) == 'n')
                {
                    std::cout << "Directory" << Paths[i].path <<" was not created!\n";
                    valid = true;
                }
                else
                {
                    std::cout << "Please provide a valid answer!" << std::endl;
                }
            }
        }
    }
}

//iterates thrue all the files in the given path looks at there respected extention and then moves them to the location found in the Paths.path (typeAndPath) object
//that is related to the extention that is being sorted..
void sortPath(std::string path, std::vector<typeAndPaths> Paths)
{
    for(auto const& file: fs::directory_iterator{path})
    {
        if(file.path().has_extension())
        {
            for (int i = 0; i < Paths.size(); i++) {
                for (int x = 0; x < Paths[i].extensions.size(); x++) {
                    if(Paths[i].extensions[x] == file.path().extension())
                    {
                        std::cout << file.path().string() << std::endl;
                        fs::rename(file.path().string(), Paths[i].path + file.path().filename().string());
                    }
                }
            }
        }

    }
}

int main()
{
    std::vector<typeAndPaths> TypesAndPaths = readSettings();
    checkSettingsPaths(TypesAndPaths);
    sortPath(sortingPath, TypesAndPaths);
    return 0;
}
