#ifndef ANALYZER_HPP
#define ANALYZER_HPP

#include <list>
#include <string>
#include <map>

#include "cfind.hpp"
#include "fileprocessor.hpp"

namespace cfind {

    void analyze_result(const std::string& source, const std::map<std::uintmax_t, std::list<PathEntry> >& path_map, std::list<PathEntryResult>& result_list);

}

#endif // ANALYZER_HPP
