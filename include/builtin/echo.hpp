#pragma once

#include <builtin/command.hpp>

namespace vsh::builtin {
    class Echo : Command {
        public:
        void execute(int argc, char** argv);
    };
};
