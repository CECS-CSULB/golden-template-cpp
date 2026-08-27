# [Assignment Title]

<!--
FACULTY: This is the student-facing assignment guide. Replace every
placeholder in square brackets before distributing the repository. Remove any
sections that do not apply to your assignment.
-->

## Overview

<!-- FACULTY: Describe the problem students are solving, why it matters, and
what they are expected to build. Avoid putting grading-only details here. -->

In this assignment, you will [describe the program, library, or system the
student will implement]. The completed program should [summarize the main
result or behavior].

This assignment is intended to help you practice:

- [Learning objective 1]
- [Learning objective 2]
- [Learning objective 3]

## What you need to implement

<!-- FACULTY: List the files, functions, classes, or other artifacts students
are responsible for. Keep names and signatures exact. -->

| File or path | Required work |
|---|---|
| `[path/to/source-file]` | [Function, class, or feature to implement] |
| `[path/to/another-file]` | [Function, class, or feature to implement] |

Do not change [function names, signatures, public interfaces, or other
constraints]. You may create additional helper functions or files if [state
whether this is allowed].

## Requirements

<!-- FACULTY: State functional requirements and important edge cases. Be
specific enough that students can test their work locally. -->

Your solution must:

1. [Requirement 1]
2. [Requirement 2]
3. [Requirement 3]

Important edge cases include:

- [Edge case 1 and expected behavior]
- [Edge case 2 and expected behavior]
- [Edge case 3 and expected behavior]

## Input and output

<!-- FACULTY: Use this section for console programs. For library assignments,
replace it with the API contract and examples. -->

### Input

[Describe the input format, valid values, number of values, and termination
conditions.]

### Output

[Describe the required output, including labels, ordering, precision, and
whether additional output is allowed.]

Example:

```text
[Example input]
```

```text
[Expected output]
```

## Project layout

| Path | Purpose |
|---|---|
| `src/` | Starter and implementation source files |
| `include/` | C++ header files and public interfaces |
| `tests/` | GoogleTest test cases |
| `docs/student/setup.md` | C++ and local build instructions |
| `CMakeLists.txt` | Build and test configuration |

Read [the build guide](docs/student/setup.md) before configuring the project.

## Test cases and grading

Your solution is checked with automated tests. The public test cases are
described below.

<!--
FACULTY: Replace this table with the tests in tests/. List one row per
meaningful test case or test group. Do not claim that a test is public if it is
hidden. If Classroom 50 or another grading system applies different weights,
make the authoritative weights clear in the course assignment instructions.
-->

| Test case | What it checks | Input or setup | Expected behavior | Points |
|---|---|---|---|---:|
| `[TestName1]` | [Behavior being tested] | [Input or setup] | [Expected result] | [N] |
| `[TestName2]` | [Behavior being tested] | [Input or setup] | [Expected result] | [N] |
| `[TestName3]` | [Behavior being tested] | [Input or setup] | [Expected result] | [N] |
| **Total** |  |  |  | **[Total points]** |

The tests may check normal inputs, boundary conditions, invalid inputs, and
whether your implementation preserves required input data. Passing the sample
input alone is not sufficient; your implementation must satisfy the complete
contract above.

<!-- FACULTY: Choose and describe the applicable grading workflow. -->

Tests can be run locally with:

```bash
cmake --preset default
cmake --build --preset default
ctest --preset default
```

Continuous integration runs the build and test suite after you push your work
to GitHub. If this assignment uses Classroom 50, the Classroom 50 assignment
settings determine when a submission is graded and how test results are
weighted.

## Submission checklist

Before submitting, confirm that:

- [ ] Your implementation is complete.
- [ ] The project builds successfully.
- [ ] All local tests pass.
- [ ] Your output follows the required format.
- [ ] You did not commit build artifacts, secrets, or unrelated files.
- [ ] You completed any required course verification or AI-use log.

<!-- FACULTY: Add assignment-specific submission instructions, due dates,
branch/tag requirements, collaboration rules, and AI-use requirements here. -->

## Questions and help

<!-- FACULTY: Add the approved help channels and any collaboration boundaries. -->

For questions, use [the course help channel or forum]. When asking for help,
include the command you ran, the relevant error message, and a minimal example
that reproduces the problem. Do not post private tokens or other sensitive
information.
