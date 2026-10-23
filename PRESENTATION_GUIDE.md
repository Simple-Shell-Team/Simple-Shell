# Simple-Shell Presentation Guide

This guide explains the work completed so far in the Simple-Shell project and divides the presentation among Aarush, Debhargo, Prithviraj, and Diya.

## 1. Project Overview

Simple-Shell is a Unix-like command-line shell written in C. It provides a smaller version of the core functionality found in shells such as Bash or Dash.

The shell can:

- Display a prompt and accept commands.
- Execute external commands such as `ls`, `cat`, `grep`, and `sleep`.
- Execute built-in commands such as `cd`, `pwd`, `echo`, `help`, `exit`, `export`, `unset`, and `jobs`.
- Parse whitespace, quoted strings, escaped characters, and shell operators.
- Redirect input and output using `<`, `>`, and `>>`.
- Connect commands using pipelines with `|`.
- Run commands in the background using `&`.
- Resolve commands using the `PATH` environment variable.
- Expand environment variables such as `$HOME` and `$PATH`.
- Display clear errors for invalid commands, malformed input, and missing files.
- Enforce input limits and validate redirection paths for security.

The main data flow is:

```text
User input
    |
REPL / main loop
    |
Parser
    |
Command structure
    |
Executor
    |
Built-in command OR fork/exec external command
    |
Redirection / pipe / background job handling
    |
Output or error message
```

## 2. Project Structure

| File | Responsibility |
|---|---|
| [`src/main.c`](src/main.c) | Prompt, input reading, and REPL loop |
| [`src/parser.c`](src/parser.c) | Tokenization, quoting, variables, and operators |
| [`src/builtins.c`](src/builtins.c) | Built-in command implementations |
| [`src/executor.c`](src/executor.c) | External execution, pipelines, waiting, and jobs |
| [`src/redirection.c`](src/redirection.c) | Input/output redirection and path validation |
| [`src/environment.c`](src/environment.c) | Environment variables and `PATH` lookup |
| [`src/limits.h`](src/limits.h) | Input and argument limits |
| [`tests/test_cases.sh`](tests/test_cases.sh) | Automated test harness |
| [`docs/rtm_code_references.md`](docs/rtm_code_references.md) | Requirement traceability map |
| [`Makefile`](Makefile) | Build and test commands |

## 3. How to Explain the SAD

The **Software Architecture and Design Specification (SAD)** explains how the system is designed internally.

### SAD purpose

The SAD describes:

- The architecture of the shell.
- The responsibility of each module.
- How modules communicate.
- How commands, pipes, and redirections are executed.
- How errors are handled.
- How security concerns are addressed.

The difference between the project documents is:

- **SRS:** What the system must do.
- **SAD:** How the system is designed to do it.
- **Test Plan:** How we verify that it works.

### Architecture

The project uses a layered architecture:

1. **REPL layer** — reads input and displays the prompt.
2. **Parser layer** — converts text into a structured `Command`.
3. **Execution layer** — decides whether the command is built-in or external.
4. **Process management layer** — uses `fork()`, `execv()`, and `waitpid()`.
5. **Redirection and pipe layer** — uses `open()`, `dup2()`, and `pipe()`.
6. **Background job layer** — tracks process IDs and job IDs.

### Important POSIX functions

- `fork()` creates a child process.
- `execv()` replaces the child process with the requested program.
- `waitpid()` allows the parent to wait for a child process.
- `pipe()` creates a communication channel between processes.
- `dup2()` connects a pipe or file to standard input or output.
- `open()` opens a file for reading or writing.
- `close()` closes file descriptors that are no longer needed.

### Example: external command

For the command `ls`:

1. The REPL reads the input.
2. The parser creates a command structure.
3. The executor checks whether `ls` is a built-in.
4. Since it is external, the shell searches for it using `PATH`.
5. The shell calls `fork()`.
6. The child calls `execv()`.
7. The parent calls `waitpid()`.
8. The prompt is displayed again.

### Example: pipeline

For:

```bash
cat file.txt | grep error
```

1. The parser creates two command structures.
2. The executor creates a pipe.
3. The first child connects its standard output to the pipe.
4. The second child connects its standard input to the pipe.
5. Both commands are executed.
6. Unused pipe descriptors are closed.
7. The parent waits for both children.

Unused descriptors must be closed; otherwise, the receiving command may wait indefinitely for end-of-file.

## 4. How to Explain the SRS

The **Software Requirements Specification (SRS)** defines the expected behaviour of the project. The latest version is [`Part-1 Deliverables/Simple-Shell_SRS_v1.2.docx`](Part-1%20Deliverables/Simple-Shell_SRS_v1.2.docx).

### SRS purpose

The SRS defines:

- The purpose and scope of the shell.
- Intended users.
- Functional requirements.
- Non-functional requirements.
- Operating environment.
- POSIX system-call dependencies.
- Security requirements.
- Stretch goals.

### Functional requirement groups

| Requirement group | Function |
|---|---|
| REQ-1 to REQ-4 | Prompt, loop, and built-in commands |
| REQ-5 to REQ-8 | Parsing and tokenization |
| REQ-9 to REQ-12 | External command execution |
| REQ-13 to REQ-15 | Input and output redirection |
| REQ-16 to REQ-17 | Piping |
| REQ-18 to REQ-19 | Background jobs |
| REQ-20 | Environment variables and `PATH` |
| REQ-21 to REQ-23 | Command history and signal handling |

### Non-functional requirements

The shell should be:

- **Reliable:** It should not crash on invalid input.
- **Responsive:** Built-in commands should normally return within 100 ms.
- **Portable:** It should work on Linux, macOS, or WSL2.
- **Maintainable:** The implementation is separated into modules.
- **Usable:** Error messages should be clear.
- **Safe:** It should not leave zombie processes or modify unintended files.

### Security requirements

The project includes the following security measures:

- No privilege escalation.
- Commands run with the invoking user's permissions.
- Redirection paths containing `..` are rejected.
- Environment variables are not printed automatically.
- Input length and argument limits are enforced.
- Malformed input produces an error instead of a crash.

### Current status

The core requirements from REQ-1 to REQ-20 and the current security requirements are implemented according to the source code and the [requirements traceability map](docs/rtm_code_references.md).

The following are stretch goals and are not currently implemented:

- REQ-21: Command history.
- REQ-22: `Ctrl+C` / `SIGINT` handling.
- REQ-23: `Ctrl+Z` / `SIGTSTP` handling.

Suggested explanation:

> The core shell functionality is complete. Command history and advanced signal handling were identified as stretch goals and are not included in the current completed scope.

## 5. How to Explain the Test Plan

The **Software Test Plan (STP)** explains how the SRS requirements are verified. It is available at [`Part-1 Deliverables/Simple-Shell_Test_Plan.docx`](Part-1%20Deliverables/Simple-Shell_Test_Plan.docx).

### Test Plan purpose

The Test Plan defines:

- Features to be tested.
- Test levels and testing strategy.
- Test environment.
- Entry and exit criteria.
- Security validation.
- Test responsibilities.
- Requirement-to-test-case traceability.

### Test levels

#### Unit testing

Each module is tested separately:

- Parser
- Executor
- Built-ins
- Redirection
- Environment handling

#### Integration testing

Multiple modules are tested together, for example:

```text
Parser + Executor
Parser + Redirection
Parser + Executor + Pipes
```

#### System testing

The complete `myshell` executable is tested using command-line scenarios. The automated test harness is [`tests/test_cases.sh`](tests/test_cases.sh).

### Important test demonstrations

#### Built-ins and directory changes

```bash
pwd
cd /
pwd
echo Hello
```

#### Input and output redirection

```bash
echo hello > output.txt
cat < output.txt
```

#### Overwrite and append modes

```bash
echo one > file.txt
echo two >> file.txt
cat file.txt
```

#### Multi-stage pipeline

```bash
printf "a\nb\n" | grep b | tr b B
```

#### Background jobs

```bash
sleep 1 &
echo prompt
jobs
```

#### Environment variables

```bash
echo $HOME
echo $PATH
export TEST_VALUE=hello
echo $TEST_VALUE
```

#### Security validation

```bash
echo test > ../outside.txt
```

Expected result:

```text
'..' paths are not allowed
```

#### Malformed input

```bash
echo "unterminated
echo recovered
```

The shell should report the error and continue processing later input.

The automated test script contains 32 test cases covering:

- External commands.
- Built-in commands.
- Invalid commands.
- Quoting and whitespace.
- Empty input.
- Redirection.
- Piping.
- Background jobs.
- Environment variables.
- Security restrictions.
- Long input.
- Malformed commands.

The Test Plan records that all tests passed for the Part-1 deliverables. Testing should be run in Linux, macOS, or WSL2 because the project requires POSIX tools.

## 6. Division of Presentation Work

The following division follows the feature ownership described in the project README and matches the current source structure.

### Prithviraj: REPL and built-in commands

#### Topics

- What the shell is.
- Prompt display and the REPL loop.
- Reading input using `fgets()`.
- EOF handling using `Ctrl+D`.
- Empty and whitespace-only lines.
- Built-in commands:
  - `cd`
  - `pwd`
  - `echo`
  - `help`
  - `exit`
- Why `cd` must execute inside the shell process.
- Error handling for invalid `cd`.
- Exit status handling.

#### Files

- [`src/main.c`](src/main.c)
- [`src/builtins.c`](src/builtins.c)
- [`src/builtins.h`](src/builtins.h)

#### Requirements

- REQ-1 to REQ-4.

#### Suggested explanation

> My part is the REPL and built-in command handling. The REPL repeatedly displays the prompt, reads a line, parses it, executes it, and then returns to the prompt. Built-ins such as `cd` must execute in the shell process itself; otherwise, changing directories in a child process would not affect the shell's working directory. I also handle commands such as `pwd`, `echo`, `help`, and `exit`, including their error conditions and exit statuses.

#### Demonstration

```bash
pwd
cd /
pwd
echo Hello
help
exit 7
```

### Aarush: Parser, quoting, and background jobs

#### Topics

- Tokenization.
- Consecutive whitespace.
- Quoted strings.
- Escaped characters.
- Operators `<`, `>`, `>>`, `|`, and `&`.
- Empty commands and malformed input.
- Background execution.
- Job IDs and process IDs.
- Non-blocking cleanup using `waitpid(..., WNOHANG)`.
- The `jobs` command.

#### Files

- [`src/parser.c`](src/parser.c)
- [`src/parser.h`](src/parser.h)
- Background job logic in [`src/executor.c`](src/executor.c)

#### Requirements

- REQ-5 to REQ-8.
- REQ-18 to REQ-19.

#### Suggested explanation

> My part is parsing and background job handling. The parser converts a text line into a linked list of Command structures. It understands whitespace, quoted strings, escaped characters, and shell operators. For background commands ending with `&`, the shell starts the process without waiting for it, stores its PID and job ID, and later checks whether it has finished without blocking the prompt.

#### Demonstration

```bash
echo "hello world"
echo 'a | b'
sleep 1 &
jobs
```

### Debhargo: External execution and pipelines

#### Topics

- Difference between built-in and external commands.
- `fork()` and `execv()`.
- Searching for commands.
- Parent and child process behaviour.
- `waitpid()` for foreground commands.
- Error statuses:
  - `127` for command not found.
  - `126` for execution failure.
- Creating pipelines.
- Connecting processes using `pipe()` and `dup2()`.
- Closing unused pipe descriptors.
- Waiting for every process in a pipeline.

#### Files

- [`src/executor.c`](src/executor.c)
- [`src/environment.c`](src/environment.c) for executable path lookup

#### Requirements

- REQ-9 to REQ-12.
- REQ-16 to REQ-17.

#### Suggested explanation

> My part is external command execution and piping. If the command is not built-in, the executor searches for its executable, creates a child using `fork()`, and the child uses `execv()` to run the program. The parent waits for foreground commands. For pipelines, the executor creates pipes between commands, connects standard input and output using `dup2()`, closes unused descriptors, and waits for all pipeline processes.

#### Demonstration

```bash
ls
definitely-not-a-command
printf "a\nb\n" | grep b | tr b B
```

### Diya: Redirection, environment, security, and testing

#### Topics

- Input redirection using `<`.
- Output overwrite using `>`.
- Output append using `>>`.
- `open()`, `dup2()`, and `close()`.
- Environment variable expansion.
- `PATH` lookup.
- `HOME`, `export`, and `unset`.
- Redirection path validation.
- Input-length limits.
- Security requirements.
- Test Plan and requirements traceability.
- Overall integration and documentation.

#### Files

- [`src/redirection.c`](src/redirection.c)
- [`src/environment.c`](src/environment.c)
- [`src/limits.h`](src/limits.h)
- [`tests/test_cases.sh`](tests/test_cases.sh)
- [`docs/rtm_code_references.md`](docs/rtm_code_references.md)

#### Requirements

- REQ-13 to REQ-15.
- REQ-20.
- REQ-SEC-1 to REQ-SEC-4.

#### Suggested explanation

> My part is redirection, environment handling, security validation, and testing integration. For redirection, the shell opens the requested file and uses `dup2()` to connect it to standard input or output. The `>` operator truncates a file, while `>>` appends to it. The environment module expands variables such as `$HOME` and searches the `PATH` for executables. We also validate redirection paths, reject parent-directory traversal, enforce input limits, and verify the requirements through the automated test plan.

#### Demonstration

```bash
echo first > output.txt
echo second >> output.txt
cat < output.txt

echo $HOME
echo $PATH
export TEST_VALUE=hello
echo $TEST_VALUE
```

## 7. Recommended Presentation Order

1. **Prithviraj:** Project introduction, prompt, REPL, and built-ins.
2. **Aarush:** Parser, quoting, operators, and background jobs.
3. **Debhargo:** `fork()`/`exec()`, external commands, waiting, and pipelines.
4. **Diya:** Redirection, environment variables, security, testing, and document summary.

Closing explanation:

> The SRS defines what the shell must do. The SAD describes the architecture and implementation approach used to satisfy those requirements. The Test Plan defines how each requirement is verified through unit, integration, and system testing. The RTM connects each requirement to the relevant source code and test cases.

## 8. Questions the Instructor May Ask

### Why is `cd` a built-in?

`cd` changes the current working directory. If it ran in a child process, only the child process would change directory and the shell would remain in the old directory.

### Why are pipes necessary?

A pipe allows the output of one process to become the input of another process.

```bash
ls | grep ".c"
```

### Why must unused pipe descriptors be closed?

If they remain open, the receiving process may never detect end-of-file and the pipeline can hang.

### What happens when a command is not found?

The shell prints an error, returns status `127`, and continues running without crashing.

### What is the difference between `>` and `>>`?

- `>` overwrites the file.
- `>>` appends to the existing file.

### Why does the shell use `fork()`?

The shell creates a separate child process to execute external programs while keeping the shell itself running.

### What are the current limitations?

Command history and advanced signal handling for `Ctrl+C` and `Ctrl+Z` are documented as stretch goals and are not part of the currently completed core functionality.

### Which operating systems are supported?

The project requires a POSIX environment such as Linux, macOS, or Windows WSL2. It is not intended to compile directly in ordinary Windows PowerShell without POSIX tools.
