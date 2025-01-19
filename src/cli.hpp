#ifndef CLI_HPP_INCLUDED
#define CLI_HPP_INCLUDED

#include <cstdint>
#include <string>

namespace cli {

    struct CommandOptions {

        std::string source;
        std::string destination;
        bool only_non_duplicates = false;
        bool usage = false;
        bool empty = true;
        bool color = false;
        std::uintmax_t chunk_size = 512 * 1024 * 1024; // 512MiB
        bool invalid = true;
    };

    CommandOptions parse_command_line(int argc, char* argv[]);
    const char* usage_string();

}

#endif // CLI_HPP_INCLUDED
