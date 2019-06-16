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
