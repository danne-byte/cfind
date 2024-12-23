#include <catch2/catch_test_macros.hpp>

#include "../src/cli.hpp"
#include "../src/cfind.hpp"

TEST_CASE( "cli empty commmand line", "[cli]" ) {

    cli::CommandOptions cmd_opts = cli::parse_command_line(0, NULL);

    REQUIRE(cmd_opts.source == "");

}

TEST_CASE("cfind basic data set", "[cfind]") {

    auto result_list = cfind::cfind("tests/data/basic_data/source", "tests/data/basic_data/dest", {false, false});

    auto it = result_list.begin();
    REQUIRE(it != result_list.end());
    REQUIRE(it->path_entry.path.string() == "tests/data/basic_data/source/onlyinsource.txt");

    ++it;
    REQUIRE(it != result_list.end());
    REQUIRE(it->path_entry.path.string() == "tests/data/basic_data/source/helloworld.txt");

    auto dup_list_it = it->duplicate_list.begin();
    REQUIRE(dup_list_it != it->duplicate_list.end());
    REQUIRE(dup_list_it->path.string() == "tests/data/basic_data/dest/helloworld.txt");
}
