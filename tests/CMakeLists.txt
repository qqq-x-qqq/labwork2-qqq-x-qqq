include(FetchContent)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/releases/download/v1.16.0/googletest-1.16.0.tar.gz
    DOWNLOAD_EXTRACT_TIMESTAMP ON
    FIND_PACKAGE_ARGS NAMES GTest
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
  number_tests
  conversion_tests.cpp
  arithmetic_tests.cpp
  comparison_tests.cpp
  output_tests.cpp
  edge_cases_tests.cpp
  compatibility_tests.cpp
)

target_link_libraries(
  number_tests
  number
  GTest::gtest_main
)

target_include_directories(number_tests PUBLIC ${PROJECT_SOURCE_DIR})

include(GoogleTest)

gtest_discover_tests(number_tests)