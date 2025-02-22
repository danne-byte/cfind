
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.4.0 # or a later release
)
FetchContent_MakeAvailable(Catch2)




add_compile_options(-Wall -Wextra -Wpedantic -Wconversion -Werror -Wsign-conversion)

add_executable(tests test.cpp testcli.cpp testcfind.cpp)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain cfind crypto ssl fmt::fmt)
target_compile_options(tests PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Werror -Wsign-conversion)

include(CTest)
include(Catch)
catch_discover_tests(tests)
