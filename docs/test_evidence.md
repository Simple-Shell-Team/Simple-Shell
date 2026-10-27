# Test and Demonstration Evidence

This file records the commands and evidence checklist used for the current
implementation. Run the commands from the repository root on a POSIX system.

## Automated test output

Run:

```text
make clean
make test
```

The expected successful run includes:

```text
Parser unit tests: 12 passed, 0 failed
Executor unit tests: 7 passed, 0 failed
34 tests passed
```

The regression suite prints a requirement-coverage table. In particular:

- REQ-6 is covered by TC-29 and TC-34.
- REQ-14 is covered by TC-12 and TC-19.
- REQ-19 is covered by TC-24 and TC-33.

GitHub Actions repeats `make clean && make test` for pushes to `main` and pull
requests. A successful workflow run is the CI evidence for the submitted
source tree.

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
