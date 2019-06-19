#include <stdio.h>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <memory>
#include <utility>

#include <vsh.hpp>
#include <winapi.hpp>

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
        std::cout << "Vip's Shell v0.1\n";
        std::cout << "usage: vsh\n";
        return 0;
    } 

    HANDLE hin = GetStdHandle(STD_INPUT_HANDLE);
    auto winapi = WindowsApiService();
    auto buffer = std::make_unique<wchar_t[]>(256);

    // for now we need to use windows.h to get the cwd
    // mingw doesn't have proper support for std::filesystem
    winapi.get_cwd(buffer.get(), 256);
    auto cwd = std::wstring(buffer.get());
    auto vsh = std::make_unique<Vsh>(std::move(cwd), std::move(hin), std::move(winapi)); 

    vsh->start();

    return 0;
}