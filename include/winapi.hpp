#ifndef VSH_WINAPI_H
#define VSH_WINAPI_H

#include <windows.h>
#include <stdexcept>
#include <string>

namespace winapi {
    /** A simple wrapper around windows.h */
    class WindowsApiService {
    public:

        /**
         * Wrapper to windows.h -> ReadConsoleInput
         */
        void read_console_input(
            HANDLE handle, 
            INPUT_RECORD* ir, 
            DWORD length, 
            DWORD* count
        ) const;

        /** Wrapper to windows.h -> CreateProcess */
        void create_process(
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
        ) const;
    };

    class WinApiException : public std::runtime_error {
        public:
        WinApiException(const std::string& message) noexcept;
    };
}
#endif