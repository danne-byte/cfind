#include "analyzer.hpp"

#include <filesystem>

namespace fs = std::filesystem;

#include "crypto.hpp"
#include "io.hpp"

namespace {

    bool is_in_dir_path(const fs::path& dir_path, const fs::path& path) {
        const auto rel_dir_string = fs::relative(dir_path).string();
        const auto rel_path_string = fs::relative(path).string();

        return rel_path_string.starts_with(rel_dir_string);
    }

    struct FindDuplicatesStrategy {
        const std::uintmax_t chunk_size;
        std::map<std::string, std::vector<crypto::Digest>> checksum_map{};

        void find_dups_source_path_entry(const cfind::PathEntry& source_entry, const std::list<cfind::PathEntry>& path_entry_list, std::list<cfind::PathEntry>& duplicate_list) {
            for (const auto& path_entry : path_entry_list) {
                if (fs::equivalent(source_entry.path, path_entry.path)) {
                    continue; //ignore self, might be buggy
                }

                if (compare_hashes(source_entry, path_entry)) {
                    duplicate_list.push_back(std::ref(path_entry)); // ERROR FIX!!
                }

            }
        }

        crypto::Digest get_chunk_sum_by_ix(const cfind::PathEntry& path_entry, std::uintmax_t chunk_ix) {
            std::uintmax_t num_chunks = path_entry.size / chunk_size;
            std::uintmax_t last_chunk_size = path_entry.size % chunk_size;
            num_chunks += last_chunk_size != 0 ? 1 : 0;

            if (num_chunks <= chunk_ix) {
                return crypto::Digest(); // TODO: Throw here
            }

            if (auto search = checksum_map.find(path_entry.path.string()); search != checksum_map.end()) { // cache lookup
                const auto& chunk_vec = search->second;

                if (chunk_ix < chunk_vec.size()) {
                    return chunk_vec.at(chunk_ix);
                }
            }


            auto offset = chunk_ix * chunk_size;
            auto size = (chunk_size + offset > path_entry.size) ? path_entry.size - offset : chunk_size;

            io::Binary data(size);
            auto read_bytes = io::read_file(path_entry.path.string(), offset, size, data);

            if (read_bytes == 0) {
                return crypto::Digest(); // TODO: Throw here
            }

            auto digest = crypto::sha256(data);

            if (auto search = checksum_map.find(path_entry.path.string()); search != checksum_map.end()) { // update cache
                auto& chunk_vec = checksum_map[path_entry.path.string()];
                chunk_vec.push_back(digest); // BUG: if vector is not accessed sequentially this will not work.
            }

            else {                                                                                      // initialize new cache entry
                checksum_map.insert({path_entry.path.string(), {digest}});
            }


            return digest;
        }

        bool compare_hashes(const cfind::PathEntry& source_entry, const cfind::PathEntry& path_entry) {
            std::uintmax_t num_chunks = source_entry.size / chunk_size;
            num_chunks += source_entry.size % chunk_size != 0 ? 1 : 0;

            for(std::uintmax_t ix=0; ix < num_chunks; ++ix) {
                // 1. get_chunk_by_ix, source and path
                auto source_chunk_checksum = get_chunk_sum_by_ix(source_entry, ix);
                auto path_chunk_checksum = get_chunk_sum_by_ix(path_entry, ix);

                // BUG: delete hash or create a cache :)

                // 2. if not equal return false;
                //if (!is_hash_equal(source_chunk_checksum, crypto::sha256_hash_size(), path_chunk_checksum, crypto::sha256_hash_size())) {
                if (source_chunk_checksum != path_chunk_checksum) {
                    return false;
                }
            }

            return true;
        }
    };

}

cfind::AnalyzerSession cfind::create_analyzer_session(const std::string& source, const std::uintmax_t chunk_size) {
    return {source, chunk_size};
}

void cfind::analyze_paths(const cfind::AnalyzerSession& session, std::map<std::uintmax_t, std::list<PathEntry> >& path_map, std::list<PathEntryResult>& result_list) {
    for (const auto& [size, path_entry_list] : path_map) {

        FindDuplicatesStrategy findDupsStrategy{session.chunk_size};
        for (const auto& path_entry : path_entry_list) {

            if (is_in_dir_path(session.source, path_entry.path)) {
                cfind::PathEntryResult pe_result{path_entry, {}};

                findDupsStrategy.find_dups_source_path_entry(path_entry, path_entry_list, pe_result.duplicate_list);
                result_list.push_back(pe_result);
            }

        }
    }
}
