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

        /** Wrapper to windows.h -> WaitForSingleObject */
        void wait_for_single_object(HANDLE handle, int length) const;

        void create_pipe(PHANDLE std_out_rd, PHANDLE std_out_wr, SECURITY_ATTRIBUTES* sattr, int count) const;

        void create_child_process(wchar_t* cmd, STARTUPINFOW* startup_info, PROCESS_INFORMATION* process_info) const;

        /** Wrapper around windows.h -> SetHandleInformation */
        void set_handle_information(HANDLE handle, int mask, int flags) const;

        /** Wrapper around windows.h -> _getcwd */
        void get_cwd(wchar_t* buffer, int len) const;
    };

    class WinApiException : public std::runtime_error {
        public:
        WinApiException(const std::string& message) noexcept;
    };
}
#endif