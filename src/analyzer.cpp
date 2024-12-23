#include "analyzer.hpp"

#include <filesystem>

namespace fs = std::filesystem;

namespace {

    bool is_in_dir_path(const fs::path& dir_path, const fs::path& path) {
        const auto rel_dir_string = fs::relative(dir_path).string();
        const auto rel_path_string = fs::relative(path).string();

        return rel_path_string.starts_with(rel_dir_string);
    }

    bool is_hash_equal(unsigned char* l_hash, size_t lh_size, unsigned char* r_hash, size_t rh_size) {

        if (!lh_size || !rh_size) {
            return false;
        }

        if (lh_size != rh_size) {
            return false;
        }

        if (l_hash == NULL || r_hash == NULL) {
            return false;
        }

        for (size_t ix=0; ix < lh_size; ++ix) {
            unsigned char lc = *(l_hash+ix);
            unsigned char rc = *(r_hash+ix);

            if (lc != rc) {
                return false;
            }
        }

        return true;
    }

    void analyze_source_path_entry(const cfind::PathEntry& path_entry, const std::list<cfind::PathEntry>& path_entry_list, std::list<cfind::PathEntry>& duplicate_list)  {

        for (const auto& list_path_entry : path_entry_list) {
            if (fs::equivalent(path_entry.path, list_path_entry.path)) {
                continue; //ignore self, might be buggy
            }


            if (is_hash_equal(path_entry.hash, path_entry.hash_size, list_path_entry.hash, list_path_entry.hash_size)) {
                duplicate_list.push_back(std::ref(list_path_entry));
            }

        }

    }
}

void cfind::analyze_result(const std::string& source, const std::map<std::uintmax_t, std::list<PathEntry> >& path_map, std::list<PathEntryResult>& result_list) {

    for (const auto& [size, path_entry_list] : path_map) {

        for (const auto& path_entry : path_entry_list) {

            const auto source_rel_string = fs::relative(source).string();
            const auto rel_path_entry = fs::relative(path_entry.path);
            const auto rel_path_entry_string = rel_path_entry.string();

            if (is_in_dir_path(source, path_entry.path)) {
                cfind::PathEntryResult pe_result{path_entry, {}};

                analyze_source_path_entry(path_entry, path_entry_list, pe_result.duplicate_list);
                result_list.push_back(pe_result);
            }

        }
    }

}
