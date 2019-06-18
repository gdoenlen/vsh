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

            auto info = make_unique<STARTUPINFOW>();
            auto pinfo = make_unique<PROCESS_INFORMATION>();
            auto sattr = make_unique<SECURITY_ATTRIBUTES>();
            sattr->nLength = sizeof(sattr);
            sattr->bInheritHandle = true;
            sattr->lpSecurityDescriptor = nullptr;
            HANDLE stdout_rd, stdout_wr, stdin_rd, stdin_wr;

            // https://docs.microsoft.com/en-us/windows/desktop/ProcThread/creating-a-child-process-with-redirected-input-and-output
            this->winapi.create_pipe(&stdout_rd, &stdout_wr, sattr.get(), 0);    
            this->winapi.create_pipe(&stdin_rd, &stdin_wr, sattr.get(), 0);
            this->winapi.set_handle_information(stdout_rd, HANDLE_FLAG_INHERIT, 0);
            this->winapi.set_handle_information(stdin_wr, HANDLE_FLAG_INHERIT, 0);
            this->winapi.create_child_process(winput.get(), info.get(), pinfo.get());

            this->winapi.wait_for_single_object(pinfo->hProcess, INFINITE);

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
