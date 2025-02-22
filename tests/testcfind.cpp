#include <catch2/catch_test_macros.hpp>

#include <cstdlib>
#include <filesystem>
#include <stdexcept>

#include "../src/cli.hpp"
#include "../src/cfind.hpp"

namespace {
	const std::string get_testdata_root() {
		const char* root_env = std::getenv("TESTDATA_ROOT");

		if (!root_env) {
			return ".";
		}

		const std::filesystem::path root_path{root_env};

		if (!std::filesystem::exists(root_path)) {
			throw std::runtime_error("no path found");
		}

		return root_path.string();
	}

	const std::string td(const std::string& data) {
		const std::filesystem::path td_root{get_testdata_root()};
		const std::filesystem::path data_path{data};

		const auto full_path = td_root / data_path;
		return full_path.string();
	}

}

TEST_CASE( "cli empty commmand line", "[cli]" ) {

    cli::CommandOptions cmd_opts = cli::parse_command_line(0, NULL);

    REQUIRE(cmd_opts.source == "");

}

TEST_CASE("cfind basic data set", "[cfind]") {

    auto result_list = cfind::find_duplicates(td("basic_data/source"), td("basic_data/dest"), {false, false});

    auto it = result_list.begin();
    REQUIRE(it != result_list.end());
    REQUIRE(it->path_entry.path.string() == td("basic_data/source/onlyinsource.txt"));

    ++it;
    REQUIRE(it != result_list.end());
    REQUIRE(it->path_entry.path.string() == td("basic_data/source/helloworld.txt"));

    auto dup_list_it = it->duplicate_list.begin();
    REQUIRE(dup_list_it != it->duplicate_list.end());
    REQUIRE(dup_list_it->path.string() == td("basic_data/dest/helloworld.txt"));
}

TEST_CASE("cfind large data set", "[cfind]") {

    auto result_list = cfind::find_duplicates(td("large_files/source"), td("large_files/dest"), {false, false, 1024});
    auto it = result_list.begin();

    REQUIRE(it != result_list.end());
    REQUIRE(it->path_entry.path.string() == td("large_files/source/1k_file"));
    REQUIRE(it->duplicate_list.size() == 1);
    REQUIRE(it->duplicate_list.begin()->path.string() == td("large_files/dest/1k_file"));
    
    ++it;
    REQUIRE(it != result_list.end());
    REQUIRE(it->path_entry.path.string() == td("large_files/source/plus_1k_file"));
    REQUIRE(it->duplicate_list.size() == 1);
    REQUIRE(it->duplicate_list.begin()->path.string() == td("large_files/dest/plus_1k_file"));

    ++it;
    REQUIRE(it != result_list.end());
    REQUIRE(it->path_entry.path.string() == td("large_files/source/plus_1k_file_only_in_source"));
    REQUIRE(it->duplicate_list.size() == 0);
    
    ++it;
    REQUIRE(it != result_list.end());
    REQUIRE(it->path_entry.path.string() == td("large_files/source/1M_file"));
    REQUIRE(it->duplicate_list.size() == 1);
    REQUIRE(it->duplicate_list.begin()->path.string() == td("large_files/dest/1M_file"));

    ++it;
    REQUIRE(it != result_list.end());
    REQUIRE(it->path_entry.path.string() == td("large_files/source/plus_1M_file_only_in_source"));
    REQUIRE(it->duplicate_list.size() == 0);

    ++it;
    REQUIRE(it != result_list.end());
    REQUIRE(it->path_entry.path.string() == td("large_files/source/plus_1M_file"));
    REQUIRE(it->duplicate_list.size() == 1);
    REQUIRE(it->duplicate_list.begin()->path.string() == td("large_files/dest/plus_1M_file"));
}
