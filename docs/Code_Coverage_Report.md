# Code Coverage Report

**Issue:** #40 – Generate Code Coverage Report
**Final measurement date:** November 6, 2026
**Coverage tool:** LLVM Source-Based Code Coverage

## 1. Objective

This report measures line, function, branch, and region coverage for the Simple Shell implementation. It identifies executed and unexecuted source code, investigates coverage gaps, and documents defensive paths and instrumentation limitations.

Coverage percentages represent measured execution data. They do not establish the absence of defects or prove complete compliance with the requirements specification.

## 2. Test Environment

| Component | Configuration |
|---|---|
| Operating system | macOS |
| Architecture | ARM64 (Apple Silicon) |
| Compiler | Apple Clang 17.0.0 |
| Compiler target | `arm64-apple-darwin27.0.0` |
| macOS SDK | `MacOSX26.0.sdk` |
| Coverage instrumentation | LLVM source-based coverage |
| Profile merger | `llvm-profdata` |
| Coverage reporter | `llvm-cov` |
| Optimization level | `-O0` |
| Debug information | `-g` |

The compiler and SDK were selected from the active Xcode installation. The initial build encountered a linker error caused by an SDK and linker mismatch. Explicitly selecting Xcode's Clang compiler and macOS SDK 26.0 resolved the issue.

## 3. Coverage Instrumentation

The project was compiled with LLVM source-based coverage instrumentation using the following flags:

- `-std=c99`
- `-Wall -Wextra -Wpedantic`
- `-D_POSIX_C_SOURCE=200809L`
- `-MMD -MP`
- `-O0 -g`
- `-fprofile-instr-generate`
- `-fcoverage-mapping`

### 3.1 Instrumented Build

The following commands were used for the instrumented standard test run:

```bash
export SDKROOT="$(xcrun --sdk macosx --show-sdk-path)"
export CC="$(xcrun --find clang)"
export LLVM_PROFILE_FILE="$PWD/coverage-final-%p.profraw"

make clean

make CFLAGS="-std=c99 -Wall -Wextra -Wpedantic -D_POSIX_C_SOURCE=200809L -MMD -MP -O0 -g -fprofile-instr-generate -fcoverage-mapping" test
```

### 3.2 Profile Merging

The final November 6 measurement used 48 LLVM raw profile files generated during the official test suite, supplementary harness runs, and exploratory input validation. The consolidated profile was produced using:

```bash
find . -maxdepth 1 -type f -name 'coverage-final-*.profraw' -print0 | \
  xargs -0 xcrun llvm-profdata merge -sparse -o coverage-final.profdata
```

### 3.3 Coverage Generation

Coverage statistics were generated with `xcrun llvm-cov report` using the instrumented shell, unit-test executables, and supplementary harness executables. Test source files and temporary harness source files were excluded from the source-code totals. Execution data from the supplementary harnesses was retained for the production source files.

The final report command was:

```bash
xcrun llvm-cov report \
  ./myshell \
  -object ./tests/test_parser \
  -object ./tests/test_executor \
  -object /tmp/test_environment_coverage \
  -object /tmp/test_redirection_coverage \
  -object /tmp/test_redirection_edges \
  -object /tmp/test_executor_coverage \
  -object /tmp/test_executor_format_coverage \
  -instr-profile=coverage-final.profdata \
  -ignore-filename-regex='(^|/)(tests/|tmp/test_.*\.c$)'
```

## 4. Standard Automated Test Results

The official `make test` suite produced the following results:

| Test category | Passed | Failed |
|---|---:|---:|
| Parser unit tests | 12 | 0 |
| Executor unit tests | 9 | 0 |
| Regression tests | 40 | 0 |
| **Official test suite total** | **61** | **0** |

All 61 standard automated test checks passed. The test execution included parser functionality, command execution, pipelines, redirection, background jobs, environment handling, and security-related regression cases.

The standard test command was:

```bash
make clean
make test
```

## 5. Supplementary Coverage Tests

Five additional temporary test harnesses were used to exercise production code paths that were not adequately captured by the standard test suite.

| Supplementary test area | Passed | Failed |
|---|---:|---:|
| Environment resolver | 8 | 0 |
| Redirection behavior | 10 | 0 |
| Redirection edge cases | 3 | 0 |
| Executor behavior and job management | 19 | 0 |
| Background command formatting | 5 | 0 |
| **Supplementary harness total** | **45** | **0** |

The supplementary checks exercised:

- Environment-variable lookup and executable-path resolution.
- Missing commands, missing `PATH`, and empty `PATH` entries.
- Input and output redirection.
- Append mode and relative output paths.
- Empty paths, missing files, and parent-traversal rejection.
- Symbolic-link output rejection.
- Foreground pipelines and background job execution.
- Job registration, completion, reaping, and cleanup.
- Background command-line formatting.

The supplementary harnesses were temporary files under `/tmp`. They were not part of the official `make test` target and are not included in the repository's standard test count. Therefore, the official automated test baseline remains 61 checks, while the coverage measurements include the additional supplementary execution data.

An additional exploratory input-validation run exercised invalid built-in arguments, invalid variable names, expansion errors, argument limits, and exit-status validation. These exploratory checks were not included in either formal test total.

One temporary redirection harness emitted an unused-variable compiler warning. This warning was in the temporary harness, not in the production source files; all ten checks in that harness passed.

## 6. Overall Source Coverage

The final consolidated November 6 profile was `coverage-final.profdata`.

The measured source-only coverage was:

| Coverage metric | Covered | Total | Coverage |
|---|---:|---:|---:|
| Lines | 929 | 1,173 | 79.20% |
| Functions | 37 | 40 | 92.50% |
| Branches | 504 | 708 | 71.19% |
| Regions | 1,151 | 1,468 | 78.41% |

The source-only totals exclude test source files and temporary harness source files. Execution data from the supplementary harnesses is retained for the production source files. `limits.h` contains no executable lines or functions in this measurement.

## 7. Coverage by Source File

| Source file | Regions | Region coverage | Functions | Function coverage | Lines | Line coverage | Branches | Branch coverage |
|---|---:|---:|---:|---:|---:|---:|---:|---:|
| `builtins.c` | 182 | 93.96% | 4/4 | 100.00% | 148 | 96.62% | 114 | 83.33% |
| `environment.c` | 71 | 95.77% | 2/2 | 100.00% | 48 | 97.92% | 24 | 87.50% |
| `executor.c` | 484 | 66.94% | 16/19 | 84.21% | 448 | 65.40% | 256 | 56.25% |
| `main.c` | 61 | 83.61% | 1/1 | 100.00% | 59 | 93.22% | 38 | 65.79% |
| `parser.c` | 519 | 77.26% | 10/10 | 100.00% | 341 | 82.99% | 220 | 77.27% |
| `redirection.c` | 151 | 90.07% | 4/4 | 100.00% | 129 | 83.72% | 56 | 87.50% |
| **TOTAL** | **1,468** | **78.41%** | **37/40** | **92.50%** | **1,173** | **79.20%** | **708** | **71.19%** |

## 8. Analysis of Uncovered Code

### 8.1 Executor

The executor has the largest remaining coverage gap:

- Line coverage: 65.40%.
- Function coverage: 84.21%.
- Branch coverage: 56.25%.

The `exec_command()` function is invoked in forked child processes. Its built-in execution path terminates using `_exit()`, while successful external command execution replaces the process using `execv()`. These paths do not reliably execute LLVM's normal profile-writing mechanism in the child process. Consequently, counters from some child-side execution paths may be absent from the consolidated profile.

Direct executor harnesses exercised parent-side behavior, including foreground pipelines, background job registration, job completion, reaping, command formatting, and job-list cleanup.

Remaining uncovered executor paths include child-side command execution and defensive error handling. The measured executor percentage should therefore be interpreted in light of this profiling limitation.

### 8.2 Parser

The parser has 82.99% line coverage and 100% function coverage.

Supplementary inputs exercised malformed variable expansions, invalid variable names, whitespace handling, and the maximum argument-count check.

Remaining uncovered paths include allocation failures during token-list growth, string expansion, command allocation, and argument allocation. These allocation failures were not artificially induced.

### 8.3 Redirection

The redirection module has 83.72% line coverage and 100% function coverage.

Supplementary tests exercised:

- Valid input and output redirection.
- Append mode.
- Empty paths.
- Parent-directory traversal rejection.
- Missing input files and output directories.
- Relative output paths.
- Symbolic-link output rejection.
- Unreadable input files.

Remaining uncovered paths primarily concern allocation failures and failures from descriptor operations such as `dup2()`.

### 8.4 Built-ins

The built-ins module has 96.62% line coverage and 100% function coverage.

Supplementary inputs exercised invalid arguments to `pwd`, `help`, `export`, `unset`, and `exit`, as well as invalid variable names and unset variables.

Remaining paths include environment-setting failures and other exceptional error conditions that were not induced during this run.

### 8.5 Environment

The environment module has 97.92% line coverage and 100% function coverage.

A dedicated direct harness exercised executable-path resolution, missing commands, missing `PATH`, empty `PATH` entries, and environment-variable lookup.

One remaining uncovered line corresponds to an allocation-failure path.

### 8.6 Main Loop

The main loop has 93.22% line coverage and 100% function coverage.

The remaining uncovered prompt and EOF-related lines are associated with interactive-terminal behavior. Most automated regression tests provide input through pipes, so they do not exercise all interactive prompt paths.

## 9. Limitations and Deviations

1. Coverage was measured on macOS ARM64 using Apple Clang and LLVM coverage tools. These percentages are not Linux coverage measurements.
2. The Linux CI workflow validates the standard build and test suite. It does not provide source-based coverage percentages.
3. LLVM profile data from child processes that terminate using `_exit()` or are replaced by `execv()` may not be written through the normal profile runtime. This particularly affects measurement of executor child-side code.
4. Allocation failures, process-creation failures, and descriptor-operation failures were not systematically induced through fault injection. Their uncovered paths are documented rather than claimed as tested.
5. Supplementary harness source files were kept under `/tmp` during this investigation. They are not part of the repository's official test target. Reproducing the supplementary aggregate requires retaining or recreating those harnesses.
6. Coverage percentages depend on the executed test inputs and instrumentation environment. They should not be interpreted as proof that every requirement or error condition is fully verified.

No unsupported 100% coverage claim is made.

## 10. CI Supporting Evidence

The GitHub Actions Build and Test workflow for PR #30 completed successfully on Ubuntu Linux.

- Pull request: #30 – Strengthen parser and background-job regression review.
- Workflow run: Build and Test.
- Tested commit: `f93edbd48854092d83e5d7d175c78daeae929a2e`.
- Result: Success.
- Parser unit tests: 12 passed.
- Executor unit tests: 9 passed.
- Shell regression tests: 40 passed.

This is supporting Linux build and regression-test evidence for PR #30. It is not a Linux coverage measurement and was not run against the Issue #40 report commit. A CI run for the Issue #40 pull request should be used as the final validation of the submitted branch.

## 11. Conclusion

The final consolidated macOS coverage measurement for the Simple Shell implementation is:

- 79.20% line coverage.
- 92.50% function coverage.
- 71.19% branch coverage.
- 78.41% region coverage.

All 61 standard automated checks passed. An additional 45 supplementary coverage checks also passed.

The largest remaining coverage gap is in the executor, where child-process termination behavior limits the availability of LLVM profile counters. Other remaining uncovered paths are primarily defensive, allocation-failure, or interactive-terminal cases.

These limitations are explicitly documented. The measured results provide a quantitative view of the exercised implementation without claiming complete coverage.

## Appendix A. Earlier Ubuntu WSL2 Baseline (November 4, 2026)

The repository's previously merged coverage reports recorded an earlier GCC/gcovr measurement from November 4, 2026. That measurement is retained here as historical evidence. It is separate from, and should not be treated as directly comparable to, the expanded November 6 LLVM measurement in Sections 2–11.

### A.1 Environment and scope

| Component | Earlier baseline configuration |
|---|---|
| Operating system | Ubuntu 26.04 LTS |
| Environment | WSL2 |
| Architecture | x86_64 |
| Compiler | GCC 15.2.0 |
| Coverage tool | gcovr 7.2 |
| Instrumentation | GCC `--coverage` |
| Measurement date | November 4, 2026 |
| Test scope | Parser and executor unit tests only (21 tests) |

The earlier run executed 12 parser unit tests and 9 executor unit tests. It did not include the 40 integration/regression tests or the five supplementary harnesses used in the November 6 measurement. The earlier line-coverage report filtered the `src` directory with:

```bash
gcovr --root . --filter 'src/.*\.c'
```

### A.2 Earlier line coverage

| Source file | Total lines | Executed lines | Reported line coverage |
|---|---:|---:|---:|
| `src/builtins.c` | 110 | 20 | 18% |
| `src/environment.c` | 35 | 2 | 5% |
| `src/executor.c` | 333 | 72 | 21% |
| `src/parser.c` | 269 | 188 | 69% |
| `src/redirection.c` | 95 | 44 | 46% |
| **Total** | **842** | **326** | **38%** |

### A.3 Earlier branch coverage

| Source file | Total branches | Branches taken | Reported branch coverage |
|---|---:|---:|---:|
| `src/builtins.c` | 114 | 18 | 15% |
| `src/environment.c` | 22 | 0 | 0% |
| `src/executor.c` | 252 | 50 | 19% |
| `src/parser.c` | 220 | 139 | 63% |
| `src/redirection.c` | 56 | 22 | 39% |
| **Total** | **664** | **229** | **34%** |

### A.4 Interpretation

The November 4 result was a unit-test-only baseline. The November 6 result in this report used a different operating system, compiler, coverage tool, set of instrumented executables, and broader execution set: all 61 official checks plus 45 supplementary checks. The November 6 report also includes `main.c` and reports function and region coverage.

Because the measurement environments and scopes differ, the 38% historical line-coverage result and the 79.20% November 6 line-coverage result are not a like-for-like before-and-after comparison. The November 6 LLVM figures are the final expanded measurements for this Issue #40 report; the November 4 GCC/gcovr figures are preserved for traceability to the previously merged Sprint 3 QA documentation.
