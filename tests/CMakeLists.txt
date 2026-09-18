cmake_minimum_required(VERSION 3.21)

# Classroom 50 can configure this directory directly and supply REPO_ROOT.
# The fallback keeps the normal root-project build convenient for students.
if(NOT DEFINED REPO_ROOT)
    get_filename_component(REPO_ROOT "${CMAKE_CURRENT_LIST_DIR}/.." ABSOLUTE)
endif()
file(TO_CMAKE_PATH "${REPO_ROOT}" REPO_ROOT)

if(NOT IS_DIRECTORY "${REPO_ROOT}/include")
    message(FATAL_ERROR "REPO_ROOT does not contain include/: ${REPO_ROOT}")
endif()

if(NOT IS_DIRECTORY "${REPO_ROOT}/src")
    message(FATAL_ERROR "REPO_ROOT does not contain src/: ${REPO_ROOT}")
endif()

# When this directory is configured directly, point vcpkg at the repository
# manifest instead of looking for a second manifest inside tests/.
if(NOT DEFINED VCPKG_MANIFEST_DIR)
    set(VCPKG_MANIFEST_DIR "${REPO_ROOT}" CACHE PATH "Project vcpkg manifest directory")
endif()

project(InstructorTests LANGUAGES CXX)

include(CTest)

find_package(GTest CONFIG REQUIRED)

add_executable(instructor_tests
    statistics_test.cpp
    "${REPO_ROOT}/src/statistics.cpp"
)

target_link_libraries(instructor_tests PRIVATE GTest::gtest_main)
target_include_directories(instructor_tests PRIVATE "${REPO_ROOT}/include")
target_compile_features(instructor_tests PRIVATE cxx_std_17)

include(GoogleTest)
gtest_discover_tests(instructor_tests)
