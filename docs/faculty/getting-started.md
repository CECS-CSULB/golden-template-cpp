# Getting Started with the C++ Code Template

This guide is for faculty who want to use this repository as the starting
point for a different C++ assignment. It focuses on replacing the starter code
and tests and keeping the local CMake build correct.

The most important idea is that CMake does not discover your source files by
itself. The [CMakeLists.txt](../../CMakeLists.txt) file declares targets, and
each target lists the source files it needs. When you replace the example
assignment, update those target definitions at the same time.

This guide does not cover course policies, grading configuration, or
distribution. It covers the code and local build side of the template.

## Start by understanding the current layout

The template currently contains one small library, one demonstration program,
and one GoogleTest executable:

~~~text
include/
└── statistics.h              # Public declarations
src/
├── statistics.cpp            # Library implementation
└── main.cpp                  # Demonstration program
tests/
└── statistics_test.cpp       # GoogleTest cases
CMakeLists.txt                # Target and build definitions
CMakePresets.json             # Local configure, build, and test presets
vcpkg.json                    # C++ package dependencies
~~~

This is an example layout, not a requirement. You can rename the files,
replace the directory contents, add directories, or use a different
organization. What matters is that the paths in CMakeLists.txt match the
layout you ship.

Before changing code, run the starter project once using the commands in
[the student build guide](../student/setup.md). This gives you a known-good
baseline and confirms that the local toolchain is working.

## Read [CMakeLists.txt](../../CMakeLists.txt) as the project map

The current file is short enough to read from top to bottom:

~~~cmake
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
~~~

Each section has a specific role:

- cmake_minimum_required states the minimum CMake version.
- project names the project and enables C++.
- The CMAKE_CXX_* settings require C++17 without compiler-specific
  extensions.
- add_library creates the reusable statistics target and lists its
  implementation files.
- target_include_directories tells consumers of that library where its public
  headers are located.
- add_executable creates the mean_median program and lists its source files.
- target_link_libraries connects the program to the reusable library.
- include(CTest) enables CTest support and the BUILD_TESTING option.
- The if(BUILD_TESTING) block creates the test executable, links it to the
  code under test and GoogleTest, and discovers individual GoogleTest cases.

When adapting the template, ask these questions:

1. What library or libraries contain the code students are implementing?
2. What executable, if any, should students be able to run?
3. What test executable should CMake build?
4. Which source files belong to each target?
5. Which include directories and external packages does each target need?

## Replace the assignment in a controlled order

### 1. Define the assignment contract

Decide the public interfaces before writing the implementation. For a library
assignment, this usually means:

- Header files under include/.
- Function, class, or other public declarations in those headers.
- Implementation files under src/.
- A clear statement of which files students should edit.

Keep the public names and signatures in the assignment instructions,
starter headers, and tests consistent. If students are expected to implement
an existing function or class, leave the declaration in place and replace only
the implementation body with a useful starter.

Update [the student assignment guide](../../STUDENT_README.md) as part of this
step. It should describe the actual files, interfaces, requirements, edge
cases, and expected input and output for the new assignment.

### 2. Replace the public headers and implementation files

Replace the example files under include/ and src/ with the files for the new
assignment. Keep the relationship between headers and implementation files
easy to follow:

~~~text
include/
└── queue.h
src/
└── queue.cpp
~~~

If the assignment has multiple components, list each implementation file in
the appropriate library target. Do not rely on an IDE project file or on
files being discovered automatically.

For example:

~~~cmake
add_library(assignment
    src/queue.cpp
    src/node.cpp
)

target_include_directories(assignment PUBLIC include)
~~~

The target name (assignment in this example) is used later when executables
and tests link to the library. Choose a stable, descriptive name and use it
consistently.

### 3. Decide whether to keep an executable

Keep src/main.cpp when students need to build and run a command-line program.
Replace it with the assignment's actual entry point and update the executable
target:

~~~cmake
add_executable(queue_demo
    src/main.cpp
)

target_link_libraries(queue_demo PRIVATE assignment)
~~~

If the assignment is library-only, remove the demonstration executable from
CMakeLists.txt rather than leaving a stale example target. Students can still
build and test the library through the test executable.

If the program has several executables, define each one explicitly and link
each target to the libraries it uses.

### 4. Replace the tests

Replace tests/statistics_test.cpp with tests for the new public behavior. Keep
tests in tests/ unless the assignment has a strong reason to use another
location. A GoogleTest file normally includes the public header and uses TEST,
EXPECT_*, or ASSERT_* macros:

~~~cpp
#include <gtest/gtest.h>

#include "queue.h"

TEST(QueueTest, StartsEmpty) {
    Queue queue;
    EXPECT_TRUE(queue.empty());
}
~~~

List every test source file in the test target:

~~~cmake
add_executable(tests
    tests/queue_test.cpp
    tests/node_test.cpp
)
~~~

The template links the tests to GTest::gtest_main. That library supplies the
GoogleTest entry point, so do not add a second main function to the test
source unless you intentionally replace the standard GoogleTest setup.

Keep the test target inside the if(BUILD_TESTING) block. This allows the
project to be configured without building tests when that is useful, while
the supplied default preset enables testing.

The final two lines register individual GoogleTest cases with CTest:

~~~cmake
include(GoogleTest)
gtest_discover_tests(tests)
~~~

Keep them when using GoogleTest. Without test discovery, the test executable
may build successfully while CTest reports no individual tests.

### 5. Update CMakeLists.txt

After replacing files, update every path and target name in CMakeLists.txt.
For the common library-plus-tests arrangement, the finished structure looks
like this:

~~~cmake
cmake_minimum_required(VERSION 3.21)

project(queue_assignment LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(assignment
    src/queue.cpp
    src/node.cpp
)

target_include_directories(assignment PUBLIC include)

include(CTest)

if(BUILD_TESTING)
    find_package(GTest CONFIG REQUIRED)

    add_executable(tests
        tests/queue_test.cpp
        tests/node_test.cpp
    )

    target_link_libraries(tests PRIVATE assignment GTest::gtest_main)

    include(GoogleTest)
    gtest_discover_tests(tests)
endif()
~~~

Do not copy this example unchanged. Remove src/node.cpp or
tests/node_test.cpp if they do not exist, and add the files your assignment
actually uses.

Prefer explicit source lists such as the examples above. They make the
project's structure visible and prevent an accidentally added file from
silently changing the build.

### 6. Update dependencies only when necessary

The current [vcpkg.json](../../vcpkg.json) declares GoogleTest:

~~~json
{
  "name": "mean-median-demo",
  "version-string": "1.0.0",
  "dependencies": [
    "gtest"
  ]
}
~~~

Keep gtest if the tests use GoogleTest. Add another package only when the
assignment genuinely needs it, and update find_package and
target_link_libraries in CMakeLists.txt to match that package's CMake
targets.

If you do not use an external package, remove unused dependencies from
vcpkg.json. Do not add a dependency merely because it is convenient during
development; every dependency increases setup time and maintenance.

The default [CMakePresets.json](../../CMakePresets.json) uses the VCPKG_ROOT
environment variable, configures a Debug build, enables testing, and writes
generated files to build/. Usually you do not need to change it when replacing
assignment code.
Change it only when the assignment needs different build options, a different
minimum CMake version, or a different toolchain arrangement.

## Configure, build, and test the adapted project

After changing the code, configure from the repository root:

~~~bash
cmake --preset default
~~~

Build every target:

~~~bash
cmake --build --preset default
~~~

Run the tests through CTest:

~~~bash
ctest --preset default
~~~

Run the same sequence after a clean configuration, not only after incremental
builds. If you renamed or removed targets and CMake appears to retain an old
target, remove this project's generated build/ directory and run the
configure command again. Do not commit the generated build directory.

Confirm all of the following before handing the repository to students:

- The project configures from a fresh checkout.
- Every source file needed by the assignment appears in a CMake target.
- Every target has the include directories and libraries it needs.
- The executable, if any, runs using the documented command.
- CTest discovers the intended test cases.
- At least one test fails when you intentionally introduce a known incorrect
  result.
- The student build guide contains commands that match the adapted project.

## Common CMake adaptation problems

### A header cannot be found

Check that the target has the correct include directory:

~~~cmake
target_include_directories(assignment PUBLIC include)
~~~

Also check the include spelling and capitalization. A path that works on one
file system may fail on another if the case does not match.

### The linker reports an undefined reference

The implementation file may not be listed in the library or executable target.
Add it explicitly:

~~~cmake
add_library(assignment
    src/queue.cpp
)
~~~

If the symbol is in another library target, link that target to the consumer
with target_link_libraries.

### The test executable builds but CTest finds no tests

Check that:

- include(CTest) appears before the if(BUILD_TESTING) block.
- BUILD_TESTING is enabled by the active preset.
- GoogleTest is found with find_package(GTest CONFIG REQUIRED).
- The test executable links to GTest::gtest_main.
- include(GoogleTest) and gtest_discover_tests(tests) are present.

### CMake cannot find GoogleTest

Check that GoogleTest is listed in vcpkg.json, VCPKG_ROOT points to a working
vcpkg installation, and the configure command uses the supplied default
preset. If you changed dependencies, reconfigure so vcpkg can install the
updated manifest.

### Old files still appear in the build

Reconfigure first. If the project structure or target names changed, remove
only this project's generated build/ directory and configure again. Do not
remove source files or modify the repository history to solve a stale build
directory.

## Final adaptation checklist

Before distributing an adapted copy, review:

- [ ] STUDENT_README.md describes the actual assignment.
- [ ] The include/, src/, and tests/ files match that description.
- [ ] CMakeLists.txt contains no sample target names or sample file paths.
- [ ] Every source file is listed in the correct target.
- [ ] Public headers are reachable through the target include directories.
- [ ] Test targets link to the code they test.
- [ ] Test discovery registers the intended test cases.
- [ ] vcpkg.json contains only required dependencies.
- [ ] CMakePresets.json still matches the documented local build.
- [ ] A clean configure, build, and test run succeeds.
- [ ] The student setup guide has been updated for any changed tools or
      commands.
- [ ] No placeholder assignment names, sample output, or stale file paths
      remain in the files students will receive.
