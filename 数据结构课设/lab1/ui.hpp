#include <iostream>
#include <vector>
#include <string>
#include <fstream>
//
using namespace std;

#if defined(_MSC_VER)
    #include <windows.h>
    #define SLEEP(seconds) Sleep(static_cast<DWORD>(seconds * 1000))
#elif defined(__GNUC__) || defined(__clang__)
    #include <unistd.h>
    #define SLEEP(seconds) sleep(seconds)
#endif
class UI{
public:
    UI(const string &filename):filename(filename){
        system("chcp 65001");
        init();
    }
    void printPage(int idx){
        system("cls");
        cout<<border<<'\n';
        for (const string& str:pages[idx])
            cout<<str<<'\n';
        cout<<border<<'\n';
    }
private:
    string border = "*************************************************";
    vector<vector<string>> pages;
    string filename;
    void init(){
        ifstream ifs(filename);
        if(!ifs.is_open()){
            throw "fail to open\n";
            return;
        }
        string line;
        vector<string>page;
        while (getline(ifs,line)){
            if(line.size()>4 && line.substr(0,4)=="page"){
                pages.push_back(page);
                page.clear();
                continue;
            }
            page.push_back(line);
        }
    }
};

