add_compile_options(-Wall -Wextra -Wpedantic -Wconversion -Werror -Wsign-conversion)

add_executable(tests test.cpp testcli.cpp testcfind.cpp)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain cfind crypto ssl fmt::fmt)
target_compile_options(tests PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Werror -Wsign-conversion)
