find_package(fastdl REQUIRED)
find_package(gaio REQUIRED)
find_package(vinbero_com REQUIRED)

add_library(vinbero_iplogger MODULE)

target_sources(
    vinbero_iplogger
    PRIVATE
    vinbero_iplogger.c
)
target_compile_options(vinbero_iplogger PRIVATE -Wall)

set_target_properties(
    vinbero_iplogger PROPERTIES
    C_STANDARD 11
    PREFIX ""
    VERSION ${version}
    SOVERSION ${soversion}
)

target_include_directories(
    vinbero_iplogger
    PRIVATE
    ${PROJECT_BINARY_DIR}
)

target_link_libraries(
    vinbero_iplogger
    PRIVATE
    vinbero_com::vinbero_com
    fastdl::fastdl
    gaio::gaio
)

configure_file(
    "${PROJECT_SOURCE_DIR}/src/config.h.in"
    "${PROJECT_BINARY_DIR}/config.h"
    @ONLY
)

install(
    TARGETS vinbero_iplogger
    LIBRARY DESTINATION lib/vinbero
    PUBLIC_HEADER DESTINATION include/vinbero
)
