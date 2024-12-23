#include "console.hpp"

#include <iostream>
#include <filesystem>

#include <fmt/color.h>

namespace fs = std::filesystem;

#include "cli.hpp"


namespace {

    fmt::text_style select_style(bool has_duplicates, bool use_color) {
        if (!use_color) {
            return fmt::text_style();
        }

        return has_duplicates ?
            fmt::text_style(fmt::emphasis::bold | fg(fmt::color::green)):
            fmt::text_style(fmt::emphasis::bold | fg(fmt::color::red));
    }
    void fn_print_path(const fs::path& path, bool has_duplicates, bool use_color) {
        fmt::text_style style = select_style(has_duplicates, use_color);
        fmt::print(style, "--- {}\n", path.string());
    }

    void fn_print_duplicate(const fs::path& path) {
        std::cout << "+++ " << path.string() << std::endl;
    }

    void fn_print_end() {
        //std::cout << std::endl;
    }

    void fn_print_non_duplicates_path(const fs::path& path) {
        std::cout << path.string() << std::endl;
    }

    void print_non_duplicates(std::list<cfind::PathEntryResult>& result_list) {
        for (const auto& result : result_list) {
            bool exists_duplicates = result.duplicate_list.size() != 0;

            if (!exists_duplicates) {
                fn_print_non_duplicates_path(result.path_entry.path);
            }

        }
    }

    class DuplicatePrinter {
    public:
        DuplicatePrinter(const cfind::Options& options):
        options(options) {

        }

        void print(std::list<cfind::PathEntryResult>& result_list);

    private:
        const cfind::Options& options;

    };

    void DuplicatePrinter::print(std::list<cfind::PathEntryResult>& result_list) {
        for (const auto& result : result_list) {
            const bool has_duplicates = result.duplicate_list.size() != 0;

            fn_print_path(result.path_entry.path, has_duplicates, this->options.use_color);

            for (const auto& dup_entry : result.duplicate_list) {
                fn_print_duplicate(dup_entry.path);
            }

            fn_print_end();
        }
    }

} // namespace



namespace cfind {

    void Console::print_result(std::list<cfind::PathEntryResult>& result_list, const Options& options) {

        if (options.only_non_duplicates) {
            print_non_duplicates(result_list);
        }

        else {
            DuplicatePrinter duplicate_printer {options};
            duplicate_printer.print(result_list);
        }
    }

void print_usage() {
    std::cout << cli::usage_string() << std::endl;
}

}
