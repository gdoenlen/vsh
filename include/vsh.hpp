#ifndef VSH_HPP
#define VSH_HPP

#include <string>
#include <memory>
#include <winapi.hpp>

namespace vsh {
    /** The shell itself */
    class Vsh {
        private:
            /** current working directory */
            std::wstring cwd;

            /** windows handle to stdin */
            const HANDLE hin;

            const winapi::WindowsApiService winapi; 
            
        public:
            Vsh(std::wstring cwd, HANDLE hin, winapi::WindowsApiService winapi);
            void start();
            static std::unique_ptr<std::string> process_key_event(char key, std::wstring& input);
    };


    class Tracker {
        private:

        public:
            Tracker();
            void push(std::shared_ptr<std::string> input) const;
    };
};

#endif
