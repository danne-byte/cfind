Include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.4.0 # or a later release
)
FetchContent_MakeAvailable(Catch2)


FetchContent_Declare(
  fmt
  GIT_REPOSITORY https://github.com/fmtlib/fmt
  GIT_TAG        11.0.2)
FetchContent_MakeAvailable(fmt)


add_compile_options(-Wall -Wextra -Wpedantic -Wconversion -Werror -Wsign-conversion)

add_library (cfind cdiff.cpp fileprocessor.cpp log.cpp io.cpp crypto.cpp analyzer.cpp cli.cpp console.cpp)
target_link_libraries(cfind PRIVATE crypto ssl fmt::fmt)
target_compile_options(cfind PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Werror -Wsign-conversion)

add_executable (cfind-cli main.cpp)
target_link_libraries(cfind-cli PRIVATE cfind crypto ssl fmt::fmt)
set_target_properties(cfind-cli PROPERTIES OUTPUT_NAME "cfind")
target_compile_options(cfind-cli PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Werror -Wsign-conversion)


