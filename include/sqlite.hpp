#ifndef VSH_SQLITE_HPP
#define VSH_SQLITE_HPP

#include <string>

namespace SQLite {
    class SQLiteApi {
        private:
        const std::string location;

        public:
        SQLiteApi(std::string location);
    };
}

#endif
