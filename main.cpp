#include <iostream>
#include <filesystem>
#include <string>
//#include <bits/stdc++.h>
#include <fstream>
using namespace std;
namespace fs = filesystem;
string path;
int numpaths;
string searpath(){
    string der;
    cout<< "what is the directory you want to search?:\t";
    cin >> der;
    return der;
}

// string* getsettings(){
//     ifstream myfile;
//     myfile.open("settings.txt");
//     string str = "";
//     int i = 0;
//     if (myfile.is_open()) {
//         while (getline(myfile, str)) {
//             if (str.find("^")!= string::npos){
//                 i += 1;
//             }
//         }
//         myfile.close();
//     }
//     myfile.open("settings.txt");
//     if (myfile.is_open()) {
//         cout << i << "\n";
//         string* fSettings = new string[i];
//         i = 0;
//         while (getline(myfile, str)) {
//             fSettings[i] = str;
//             i += 1;
//         }
//         numpaths = i;
//         myfile.close();
//         return fSettings;
//     }
// }


void search() {
    path = searpath();
    if (fs::exists(path)) {
        for (const auto &entry : fs::directory_iterator(path)) {
            if (entry.path().string().find("/.") == string::npos) {

                if (entry.path().has_extension()) {
                    cout << entry.path() << std::endl;
                    //// check if it is video file
                    if (entry.path().extension() == ".mp4" || entry.path().extension() == ".mkv") {
                        fs::rename(entry.path().string(), "/home/mrfluffy/Videos/" + entry.path().filename().string());
                    }
                    else if (entry.path().extension() == ".jpeg" || entry.path().extension() == ".jpg" ||
                               entry.path().extension() == ".png") {
                        fs::rename(entry.path().string(),
                                   "/home/mrfluffy/Pictures/" + entry.path().filename().string());
                    }
                    else if (entry.path().extension() == ".mp3" ){
                        fs::rename(entry.path().string(),
                                   "/home/mrfluffy/Music/" + entry.path().filename().string());
                    }
                    else if (entry.path().extension() == ".pdf") {
                        fs::rename(entry.path().string(),
                                   "/home/mrfluffy/Documents/PDF/" + entry.path().filename().string());
                    }
                    else if (entry.path().extension() == ".docx") {
                        fs::rename(entry.path().string(),
                                   "/home/mrfluffy/Documents/DOCX/" + entry.path().filename().string());
                    }
                    else if (entry.path().extension() == ".jar") {
                        fs::rename(entry.path().string(),
                                   "/home/mrfluffy/Documents/JAR/" + entry.path().filename().string());
                    }
                    else if (entry.path().extension() == ".zip" || entry.path().extension() == ".rar" ||
                               entry.path().extension() == ".zst" || entry.path().extension() == ".gz" || entry.path().extension() == ".xz"){
                        fs::rename(entry.path().string(),
                                   "/home/mrfluffy/Documents/Compressed/" + entry.path().filename().string());
                    }
                    else if (entry.path().extension() == ".iso") {
                        fs::rename(entry.path().string(),
                                   "/home/mrfluffy/Documents/DiscImages/" + entry.path().filename().string());
                    }
                }
            }
        }
    }
    else{
        cout << "Enter valid directory.\n";
        search();
    }
}
void changepath(string nepathS){
    string newpath;
    fstream myfile;
    myfile.open("settings.txt");
    string str = "";
    int i = 0;
    if (myfile.is_open()) {
        while (getline(myfile, str)) {
            if (str.find("^")!= string::npos){
                i += 1;
            }
        }
        myfile.close();
    }
    myfile.open("settings.txt");
    if (myfile.is_open()){
        cout << i << "\n";
        string settings[i];
        i=0;
        while (getline(myfile, str)) {
            settings[i] = str;
            i += 1;
        }
        myfile.close();
        ofstream temp("temp.txt");
        for (int j = 0; j < i; ++j) {
            if (settings[j].find(nepathS)!= string::npos){
                cout << "Enter new path.:\t";
                cin >> newpath;
                settings[j] = nepathS + " " + newpath;
            }
            int t = j;
            temp << settings[t] + "\n";
        }
        temp.close();
        remove("settings.txt");
        rename("temp.txt","settings.txt");
    }
    return;
}
void settings(){
//    system("clear");
    cout << "Change output location for.\n";
    cout << "1. Videos\n";
    cout << "2. Music\n";
    cout << "3. Pictures\n";
    cout << "4. Pdf\n";
    cout << "5. Docx\n";
    cout << "6. Jar\n";
    cout << "7. Disc Images\n";
    int settingmenu;
    cin >> settingmenu;
    switch (settingmenu) {
        case 1:{
            changepath("^Videos");
            break;
        }
        case 2:
            changepath("^Music");
            break;
        case 3:
            changepath("^Pictures");
            break;
        case 4:
            changepath("^Pdf");
            break;
        case 5:
            changepath("^Docx");
            break;
        case 6:
            changepath("^Jar");
            break;
        case 7:
            changepath("^DiscIMage");
            break;
    }
}
int main() {
//    system("clear");
    cout << "1. Sort a directory.\n";
    cout << "2. settings.\n";
    cout << "3. exit.\n";
    int menu;
    cin >> menu;
    switch (menu) {
        case 1:{
            search();
//            string* settingslist = getsettings();
//            for (int i = 0; i < numpaths; ++i) {
//                cout << settingslist[i] << "\n";
//            }
            main();
        }
        case 2:
            settings();
            main();
        case 3:
            exit(3);
    }
}

