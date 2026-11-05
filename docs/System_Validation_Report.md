# System Validation Report

## 1. Overview

This report documents system-level validation of the Simple-Shell project for the Software Engineering Mini-Project Part-3 deliverables.

Execution Date: 5 November 2026

## 2. Test Environment

| Item | Details |
|---|---|
| Operating System | Ubuntu 26.04 LTS |
| Environment | WSL2 |
| Architecture | x86_64 |
| Build Tool | GNU Make |
| Compiler | GCC 15.2.0 |
| Regression Test Script | tests/test_cases.sh |

## 3. Validation Procedure

The project was cleaned, rebuilt, and tested using the command make clean && make test.

The build completed successfully and generated the shell executable and unit-test executables.

## 4. Test Execution Summary

| Test Suite | Total | Passed | Failed |
|---|---:|---:|---:|
| Parser Unit Tests | 12 | 12 | 0 |
| Executor Unit Tests | 9 | 9 | 0 |
| Integration/Regression Tests | 40 | 40 | 0 |
| Overall | 61 | 61 | 0 |

## 5. System Validation Coverage

The executed regression tests covered:

- External command execution and PATH lookup.
- Built-in commands and environment variables.
- Input and output redirection.
- Multi-stage pipelines.
- Background execution and job tracking.
- Quoted arguments and whitespace handling.
- Empty input and malformed command handling.
- Command-not-found and nonzero exit statuses.
- Path traversal and symbolic-link redirection checks.
- Long input handling and recovery.

## 6. Validation Results

The parser unit-test suite completed with 12 passing tests and zero failures.

The executor unit-test suite completed with 9 passing tests and zero failures.

The integration/regression suite completed with 40 passing tests and zero failures.

The complete automated test execution recorded 61 passing tests and zero reported failures.

The missing-command diagnostic during executor testing was expected and formed part of the missing-command test case.

## 7. Evidence Sources

| Evidence | Location |
|---|---|
| Parser unit tests | tests/test_parser.c |
| Executor unit tests | tests/test_executor.c |
| Integration/regression tests | tests/test_cases.sh |
| Test execution record | docs/Simple-Shell_Test_Plan.docx |
| Unit test results | docs/Unit_Test_Report.md |
| Line and branch coverage | docs/Branch_Coverage_Report.md |
| Requirements traceability | docs/rtm_code_references.md |
| Manual test evidence checklist | docs/test_evidence.md |

## 8. Known Limitations and Verification Gaps

- REQ-1 and REQ-2 have no dedicated test IDs in the current regression script. Complete verification cannot be claimed from this run alone.
- REQ-21 command history, REQ-22 SIGINT handling, and REQ-23 SIGTSTP handling remain unimplemented according to the existing Test Plan.
- The shell does not support 2>, &&, fg, or bg.
- Background timing and lifecycle tests may depend on operating-system scheduling.
- Manual screenshot evidence remains subject to separate capture and review.
- Automated test results do not establish that every system requirement has been fully verified.

## 9. Conclusion

The Simple-Shell project successfully built and completed the recorded automated validation run on 5 November 2026.

A total of 61 automated tests passed, comprising 21 unit tests and 40 integration/regression tests, with zero reported failures.

The identified requirement gaps and unimplemented features remain documented for further review.

