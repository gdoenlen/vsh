#include <stdio.h>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <memory>
#include <utility>

#include <vsh.hpp>
#include <winapi.hpp>

using std::getenv;
using std::vector;
using std::wstring;
using std::stringstream;
using std::string;
using std::move;
using std::cout;
using std::make_unique;
using std::make_shared;
using std::getline;
using winapi::WindowsApiService;
using namespace vsh;

/**
 * Vsh main. Sets up dependencies for Vsh
 * 
 * @see Vsh::start for the main loop
 */
#pragma GCC diagnostic ignored "-Wunused-parameter"
int main(int argc, char** argv) {
    if (argc > 1) {
        cout << "Vip's Shell v0.1\n";
        cout << "usage: vsh\n";
        return 0;
    } 

    auto path = string(getenv("PATH"));
    auto vec = make_shared<vector<string>>(); 
    auto ss = stringstream(path);
    string to;
    while (getline(ss, to, ';')) {
        vec->push_back(move(to));
    }
    HANDLE hin = GetStdHandle(STD_INPUT_HANDLE);
    auto winapi = WindowsApiService();
    auto buffer = make_unique<wchar_t[]>(256);

    // for now we need to use windows.h to get the cwd
    // mingw doesn't have proper support for std::filesystem
    winapi.get_cwd(buffer.get(), 256);
    auto cwd = wstring(buffer.get());
    auto vsh = make_unique<Vsh>(move(cwd), move(hin), move(winapi)); 

    vsh->start();

    return 0;
}