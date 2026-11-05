# Code Coverage Report

## 1. Overview

This report documents source-code line coverage for the Simple-Shell project as part of the Software Engineering Mini-Project Part-3 testing deliverables.

Coverage Measurement Date: 4 November 2026

## 2. Test Environment

| Item | Details |
|---|---|
| Operating System | Ubuntu 26.04 LTS |
| Environment | WSL2 |
| Architecture | x86_64 |
| Compiler | GCC 15.2.0 |
| Coverage Tool | gcovr 7.2 |
| Instrumentation | GCC --coverage |

## 3. Coverage Methodology

The parser and executor unit-test executables were compiled with GCC coverage instrumentation.

The following test suites were executed:

- Parser unit tests: 12 passed, 0 failed.
- Executor unit tests: 9 passed, 0 failed.

Coverage data from both test executables was collected using gcovr.

The measured source files were restricted to the project's src directory.

Line coverage was calculated using:

gcovr --root . --filter 'src/.*\.c'

## 4. Line Coverage Results

| Source File | Total Lines | Executed Lines | Coverage |
|---|---:|---:|---:|
| src/builtins.c | 110 | 20 | 18% |
| src/environment.c | 35 | 2 | 5% |
| src/executor.c | 333 | 72 | 21% |
| src/parser.c | 269 | 188 | 69% |
| src/redirection.c | 95 | 44 | 46% |
| **Total** | **842** | **326** | **38%** |

## 5. Coverage Analysis

The overall measured line coverage was 38%, with 326 of 842 executable lines covered.

Parser achieved the highest line coverage at 69%, followed by redirection at 46%.

Executor achieved 21% coverage, built-ins achieved 18%, and environment handling achieved 5%.

The lower coverage figures indicate that substantial portions of these components were not executed by the measured unit-test suites.

## 6. Coverage Limitations

- Coverage was measured using the parser and executor unit-test suites.
- Integration and regression test execution was not included in this coverage measurement.
- The coverage percentage does not represent the percentage of functional requirements satisfied.
- Unexecuted code paths may contain defects that were not detected by the measured tests.
- Additional tests are recommended for environment handling, built-ins, executor error paths, and exceptional conditions.

## 7. Relationship to Branch Coverage

The separate Branch Coverage Report documents 34% branch coverage, with 229 of 664 branches taken.

Branch coverage measures executed decision outcomes, whereas line coverage measures executed source-code lines.

See docs/Branch_Coverage_Report.md for the detailed branch coverage results.

## 8. Conclusion

The Simple-Shell project achieved 38% line coverage across 842 measured executable lines during the November 4 instrumented unit-test run.

The results establish a reproducible baseline and identify components requiring additional unit-test coverage.
