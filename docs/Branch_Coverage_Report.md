# Branch Coverage Report

## 1. Overview

This report documents line and branch coverage for the Simple-Shell implementation using GCC coverage instrumentation and gcovr.

## 2. Test Environment

| Item | Details |
|---|---|
| Operating System | Ubuntu 26.04 LTS |
| Environment | Windows Subsystem for Linux 2 (WSL2) |
| Architecture | x86_64 |
| Compiler | GCC 15.2.0 |
| Coverage Tools | gcov, gcovr 7.2 |
| Coverage Run | November 4, 2026 |

## 3. Coverage Method

The unit tests were compiled and executed with GCC coverage instrumentation using the `--coverage` flag.

The following test suites were included:
- Parser unit tests: 12 passed, 0 failed
- Executor unit tests: 9 passed, 0 failed

A total of 21 unit tests passed.

Coverage was generated from the instrumented test executables and summarized with gcovr.

## 4. Line Coverage by Source File

| Source File | Total Lines | Lines Executed | Line Coverage |
|---|---:|---:|---:|
| src/builtins.c | 110 | 20 | 18% |
| src/environment.c | 35 | 2 | 5% |
| src/executor.c | 333 | 72 | 21% |
| src/parser.c | 269 | 188 | 69% |
| src/redirection.c | 95 | 44 | 46% |
| **Total** | **842** | **326** | **38%** |

## 5. Branch Coverage by Source File

| Source File | Total Branches | Branches Taken | Branch Coverage |
|---|---:|---:|---:|
| src/builtins.c | 114 | 18 | 15% |
| src/environment.c | 22 | 0 | 0% |
| src/executor.c | 252 | 50 | 19% |
| src/parser.c | 220 | 139 | 63% |
| src/redirection.c | 56 | 22 | 39% |
| **Total** | **664** | **229** | **34%** |

## 6. Coverage Analysis

The measured unit-test run achieved:
- 38% overall line coverage (326 of 842 lines).
- 34% overall branch coverage (229 of 664 branches).

Parser coverage was the highest among the measured files, with 69% line coverage and 63% branch coverage.

Redirection achieved 46% line coverage and 39% branch coverage. Coverage was lower in executor and built-ins.

Environment handling had 5% line coverage and 0% branch coverage, indicating that additional tests are needed to exercise its decision paths.

## 7. Error-Path and Allocation-Failure Coverage

The unit tests exercise selected error paths, including malformed parser input, missing commands, and nonzero command exit statuses.

However, the current unit-test suite does not comprehensively exercise all defensive and error-handling branches. Allocation-failure paths and other exceptional conditions remain coverage gaps unless specifically triggered by a test.

## 8. Known Gaps and Limitations

- Coverage is based on the current parser and executor unit-test suites; it is not a measure of complete system or integration coverage.
- Environment handling has 0% branch coverage in the measured run.
- Many branches in built-ins, executor, and redirection were not taken.
- Allocation failures and uncommon system-call failures are not comprehensively simulated.
- Coverage percentages indicate which instrumented lines and branches were executed; they do not independently establish correctness of untested behavior.

## 9. Conclusion

The measured unit-test run achieved 38% overall line coverage and 34% overall branch coverage across the five measured source files.

The parser received the strongest coverage, while environment handling and several executor-related components require additional test cases.

This report documents the coverage achieved by the current test suite and identifies areas for future testing improvements.
