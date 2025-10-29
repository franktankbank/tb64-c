cmake_minimum_required(VERSION 3.21)

include(cmake/prelude.cmake)

project(
    tb64
    VERSION 0.1.1
    DESCRIPTION "A niche tool to encode text in base64 3 times. (C version)"
    HOMEPAGE_URL "https://github.com/franktankbank/tb64-c"
    LANGUAGES C
)

include(FetchContent)

# Declare turbo-base64 dependency
FetchContent_Declare(
  turbo_base64
  GIT_REPOSITORY https://github.com/franktankbank/Turbo-Base64.git
  GIT_TAG        master  # or a specific tag/commit for stability
)

# Download and make the target available
FetchContent_MakeAvailable(turbo_base64)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

include(cmake/variables.cmake)

# ---- Declare executable ----

add_executable(tb64 src/tb64.c src/box.c src/clip.c src/safe.c src/base64.c)
add_executable(tb64::exe ALIAS tb64)

set_property(TARGET tb64 PROPERTY OUTPUT_NAME tb64)

target_compile_features(tb64 PRIVATE c_std_99)

target_include_directories(tb64 PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_include_directories(tb64 PRIVATE ${turbo_base64_SOURCE_DIR})
target_link_libraries(tb64 PRIVATE base64)

# ---- Install rules ----

if(NOT CMAKE_SKIP_INSTALL_RULES)
  include(cmake/install-rules.cmake)
endif()

# ---- Developer mode ----

if(NOT tb64_DEVELOPER_MODE)
  return()
elseif(NOT PROJECT_IS_TOP_LEVEL)
  message(
      AUTHOR_WARNING
      "Developer mode is intended for developers of tb64"
  )
endif()

include(cmake/dev-mode.cmake)
