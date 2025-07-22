include(cmake/folders.cmake)

add_custom_target(
    run-exe
    COMMAND tb64
    VERBATIM
)
add_dependencies(run-exe tb64)

include(cmake/lint-targets.cmake)
include(cmake/spell-targets.cmake)

add_folders(Project)
