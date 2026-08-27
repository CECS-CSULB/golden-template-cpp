# Guidance for Faculty

This template contains a C++ program shell using CMake and Google Test (GTest). It integrates with GitHub Actions so that every push to GitHub triggers a compile + test CI cycle. It can be used with Classroom 50 as the basis for an auto-graded programming assignment, or given to students to fork by hand if you don't care for auto-grading. 

The [docs/faculty](docs/faculty/README.md) folder contains documentation on using this template. It will guide you on setting up your starter code, writing test cases, and optionally configuring a Classroom 50 instance. Before publishing your assignment to GitHub, we recommend **removing** the `docs/faculty` folder to not confuse students with the instructions therein, and similarly removing this section of the README file.

## Faculty To-Do

1. Edit [STUDENT_README.md](STUDENT_README.md) with assignment-specific instructions.
2. Edit [docs/student/setup.md](docs/student/setup.md) with project setup instructions: installing compilers, build managers, libraries, etc. if needed.
3. Review the Warning below and decide about remove the student publishing.md file. 
4. Go through the documentation at [docs/faculty](docs/faculty/README.md) to understand the assignment organization, CI commands, and optional integration with Classroom 50.
5. Create a template repository on GitHub for your assignment to live at, if you haven't already.
6. If you allow AI assistance on the assignment, copy or adapt the faculty
   [Verification Log template](docs/faculty/VERIFICATION-LOG.md) into the
   assignment root. Otherwise, remove any assignment-specific verification-log
   requirement.
7. Remove Faculty documentation to not confuse students.
8. Commit and push changes to GitHub.

## Language-specific notes

This template uses [CMake](https://cmake.org) for build configuration and [vcpkg](https://vcpkg.io) for dependency management. A single dependency, [GTest](https://github.com/google/googletest), is installed by default.

CMake settings:

* The assignment "business" logic is in `src/statistics.cpp`, and that file is compiled into a static library called `statistics`. ([CMakeLists.txt line 10](CMakeLists.txt#L10))
* The assignment "presentation" logic is in `src/main.cpp`, and that file is compiled into an application executable called `mean_median`. ([line 16](CMakeLists.txt#L16))
* The `mean_median` executable automatically links with the `statistics` library ([line 19](CMakeLists.txt#L19)).
* The `/include` directory is on to the compiler's #include path, and header files are expected there. ([line 13](CMakeLists.txt#L13))
* A second executable `tests` compiles `tests/statistics_test.cpp` ([line 27](CMakeLists.txt#L27)), and links to both the `statistics` library and `GTest` ([line 30](CMakeLists.txt#L30)). This executable runs the test cases defined in `tests` and prints the results to standard output.

Source files are expected in `/src`. CMake requires manually adding source files to the build configuration ([CMakeLists.txt line 10](CMakeLists.txt)).

## Warning about student documentation

The file [docs/student/publishing.md](docs/student/publishing.md) walks students through publishing a copy of their completed assignment to their public GitHub profile, to help them build a portfolio of well-documented work during their time in the program. They are advised to only do this with permission, and only after the semester is over, to avoid accusations of plagiarism. 

If you prefer they not do this, please edit the publishing.md file and replace its content with your wishes that the student not publish their completed assignment. You should advise them instead on how to best describe the work they completed, for example as part of their résumé. 

# Guidance for Students

This assignment is derived from the CSULB CECS Department Golden Template, a starting point for faculty to create more authentic programming assignments, following industry-standard practices for source code and test case organization. 

Assignment-specific information can be found in the [STUDENT_README.md](STUDENT_README.md) file. You should read it first before proceeding. If you need help with compilers, Git, GitHub, or publishing your work to a public portfolio, please consult our documentation in [docs/student](docs/student/README.md).
