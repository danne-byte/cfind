#include "cfind.hpp"

#include <iostream>

#include "analyzer.hpp"
#include "cli.hpp"
#include "crypto.hpp"
#include "console.hpp"
#include "fileprocessor.hpp"
#include "io.hpp"
#include "log.hpp"
#include "projectinfo.hpp"

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

std::list<cfind::PathEntryResult> cfind::find_duplicates(const std::string& source, const std::string& target, const Options& options) {

    const std::list<std::string>& search_list{source, target};

    CDContext context;
    // fileprocessor
    read_file_sizes(search_list, context.size_map);

    std::list<PathEntryResult> result_list;
    // analyzer
    auto analyzer_session = create_analyzer_session(source, options.chunk_size);
    analyze_paths(analyzer_session, context.size_map, result_list);

    print_result(result_list, options);

    return result_list;
}

int cfind::launch(int argc, char* argv[]) {
    
    auto cmd_options = cli::parse_command_line(argc, argv);

    if (cmd_options.empty || cmd_options.usage) {
        print_usage();
        return 0;
    }

    cfind::find_duplicates(cmd_options.source, cmd_options.destination, {cmd_options.only_non_duplicates, cmd_options.color, cmd_options.chunk_size});
   
	return 0;
}




