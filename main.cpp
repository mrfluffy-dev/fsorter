#include <iostream>
#include <filesystem>
#include <string>
#include <vector>
#include <fstream>
std::string musicTypes[] = {".mp3",".wav"};
std::string pictureType[] = {".jpg","jpeg","png"};
namespace fs = std::filesystem;
std::string home = getenv("HOME");
std::string settingsPath = home+"/.config/fsorter/settings.conf";
std::string sortingPath = fs::current_path();

//createn of the typeAndPath object
class typeAndPaths{
    public:
        std::string type;
        std::string path;
        std::vector<std::string> extensions;
};

//this is just a basic function that will create a basic settings.conf file if it does not exist (it is called by readSettings in the case settings.conf does not exist)
void writeSettins()
{
    std::ofstream settings(settingsPath);
    settings << "Picture=\n"+ home +"/Pictures/\n.jpg,.jpeg,.png," << std::endl;
    settings << "Music=\n"+home+"/Music/\n.mp3,.wav," << std::endl;
    settings << "Video=\n"+home+"/Videos/\n.mp4," << std::endl;
    settings << "Arcive=\n"+home+"/Documents/Compressed/\n.zip,.rar,.7z," << std::endl;
    settings.close();
}

//Reads all the lines in settings.conf and saves them in a vector line by line.
std::vector<std::string> readSettings()
{
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
        while(getline(settingsFile, setting))
        {
            listOfPaths.push_back(setting);
        }
    }
    settingsFile.close();
    return listOfPaths;
}

//declarePaths will take a vector of all the text written in settings.conf and devide them in to there respected atrebutes in Object typeAndPath
std::vector<typeAndPaths> declarePaths(std::vector<std::string> listOfPaths)
{
    typeAndPaths Paths;
    std::vector<typeAndPaths> paths;
    for (int i = 0; i < listOfPaths.size(); i+=3)
    {
        listOfPaths[i].pop_back();
        Paths.type = listOfPaths[i];
        Paths.path = listOfPaths[i+1];
        std::string stringextensions = listOfPaths[i+2];
        std::vector<std::string> extensions;
        std::string tempWord;
        int counter = 0;
        i = 0;
        while (i < stringextensions.size()) {
            char temp = stringextensions[i];
            if(temp != ',')
            {

                tempWord.push_back(temp);
            }
            else
            {
                extensions.push_back(tempWord);
                tempWord = "";
                counter++;
            }
            i++;
        }
        Paths.extensions = extensions;
        paths.push_back(Paths);

    }
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
    std::vector<std::string> listOfPaths = readSettings();
    std::vector<typeAndPaths> Paths = declarePaths(listOfPaths);
    checkSettingsPaths(Paths);
    sortPath(sortingPath, Paths);
    return 0;
}


