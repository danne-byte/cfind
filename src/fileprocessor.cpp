#include "fileprocessor.hpp"

#include <filesystem>
#include <functional>

#include "crypto.hpp"
#include "io.hpp"
#include "log.hpp"

using namespace cfind;

namespace {
    std::function<void(const std::filesystem::path&)> create_on_regular_file(std::map<std::uintmax_t, std::list<PathEntry> >& size_map) {
        return [&] (const std::filesystem::path& path) {
            auto size = std::filesystem::file_size(path);

            PathEntry se {path, size};
            size_map[size].push_back(se);
        };
    }

    void process_path(const std::filesystem::path& path, std::function<void(const std::filesystem::path&)> on_regular_file) {
        //TRACE_CALL;

        if (std::filesystem::is_regular_file(path)) {
            //LOG_DEBUG(path.filename() << " is regular file");
            on_regular_file(path);
        }

        else if (std::filesystem::is_directory(path)) {
            for (auto const& dir_entry : std::filesystem::directory_iterator{path}) {
                process_path(dir_entry.path(), on_regular_file);
            }

        }

        else if (std::filesystem::is_symlink(path)) {

        }
    }

    void make_checksum(PathEntry& size_entry) {

        auto relative_path = std::filesystem::relative(size_entry.path);


        if (!std::filesystem::exists(size_entry.path)) {
            //LOG_ERROR("file dont exist: " << size_entry.path.string());
            return;
        }

        std::unique_ptr<char[]> buf(new char[size_entry.size]);

        auto buf_size = io::read_file_content(relative_path.string(), size_entry.size, buf.get());

        size_entry.hash_size = crypto::allocate_sha56_buffer(&size_entry.hash);
        crypto::make_sha256(buf.get(), buf_size, size_entry.hash_size, size_entry.hash);

        return;
    }

    void create_hashes_from_list(std::list<PathEntry>& path_entry_list) {

        for (auto& se : path_entry_list) {
            make_checksum(se);
        }
    }
}

void cfind::read_file_sizes(const std::list<std::string>& search_list, std::map<std::uintmax_t, std::list<PathEntry>>& size_map)
{
    //TRACE_CALL;

    auto f_on_regular_file = create_on_regular_file(size_map);

    for (auto search : search_list) {
        process_path(search, f_on_regular_file);
    }

}

void cfind::create_hashes(std::map<std::uintmax_t, std::list<PathEntry>>& size_map)
{
    for (auto& sm_pair : size_map) {
        //LOG_DEBUG("size: " << sm_pair.first << " count: " << sm_pair.second.size());

        std::list<PathEntry>& path_entry_list = sm_pair.second;

        if (1 < path_entry_list.size()) {
            create_hashes_from_list(sm_pair.second);
        }
    }
}
