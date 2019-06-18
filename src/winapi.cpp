#include <winapi.hpp>
#include <iostream>

using namespace winapi;

WinApiException::WinApiException(const std::string& message) noexcept
    : std::runtime_error(message) {
    
}

void WindowsApiService::read_console_input(
    HANDLE handle, 
    INPUT_RECORD* ir, 
    DWORD length, 
    DWORD* count
) const {
   if (!ReadConsoleInput(handle, ir, length, count)) {
       throw WinApiException("Failed to read console input");
   }
}

void WindowsApiService::create_process(
   LPCWSTR lpApplicationName,
   LPWSTR lpCommandLine,
   LPSECURITY_ATTRIBUTES lpProcessAttributes,
   LPSECURITY_ATTRIBUTES lpThreadAttributes,
   BOOL bInheritHandles,
   DWORD dwCreationFlags,
   LPVOID lpEnvironment,
   LPCWSTR lpCurrentDirectory,
   LPSTARTUPINFOW lpStartupInfo,
   LPPROCESS_INFORMATION lpProcessInformation 
) const {
    if (!CreateProcessW(
            lpApplicationName,
            lpCommandLine,
            lpProcessAttributes,
            lpThreadAttributes,
            bInheritHandles,
            dwCreationFlags,
            lpEnvironment,
            lpCurrentDirectory,
            lpStartupInfo,
            lpProcessInformation)
    ) {
        throw WinApiException("Failed to create process");
    }
}

void WindowsApiService::wait_for_single_object(HANDLE handle, int length) const {
    if (WaitForSingleObject(handle, length)) {
        throw WinApiException("Failed to wait for object");
    }
}

void WindowsApiService::create_pipe(
    PHANDLE std_out_rd, 
    PHANDLE std_out_wr, 
    SECURITY_ATTRIBUTES* sattr, 
    int count
) const {
    if (!CreatePipe(std_out_rd, std_out_wr, sattr, count)) {
        throw WinApiException("Failed to create pipe");
    }
}

void WindowsApiService::create_child_process(
    wchar_t* cmd, 
    STARTUPINFOW* startup_info, 
    PROCESS_INFORMATION* proc_info
) const {
    this->create_process(
        nullptr,
        cmd,
        nullptr,
        nullptr,
        true,
        0,
        nullptr,
        nullptr,
        startup_info,
        proc_info
    );
}

void WindowsApiService::set_handle_information(HANDLE handle, int mask, int flags) const {
    if (!SetHandleInformation(handle, mask, flags)) {
        throw WinApiException("Failed to set handle information");
    }
}
