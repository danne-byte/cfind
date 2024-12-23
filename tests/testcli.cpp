#include <catch2/catch_test_macros.hpp>

#include "../src/cli.hpp"


TEST_CASE( "empty command line", "[cli]" ) {

    cli::CommandOptions cmd_opts = cli::parse_command_line(0, NULL);

    REQUIRE(cmd_opts.source == "");

}

TEST_CASE( "empty command line, no arguments given", "[cli]" ) {

    const char* argv[] = {"cfind"};
    cli::CommandOptions cmd_opts = cli::parse_command_line(1, const_cast<char**>(argv));

    REQUIRE(cmd_opts.empty);
    REQUIRE(cmd_opts.source == "");

}

TEST_CASE( "invalid command line, only opts -- given", "[cli]" ) {

    const char* argv[] = {"cfind", "--"};
    cli::CommandOptions cmd_opts = cli::parse_command_line(1, const_cast<char**>(argv));

    REQUIRE(cmd_opts.empty);
    REQUIRE(cmd_opts.source == "");

}

TEST_CASE( "valid commmand line", "[cli]" ) {

    const char* argv[] = {"cfind", "bbbb", "cccc"};

    cli::CommandOptions cmd_opts = cli::parse_command_line(3, const_cast<char**>(argv));

    REQUIRE(cmd_opts.only_non_duplicates == false);
    REQUIRE(cmd_opts.source == "bbbb");
    REQUIRE(cmd_opts.destination == "cccc");

}

TEST_CASE( "valid command line, option show only non duplicates", "[cli]" ) {

    const char* argv[] = {"cfind", "--non-duplicates", "source", "destination"};

    cli::CommandOptions cmd_opts = cli::parse_command_line(4, const_cast<char**>(argv));

    REQUIRE(cmd_opts.only_non_duplicates == true);
    REQUIRE(cmd_opts.source == "source");
    REQUIRE(cmd_opts.destination == "destination");

}

TEST_CASE( "valid command line, option color", "[cli]" ) {

    const char* argv[] = {"cfind", "--color", "source", "destination"};

    cli::CommandOptions cmd_opts = cli::parse_command_line(4, const_cast<char**>(argv));

    REQUIRE(cmd_opts.only_non_duplicates == false);
    REQUIRE(cmd_opts.color == true);
    REQUIRE(cmd_opts.source == "source");
    REQUIRE(cmd_opts.destination == "destination");

}

