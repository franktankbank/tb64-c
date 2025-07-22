cmake_minimum_required(VERSION 3.21)

include(cmake/prelude.cmake)

project(
    tb64
    VERSION 0.1.0
    DESCRIPTION "A niche tool to encode text in base64 3 times. (C version)"
    HOMEPAGE_URL "https://github.com/franktankbank/tb64-c"
    LANGUAGES C
)

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

include(cmake/variables.cmake)
if(DEFINED ENV{VCPKG_ROOT})
  set(VCPKG_ROOT "$ENV{VCPKG_ROOT}")
  include(${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake)
else()
  message(FATAL_ERROR "vcpkg not found. Please set \'VCPKG_ROOT\'.")
endif()

# ---- Declare executable ----

add_executable(tb64 source/tb64.c source/box.c source/base64.c source/clip.c source/safe.c)
add_executable(tb64::exe ALIAS tb64)

set_property(TARGET tb64 PROPERTY OUTPUT_NAME tb64)

target_compile_features(tb64 PRIVATE c_std_99)

find_package(OpenSSL REQUIRED)
target_link_libraries(tb64 PRIVATE OpenSSL::SSL)
target_link_libraries(tb64 PRIVATE OpenSSL::Crypto)

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
