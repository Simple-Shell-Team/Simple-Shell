# Final Test Case Inventory

This inventory documents the test assets used by the final implementation
after Sprint 1, Sprint 2, and Sprint 3. The authoritative executable tests
remain in `tests/test_parser.c`, `tests/test_executor.c`, and
`tests/test_cases.sh`.

## Parser unit tests

`tests/test_parser.c` contains 12 checks for:

1. Simple command parsing
2. Argument preservation
3. Quoted arguments
4. Two-command pipelines
5. Pipeline command order
6. Input redirection
7. Append redirection
8. Background markers
9. Environment-variable expansion
10. Empty input
11. Missing pipeline command
12. Redirection without a filename

## Executor unit tests

`tests/test_executor.c` contains 9 checks for:

1. Successful command execution
2. Nonzero exit status
3. External exit-status propagation
4. Missing-command status 127
5. Two-command pipeline execution
6. Final pipeline status
7. Final pipeline failure propagation
8. File-descriptor cleanup after repeated execution
9. Redirection and pipeline descriptor handling

## Integration and regression tests

`tests/test_cases.sh` contains 40 requirement-labelled checks covering:

- REQ-1 through REQ-20 functional behavior
- Parser whitespace, quoting, operators, and malformed input
- Built-ins, PATH lookup, and environment expansion
- Input and argument limits
- `<`, `>`, and `>>` redirection
- Two- and three-stage pipelines
- Background execution, timing, lifecycle, and `jobs`
- Missing commands and status handling
- Redirection path validation and symbolic-link protection
- Privilege identity and environment exposure checks

The script prints the requirement coverage table and pass/fail total. Run the
complete test baseline with:

```text
make clean
make test
```

Expected results for the current Linux baseline are 12 parser checks, 9
executor checks, and 40 integration checks passed. Test gaps and intentionally
unsupported requirements are documented in
[`rtm_code_references.md`](rtm_code_references.md).
