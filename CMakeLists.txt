cmake_minimum_required(VERSION 3.21)

project(mean_median_demo LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(statistics
    src/statistics.cpp
)

target_include_directories(statistics PUBLIC include)

add_executable(mean_median
    src/main.cpp
)

target_link_libraries(mean_median PRIVATE statistics)

include(CTest)

if(BUILD_TESTING)
    find_package(GTest CONFIG REQUIRED)

    add_executable(tests
        tests/statistics_test.cpp
    )

    target_link_libraries(tests PRIVATE statistics GTest::gtest_main)

    include(GoogleTest)
    gtest_discover_tests(tests)
endif()
