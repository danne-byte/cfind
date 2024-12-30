#include "fileprocessor.hpp"

#include <filesystem>
#include <functional>


using namespace cfind;

namespace {
    std::function<void(const std::filesystem::path&)> create_on_regular_file(std::map<std::uintmax_t, std::list<PathEntry> >& size_map) {
        return [&] (const std::filesystem::path& path) {
            auto size = std::filesystem::file_size(path);

            PathEntry se {path, size};
            size_map[size].push_back(se);
        };
    }

    void walk_path(const std::filesystem::path& path, std::function<void(const std::filesystem::path&)> on_regular_file) {

        if (std::filesystem::is_regular_file(path)) {
            on_regular_file(path);
        }

        else if (std::filesystem::is_directory(path)) {
            for (auto const& dir_entry : std::filesystem::directory_iterator{path}) {
                walk_path(dir_entry.path(), on_regular_file);
            }
        }

        else if (std::filesystem::is_symlink(path)) {

        }
    }

}

void cfind::read_file_sizes(const std::list<std::string>& search_list, std::map<std::uintmax_t, std::list<PathEntry>>& size_map)
{
    auto f_on_regular_file = create_on_regular_file(size_map);

    for (auto search : search_list) {
        walk_path(search, f_on_regular_file);
    }
}
