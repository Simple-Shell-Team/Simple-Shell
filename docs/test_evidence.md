# Test and Demonstration Evidence

This file records the commands and evidence checklist used for the current
implementation. Run the commands from the repository root on a POSIX system.

## Automated test output

Run the following commands from the repository root on a POSIX system:

```text
make clean
make test
```

The current successful local run includes:

```text
Parser unit tests: 12 passed, 0 failed
Executor unit tests: 9 passed, 0 failed
40 tests passed
```

The regression suite prints a requirement-coverage table. In particular:

- REQ-6 is covered by TC-29 and TC-35 for quoted operators and arguments with spaces.
- REQ-14 is covered by TC-12 and TC-19 for output redirection.
- REQ-18 is covered by TC-21, TC-22, and TC-23 for background execution and lifecycle.
- REQ-19 is covered by TC-23, TC-24, and TC-33 for job tracking and PID display.
- REQ-SEC-2 is covered by TC-25, TC-26, TC-36, TC-37, TC-38, and TC-40 for redirection-path validation.

TC-21 measures background-command return time and checks the 100 ms target.
TC-23 checks that a background pipeline is listed as one job with both PIDs,
its command line, a running status, and a completion message.

GitHub Actions is configured to run `make clean && make test` on Ubuntu Linux
for pull requests targeting `main`. After these review changes are pushed,
the successful workflow run for the new pull request should be used as Linux
build and regression-test evidence.

## Limitations and deviations

- REQ-1 and REQ-2 do not currently have dedicated automated tests that fully
  verify their requirements.
- REQ-21 through REQ-23 remain unimplemented requirements.
- `2>` and `&&` are unsupported.
- `&` is supported only at the end of a command line.
- The `fg` and `bg` job-control commands are not available.
- Background timing and lifecycle tests depend on operating-system scheduling;
  the local result should be supplemented by Linux CI validation.
- A passing test demonstrates only the behavior asserted by that test; it does
  not establish complete compliance with the full requirements specification.

## SRS, SAD, and Test Plan deviations

The following deviations and verification gaps were identified during the
requirements traceability review.

| Source document | Deviation or gap | Status |
| --- | --- | --- |
| SRS | REQ-21, REQ-22, and REQ-23 (command history and interactive signal handling) are not implemented. | Documented in the RTM |
| SRS | `2>` and `&&` are unsupported; `&` is supported only at the end of a command line; `fg` and `bg` are unavailable. | Documented scope limitations |
| Test Plan | REQ-1 and REQ-2 do not have dedicated automated tests that fully verify their requirements. | Coverage incomplete |
| Test Plan | REQ-4, REQ-12, and REQ-SEC-4 have specific coverage gaps documented in the RTM. | Coverage incomplete |
| SAD | Architecture-level conformance has not been independently re-audited; no deviation is asserted. | Verification pending |

These entries distinguish implementation limitations from test coverage gaps.
A requirement marked implemented does not imply that every aspect of it
has been tested. See `rtm_code_references.md` for requirement-level details.

## Manual screenshot checklist

Capture the following terminal states after running `./myshell` and attach the
screenshots to the project submission or sprint demonstration:

1. The prompt after an empty line, followed by `pwd`.
2. `echo "quoted argument with spaces"` showing one preserved argument.
3. `echo first > output.txt`, followed by `cat output.txt`.
4. `printf "a\nb\n" | wc -l` showing pipeline output.
5. `sleep 2 &`, followed by `jobs` showing a job ID, PID, command, and status.
6. `export DEMO_VALUE=ready`, followed by `echo $DEMO_VALUE`.

These checks correspond to the implementation and requirement mappings in
[`rtm_code_references.md`](rtm_code_references.md).
