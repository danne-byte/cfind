#ifndef FILEPROCESSOR_HPP
#define FILEPROCESSOR_HPP

#include <filesystem>
#include <list>
#include <map>
#include <string>

#include "cfind.hpp"


namespace cfind{

    void read_file_sizes(const std::list<std::string>& search_list, std::map<std::uintmax_t, std::list<PathEntry> >& size_map);

}


#endif // FILEPROCESSOR_HPP
