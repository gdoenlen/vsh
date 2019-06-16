#include <iostream>
#include <windows.h>
#include <utility>
#include <vector>
#include <string>

#include <vsh.hpp>
#include <winapi.hpp>

using std::shared_ptr;
using std::vector;
using std::wstring;
using std::cout;
using std::string;
using std::unique_ptr;
using std::make_unique;
using std::wcslen;
using std::wcscpy;

using namespace vsh;
using winapi::WindowsApiService;

Vsh::Vsh(string cwd, HANDLE hin, WindowsApiService winapi) 
    : cwd(cwd), hin(hin), winapi(winapi) {

}

void Vsh::start() {
    DWORD count;
    INPUT_RECORD inputRecord;
    wstring input;

    cout << "VSH " << this->cwd << "> ";
    for (;;) {
        string buffer;
        do {
            this->winapi.read_console_input(this->hin, &inputRecord, 1, &count);
        } while (inputRecord.EventType != KEY_EVENT || !inputRecord.Event.KeyEvent.bKeyDown);

        auto key = inputRecord.Event.KeyEvent.uChar.UnicodeChar; 
        cout << *process_key_event(key, input);

        if (key == '\r') {
            // awful hack to convert from const wchar_t* to wchar_t* for windows
            auto winput = make_unique<wchar_t[]>(wcslen(input.c_str()) + 1);
            wcscpy(winput.get(), input.c_str());

            STARTUPINFOW info;
            PROCESS_INFORMATION pinfo;
            winapi.create_process(
                nullptr, 
                winput.get(), 
                nullptr, 
                nullptr, 
                true, 
                0, 
                nullptr,
                nullptr,
                &info,
                &pinfo 
            );
            winapi.wait_for_single_object(pinfo.hProcess, INFINITE);

            // todo push history 
            input = wstring();
            cout << "VSH " << this->cwd << "> ";
        }
    }
}

unique_ptr<string> Vsh::process_key_event(char key, wstring& input) {
    // should this be allocated each time?
    auto buffer = make_unique<string>();
    switch (key) {
        case '\b':
            if (input.size() == 0) { break; }
            buffer->push_back(key);
            buffer->push_back(' ');
            buffer->push_back(key);
            input.pop_back();
            break;
        case '\r':
            buffer->push_back(key);
            buffer->push_back('\n');
            break;
        default:
            buffer->push_back(key);
            input.push_back(key);
            break;
    }

    return buffer;
}
