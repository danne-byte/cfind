#ifndef CFIND_HPP
#define CFIND_HPP

#include <filesystem>
#include <list>
#include <string>


namespace cfind {

    /* Process files on storage device
    *
    * Files are read from files and sorted depending on their file size.
    * If there are multiple files for a size those files are read
    * and a hash signature is created for fast comparison.
    */

    struct PathEntry {
        std::filesystem::path path;
        std::uintmax_t size = 0;
        unsigned char* hash = NULL;
        size_t hash_size = 0;
    };

    struct PathEntryResult {
        const PathEntry path_entry;
        std::list<PathEntry> duplicate_list;
    };

    struct Options {
        bool only_non_duplicates = false;
        bool use_color = false;
        std::uintmax_t chunk_size = 512 * 1024 * 1024; // 512MiB
    };

    std::list<PathEntryResult> find_duplicates(const std::string& source, const std::string& target, const Options& options);

    int launch(int argc, char* argv[]);

}


#endif //CFIND_HPP
