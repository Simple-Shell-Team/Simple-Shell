# Branch Coverage Report

## 1. Overview

This report documents branch coverage for the Simple-Shell implementation using GCC coverage instrumentation and gcovr.

## 2. Test Environment

| Item | Details |
|---|---|
| Operating System | Ubuntu 26.04 LTS |
| Environment | Windows Subsystem for Linux 2 (WSL2) |
| Architecture | x86_64 |
| Compiler | GCC 15.2.0 |
| Coverage Tools | gcov, gcovr 7.2 |

## 3. Coverage Method

The unit tests were compiled and executed with GCC coverage instrumentation using the `--coverage` flag.

The following test suites were included:
- Parser unit tests
- Executor unit tests

Coverage was generated from the instrumented test executables and summarized with gcovr.

## 4. Branch Coverage by Source File

| Source File | Total Branches | Branches Taken | Branch Coverage |
|---|---:|---:|---:|
| src/builtins.c | 114 | 18 | 15% |
| src/environment.c | 22 | 0 | 0% |
| src/executor.c | 252 | 50 | 19% |
| src/parser.c | 220 | 139 | 63% |
| src/redirection.c | 56 | 22 | 39% |
| **Total** | **664** | **229** | **34%** |

## 5. Covered and Missed Branches

Across the measured source files, 229 of 664 branches were taken, corresponding to 34% branch coverage. The remaining 435 branches were not taken during the measured test execution.

Parser coverage was the highest among the measured files at 63%. Coverage was lower in executor, built-ins, redirection, and environment handling.

## 6. Error-Path and Allocation-Failure Coverage

The unit tests exercise selected error paths, including malformed parser input, missing commands, and nonzero command exit statuses.

However, the current unit-test suite does not comprehensively exercise all defensive and error-handling branches. Allocation-failure paths and other exceptional conditions remain coverage gaps unless specifically triggered by a test.

## 7. Known Gaps and Limitations

- Branch coverage is based on the current parser and executor unit tests; it is not a measure of complete system or integration coverage.
- Environment handling has 0% branch coverage in the measured run.
- Many branches in built-ins, executor, and redirection were not taken.
- Allocation failures and uncommon system-call failures are not comprehensively simulated.
- Coverage percentages indicate which instrumented branches were taken; they do not independently establish correctness of untested behavior.

## 8. Conclusion

The measured unit-test run achieved 34% overall branch coverage across 664 branches. The parser received the strongest branch coverage, while environment handling and several executor-related components require additional test cases.

This report documents the coverage achieved by the current test suite and identifies areas for future testing improvements.
