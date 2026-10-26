# Requirements Traceability Map

This matrix maps requirements from `docs/Simple-Shell_SRS_v1.2.docx`
to implementation references and automated tests.

**Status definitions**
- **Implemented**: implementation evidence has been identified.
- **Not implemented**: the feature is not currently implemented.
- **Coverage incomplete**: the available tests do not verify every aspect of the requirement.

| REQ-ID | Requirement summary | Source files and functions | Test references | Implementation status |
| --- | --- | --- | --- | --- |
| REQ-1 | Display a prompt and read input within 100 ms of the previous command completing | `src/main.c`: `main` | No dedicated timing test | Implemented; coverage incomplete |
| REQ-2 | Continue accepting commands until `exit` or EOF (Ctrl+D) | `src/main.c`: `main` | TC-01 exercises `exit`; no dedicated EOF-loop test identified | Implemented; coverage incomplete |
| REQ-3 | Support `cd`, `exit`, `pwd`, `echo`, and `help` as built-ins in the shell process | `src/builtins.c`: `is_builtin`, `run_builtin`; `src/executor.c`: `execute_commands` | TC-04, TC-05, TC-06, TC-08 | Implemented |
| REQ-4 | On invalid or inaccessible `cd`, print a single-line error and remain in the current directory | `src/builtins.c`: `run_builtin` | TC-06; directory preservation is not explicitly asserted | Implemented; coverage incomplete |
| REQ-5 | Split input into a command and arguments while handling consecutive whitespace | `src/parser.c`: `parse_line`, `parse_word` | TC-11 | Implemented |
| REQ-6 | Treat single- or double-quoted text, including embedded spaces, as one argument | `src/parser.c`: `parse_word` | TC-29 | Implemented |
| REQ-7 | Recognize `<`, `>`, `>>`, `|`, and `&` as structural operators | `src/parser.c`: `parse_line` | TC-12 | Implemented |
| REQ-8 | Handle empty and whitespace-only input without error | `src/main.c`: `main`; `src/parser.c`: `parse_line` | TC-13 | Implemented |
| REQ-9 | Execute external commands using `fork()` and an `exec()` family call | `src/executor.c`: `execute_command`, `execute_pipeline`, `exec_command` | TC-01, TC-03, TC-29, TC-30, TC-31 | Implemented |
| REQ-10 | Resolve a bare command name using `PATH` | `src/environment.c`: `resolve_executable_path`; `src/executor.c`: `exec_command` | TC-01, TC-32 | Implemented |
| REQ-11 | Wait for foreground children unless the command runs in the background | `src/executor.c`: `execute_command`, `execute_pipeline` | TC-09; TC-17 also exercises pipelines | Implemented |
| REQ-12 | For missing or non-executable commands, print a single-line error within one second and return to the prompt without crashing | `src/executor.c`: `exec_command` | TC-02 checks error output; TC-34 checks status 127 at EOF | Implemented; timing and non-executable-path coverage incomplete |
| REQ-13 | Redirect standard input from a file using `< filename` | `src/redirection.c`: `apply_redirection` | TC-14, TC-16, TC-19 | Implemented |
| REQ-14 | Redirect standard output to a file, overwriting its contents, using `> filename` | `src/redirection.c`: `apply_redirection` | TC-12, TC-19 | Implemented |
| REQ-15 | Redirect standard output to a file, appending using `>> filename` | `src/redirection.c`: `apply_redirection` | TC-15, TC-16 | Implemented |
| REQ-16 | Chain two or more commands with `|` | `src/executor.c`: `execute_pipeline` | TC-17, TC-18, TC-19, TC-20 | Implemented |
| REQ-17 | Close unused pipe file descriptors in parent and child processes after descriptor duplication | `src/executor.c`: `execute_pipeline`, `close_pipes` | TC-17, TC-19 | Implemented |
| REQ-18 | Run a command ending in `&` without waiting and return to the prompt within 100 ms | `src/executor.c`: `run_in_background`, `execute_pipeline` | TC-21, TC-22, TC-23 | Implemented |
| REQ-19 | Maintain background job IDs and process IDs for the current session, viewable on request | `src/executor.c`: `JobList`, `reap_finished_jobs`, `shell_job_list`; `src/builtins.c`: `jobs` built-in | TC-24, TC-33 | Implemented |
| REQ-20 | Make environment variables available to child processes and support reading variables such as `PATH` and `HOME` | `src/environment.c`: `shell_getenv`, `resolve_executable_path`; `src/parser.c`: `expand_variable`; `src/builtins.c`: `run_builtin` | TC-07 | Implemented |
| REQ-21 | (Should) Maintain a history of at least the last 50 commands in the current session | No implementation identified | No test identified | Not implemented |
| REQ-22 | (Should) Handle SIGINT (Ctrl+C) by returning to a fresh prompt instead of terminating the shell | No implementation identified | No test identified | Not implemented |
| REQ-23 | (Should) Handle SIGTSTP (Ctrl+Z) by suspending the current foreground job, if one is running | No implementation identified | No test identified | Not implemented |
| REQ-SEC-1 | Run commands with the invoking shell's user/group privileges; do not elevate privileges | `src/executor.c`: fork/exec paths; no `setuid`/`setgid` calls identified in reviewed code | TC-10 checks user and UID identity | Implementation evidence identified; TC-10 is a limited check, not a comprehensive security audit |
| REQ-SEC-2 | Validate and canonicalize redirection paths before `open()`, rejecting disallowed parent traversal | `src/redirection.c`: `has_parent_component`, `canonical_redirection_input`, `canonical_redirection_output`, `apply_redirection` | TC-25, TC-26 | Implemented; coverage limited to tested paths |
| REQ-SEC-3 | Do not print or log environment values unless explicitly requested | `src/environment.c`: `shell_getenv`; `src/parser.c`: `expand_variable` | TC-27 | Implemented; coverage limited to TC-27 |
| REQ-SEC-4 | Limit input line length and argument count, rejecting excessive input with an error | `src/limits.h`; `src/main.c`: bounded input; `src/parser.c`: argument-count check | TC-28; TC-32 tests a long supported line | Implemented; boundary and argument-count coverage incomplete |

## Coverage notes

- TC-01, TC-02, TC-03, TC-10, and TC-34 mappings in `tests/test_cases.sh`
  should remain consistent with this matrix.
- REQ-1 and REQ-2 do not currently have dedicated automated tests that fully
  verify their requirements.
- REQ-21 through REQ-23 remain unimplemented requirements.
- The README documents further limitations: `2>` and `&&` are unsupported,
  `&` is supported only at the end of a command line, and `fg`/`bg` job-control
  commands are not available.
- A passing test demonstrates only the behavior asserted by that test; it does
  not establish complete compliance with the full requirement.
