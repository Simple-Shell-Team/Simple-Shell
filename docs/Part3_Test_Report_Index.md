# Part-3 Testing Report Index

## Authoritative execution baseline

The current Part-3 automated baseline is the 5 November 2026 Linux/WSL2
execution documented in the Test Plan:

| Suite | Passed | Failed |
|---|---:|---:|
| Parser unit tests | 12 | 0 |
| Executor unit tests | 9 | 0 |
| Integration/regression tests | 40 | 0 |
| **Combined total** | **61** | **0** |

The baseline was rebuilt and executed with:

```text
make clean
make test
```

The executable test sources are `tests/test_parser.c`,
`tests/test_executor.c`, and `tests/test_cases.sh`. The current test inventory
is listed in [`test_case_inventory.md`](test_case_inventory.md).

## Report index

| Report | Purpose |
|---|---|
| [`Unit_Test_Report.md`](Unit_Test_Report.md) | Parser and executor unit-test results: 21 passed, 0 failed. |
| [`System_Validation_Report.md`](System_Validation_Report.md) | Integration/regression and combined validation results: 61 passed, 0 failed. |
| [`Code_Coverage_Report.md`](Code_Coverage_Report.md) | Line/function coverage data from the recorded coverage runs. |
| [`Branch_Coverage_Report.md`](Branch_Coverage_Report.md) | Branch coverage data and branch-analysis limitations. |
| [`Simple-Shell_Test_Plan.docx`](Simple-Shell_Test_Plan.docx) | Approved test strategy, current Part-3 execution section, and evidence references. |
| [`rtm_code_references.md`](rtm_code_references.md) | Requirement-to-source and requirement-to-test traceability. |
| [`test_evidence.md`](test_evidence.md) | Final evidence checklist and documented verification gaps. |

## Interpreting coverage reports

The coverage reports contain historical sections retained for traceability.
Coverage percentages must be read with their stated operating system, tool,
compiler, source scope, and execution command. They are not interchangeable
with the 61-test execution total, and the project does not claim complete
coverage merely because all recorded tests passed.

The authoritative functional result is the 12/9/40/61 baseline above. The
coverage reports provide supplementary line, function, and branch evidence
for their respective runs.

## Known gaps

- REQ-1 and REQ-2 do not have dedicated test IDs in the current regression
  script, so complete verification cannot be claimed from that run alone.
- REQ-21 command history, REQ-22 SIGINT handling, and REQ-23 SIGTSTP handling
  remain unimplemented.
- The shell does not support `2>`, `&&`, `fg`, or `bg`.
- Background timing and lifecycle checks can vary with operating-system
  scheduling.
- Manual screenshot evidence requires separate capture and review.
