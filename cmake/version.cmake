# define MAS_HASH_VERSION from git
set(MAS_HASH_VERSION "DEBUG_VERSION" CACHE STRING "maaskland version")
if (MAS_HASH_VERSION STREQUAL "DEBUG_VERSION")
    find_package(Git)
endif ()
if (MAS_HASH_VERSION STREQUAL "DEBUG_VERSION" AND GIT_FOUND)
    execute_process(
        COMMAND "${GIT_EXECUTABLE}" rev-parse HEAD
        WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
        RESULT_VARIABLE result
        OUTPUT_VARIABLE output
        ERROR_VARIABLE err
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )
    if (result EQUAL 0)
        set(MAS_HASH_VERSION "${output}")
    else ()
        message(WARNING "git rev-parse returning ${result}, output:\n${err}")
    endif ()
endif ()
message(STATUS "MAS_HASH_VERSION=${MAS_HASH_VERSION}")
add_compile_definitions(MAS_VERSION="${MAS_HASH_VERSION}")
