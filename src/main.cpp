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
using std::string;
using std::stringstream;
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
    auto user_profile = string(getenv("USERPROFILE"));
    HANDLE hin = GetStdHandle(STD_INPUT_HANDLE);
    auto winapi = WindowsApiService();
    auto vsh = make_unique<Vsh>(move(user_profile), move(hin), move(winapi)); 

    vsh->start();

    return 0;
}