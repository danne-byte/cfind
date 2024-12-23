#ifndef FILEPROCESSOR_HPP
#define FILEPROCESSOR_HPP

#include <filesystem>
#include <list>
#include <map>
#include <string>

#include "cfind.hpp"


namespace cfind{

    /* Read all files and their sizes from the list of directories.
    *
    * search_list - list of directories to search for files.
    * size_map - result of search with files ordered in map by file size.
    */
    void read_file_sizes(const std::list<std::string>& search_list, std::map<std::uintmax_t, std::list<PathEntry> >& size_map);

    /* Create hashes for files.
    * size_map - map with files sorted by size, entries are updated with result
    */
    void create_hashes(std::map<std::uintmax_t, std::list<PathEntry> >& size_map);

}


#endif // FILEPROCESSOR_HPP
