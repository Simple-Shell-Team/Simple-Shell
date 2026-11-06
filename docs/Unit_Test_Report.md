# Unit Test Report

## 1. Overview

This report documents the execution of the Simple-Shell parser and executor unit tests for Sprint 3.

## 2. Test Environment

| Item | Details |
|---|---|
| Operating System | Ubuntu 26.04 LTS |
| Environment | Windows Subsystem for Linux 2 (WSL2) |
| Kernel | Linux 6.18.33.1-microsoft-standard-WSL2 |
| Architecture | x86_64 |
| Compiler | GCC 15.2.0 |
| Compiler flags | -std=c99 -Wall -Wextra -Wpedantic -D_POSIX_C_SOURCE=200809L |

## 3. Test Execution

The following commands were executed from the repository root:

- `make clean`
- `make unit-test`

## 4. Parser Unit Tests

| Test | Result |
|---|---|
| Parse a simple command | PASS |
| Preserve command arguments | PASS |
| Preserve a quoted argument | PASS |
| Parse a two-command pipeline | PASS |
| Preserve pipeline command order | PASS |
| Parse input redirection | PASS |
| Parse append redirection | PASS |
| Recognize a background command | PASS |
| Expand an environment variable | PASS |
| Accept empty or whitespace-only input | PASS |
| Reject a pipeline missing its final command | PASS |
| Reject redirection without a filename | PASS |

**Parser summary:** 12 passed, 0 failed.

## 5. Executor Unit Tests

| Test | Result |
|---|---|
| Execute a successful command | PASS |
| Return a nonzero exit status | PASS |
| Propagate an external command exit status | PASS |
| Return 127 for a missing command | PASS |
| Execute a two-command pipeline | PASS |
| Return the final pipeline command status | PASS |
| Propagate failure from the final pipeline command | PASS |
| Repeat pipelines and redirections successfully | PASS |
| Close file descriptors after pipelines and redirections | PASS |

**Executor summary:** 9 passed, 0 failed.

The `command not found` diagnostic emitted during the missing-command test was expected. The test passed by verifying that the shell returned exit status 127.

## 6. Overall Results

| Test Suite | Passed | Failed |
|---|---:|---:|
| Parser | 12 | 0 |
| Executor | 9 | 0 |
| **Total** | **21** | **0** |

## 7. Conclusion

The parser and executor unit test suites completed successfully in the recorded environment. All 21 tests passed, with no test failures reported.

These results apply to the unit tests executed through `make unit-test`. They do not, by themselves, establish complete system validation or branch coverage.
