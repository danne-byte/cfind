#include "cli.hpp"

#include <cctype>
#include <algorithm>


namespace {

    const char* OPT_INDICATOR = "--";
    const char* OPT_NON_DUPLICATES = "--non-duplicates";
    const char* OPT_HELP = "--help";
    const char* OPT_COLOR = "--color";
    const char* OPT_CHUNK_SIZE = "--chunk-size";

    const char* USAGE = "cfind [--help] [--color] [--non-duplicates] [--chunk-size=123M|K|G] <source> <target>";

    bool parse_chunk_size_value(const std::string& option, cli::CommandOptions& cmd_options) {

        auto equals_it = std::find(option.begin(), option.end(), '=');

        if (equals_it == option.end()) { // no '=' found
            return false;
        }

        ++equals_it;

        if (equals_it == option.end()) { // no value after '='
            return false;
        }

        std::string chunk_size_str = "";
        unsigned int prefix_size = 0;
        const unsigned int ILLEGAL = 1;

        std::for_each(equals_it, option.end(), [&](const char& val) {
            if(!std::isdigit(val)) {
                prefix_size = val == 'M' ? 1024*1024 : val == 'K' ? 1024 : val =='G' ? 1024*1024*1024 : ILLEGAL;
            }

            if (prefix_size == 0) {
                chunk_size_str.push_back(val);
            }
        });

        if (prefix_size == ILLEGAL) {
            return false;
        }

        cmd_options.chunk_size = std::stoul(chunk_size_str) * prefix_size;

        return true;
    }

    bool found_option(cli::CommandOptions& cmd_options, const std::string& option) {

        if (!cmd_options.source.empty() || !cmd_options.destination.empty()) {
            return false;
        }

        if (option == OPT_NON_DUPLICATES) {
            cmd_options.only_non_duplicates = true;
            return true;
        }

        if (option == OPT_HELP) {
            cmd_options.usage = true;
            return true;
        }

        if (option == OPT_COLOR) {
            cmd_options.color = true;
            return true;
        }

        if (option.starts_with(OPT_CHUNK_SIZE)) {
            return parse_chunk_size_value(option, cmd_options);
        }

        return false;
    }

    bool found_data_dir(cli::CommandOptions& cmd_options, const std::string& data_path) {
        if(cmd_options.source.empty()) {
            cmd_options.source = data_path;
            return true;
        }

        else if(cmd_options.destination.empty()) {
            cmd_options.destination = data_path;
            return true;
        }

        return false;
    }

}

cli::CommandOptions cli::parse_command_line(int argc, char* argv[]) {

    CommandOptions cmd_options;

    if (argc <= 1) {
        return cmd_options;
    }

    for(auto ix=1; ix < argc; ++ix) {
        auto current_value = std::string(argv[ix]);
        bool is_valid = false;

        if (current_value.starts_with(OPT_INDICATOR)) {
            is_valid = found_option(cmd_options, current_value);
        }

        else {
            is_valid = found_data_dir(cmd_options, current_value);
        }

        if (is_valid) {
            cmd_options.empty = false;
        }

        if(!is_valid) {
            break;
        }

    }

    return cmd_options;
}

const char* cli::usage_string() {
    return USAGE;
}
