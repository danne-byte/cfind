#include "cfind.hpp"

#include <iostream>

#include "analyzer.hpp"
#include "cli.hpp"
#include "crypto.hpp"
#include "console.hpp"
#include "fileprocessor.hpp"
#include "io.hpp"
#include "log.hpp"

namespace fs = std::filesystem;

using namespace logger;


struct CDContext {

    std::map<std::uintmax_t, std::list<cfind::PathEntry> > size_map;
};


void print_result(std::list<cfind::PathEntryResult>& result_list, const cfind::Options& options) {
    cfind::Console console;
    console.print_result(result_list, options);
}

void print_usage() {
    std::cout << cli::usage_string() << std::endl;
}

std::list<cfind::PathEntryResult> cfind::cfind(const std::string& source, const std::string& dest, const Options& options) {

    const std::list<std::string>& search_list{source, dest};

    CDContext context;
    // fileprocessor
    read_file_sizes(search_list, context.size_map);
    create_hashes(context.size_map);

    std::list<PathEntryResult> result_list;
    // analyzer
    analyze_result(source, context.size_map, result_list);

    print_result(result_list, options);

    return result_list;
}

int cfind::launch(int argc, char* argv[]) {
    
    auto cmd_options = cli::parse_command_line(argc, argv);

    if (cmd_options.empty || cmd_options.usage) {
        print_usage();
        return 0;
    }

    cfind::cfind(cmd_options.source, cmd_options.destination, {cmd_options.only_non_duplicates, cmd_options.color});
   
	return 0;
}




