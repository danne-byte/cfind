FetchContent_Declare(
  fmt
  GIT_REPOSITORY https://github.com/fmtlib/fmt
  GIT_TAG        11.0.2
  EXCLUDE_FROM_ALL
)
FetchContent_MakeAvailable(fmt)

# libcfind
configure_file(projectinfo.cpp.in projectinfo.cpp)
add_library (cfind cdiff.cpp fileprocessor.cpp log.cpp io.cpp crypto.cpp analyzer.cpp cli.cpp console.cpp projectinfo.cpp)
target_link_libraries(cfind PRIVATE crypto ssl fmt::fmt)
target_compile_options(cfind PRIVATE ${COMPILE_OPTS})
target_include_directories(cfind PUBLIC ./)
set_property(TARGET cfind PROPERTY VERSION "${PROJECT_VERSION}")
set_property(TARGET cfind PROPERTY SOVERSION "${PROJECT_VERSION_MAJOR}")

# cfind cli
add_executable (cfind-cli main.cpp)
target_link_libraries(cfind-cli PRIVATE cfind crypto ssl fmt::fmt)
set_target_properties(cfind-cli PROPERTIES OUTPUT_NAME "cfind")
target_compile_options(cfind-cli PRIVATE ${COMPILE_OPTS})
set_property(TARGET cfind-cli PROPERTY VERSION "${PROJECT_VERSION}")
set_property(TARGET cfind-cli PROPERTY SOVERSION "${PROJECT_VERSION_MAJOR}")
install(TARGETS cfind-cli RUNTIME DESTINATION bin)

# configure cpack
set(CPACK_BINARY_DEB "ON")
set(CPACK_BINARY_RPM "ON")
set(CPACK_PACKAGE_CONTACT "danne6543")
include(CPack)


