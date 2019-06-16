#ifndef VSH_COMMAND_HPP
#define VSH_COMMAND_HPP

namespace vsh::builtin {
    class Command {
        public:
            virtual void execute(int argc, char** argv);
    };
};

#endif
