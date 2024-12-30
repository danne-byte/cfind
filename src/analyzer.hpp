#ifndef ANALYZER_HPP
#define ANALYZER_HPP

#include <list>
#include <string>
#include <map>

#include "cfind.hpp"
#include "fileprocessor.hpp"

namespace cfind {

    struct AnalyzerSession {
        const std::string& source;
        std::uintmax_t chunk_size;
    };

    AnalyzerSession create_analyzer_session(const std::string& source, const std::uintmax_t chunk_size);
    void analyze_paths(const AnalyzerSession& session, std::map<std::uintmax_t, std::list<PathEntry> >& path_map, std::list<PathEntryResult>& result_list);
}

#endif // ANALYZER_HPP
