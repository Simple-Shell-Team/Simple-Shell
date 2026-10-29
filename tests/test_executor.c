#include "executor.h"
#include "parser.h"

#include <stdio.h>
#include <stdlib.h>

#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

static int passed;
static int failed;

#define CHECK(condition, description) do {                 \
    int ok = !!(condition);                                \
    printf("%s: %s\n", ok ? "PASS" : "FAIL", description);  \
    if (ok) passed++; else failed++;                       \
} while (0)

static int run_line(const char *line)
{
    Command *commands = NULL;
    char *error = NULL;
    int result;

    if (parse_line(line, &commands, &error) != 0) {
        fprintf(stderr, "parse failed for '%s': %s\n",
                line, error != NULL ? error : "unknown error");
        free(error);
        free_commands(commands);
        return -1;
    }

    result = execute_commands(commands);
    free(error);
    free_commands(commands);
    return result;
}


static int count_open_fds(void)
{
    long limit = sysconf(_SC_OPEN_MAX);
    long fd;
    int count = 0;

    if (limit < 0 || limit > 4096)
        limit = 4096;

    for (fd = 0; fd < limit; fd++) {
        errno = 0;
        if (fcntl((int)fd, F_GETFD) != -1 || errno != EBADF)
            count++;
    }

    return count;
}

static void test_file_descriptor_cleanup(void)
{
    char path[] = "/tmp/simple-shell-fd-check-XXXXXX";
    char command[512];
    int temp_fd = mkstemp(path);
    int baseline;
    int after;
    int all_succeeded = 1;
    int length;
    int i;

    if (temp_fd < 0) {
        CHECK(0, "create temporary file for descriptor test");
        return;
    }
    close(temp_fd);

    length = snprintf(command, sizeof(command),
                      "echo fd-check > %s", path);
    if (length < 0 || (size_t)length >= sizeof(command)) {
        unlink(path);
        CHECK(0, "prepare redirection for descriptor test");
        return;
    }

    if (run_line("true | true") != 0 || run_line(command) != 0) {
        unlink(path);
        CHECK(0, "warm up pipeline and redirection");
        return;
    }

    baseline = count_open_fds();

    for (i = 0; i < 25; i++) {
        if (run_line("true | true") != 0)
            all_succeeded = 0;
        if (run_line(command) != 0)
            all_succeeded = 0;
    }

    after = count_open_fds();
    unlink(path);

    CHECK(all_succeeded,
          "repeat pipelines and redirections successfully");
    CHECK(after == baseline,
          "close file descriptors after pipelines and redirections");
}

int main(void)
{
    CHECK(run_line("true") == 0,
          "execute a successful command");

    CHECK(run_line("false") == 1,
          "return a nonzero exit status");

    CHECK(run_line("sh -c 'exit 7'") == 7,
          "propagate an external command exit status");

    CHECK(run_line("command_that_does_not_exist_7f3a") == 127,
          "return 127 for a missing command");

    CHECK(run_line("true | true") == 0,
          "execute a two-command pipeline");

    CHECK(run_line("false | true") == 0,
          "return the final pipeline command status");

    CHECK(run_line("true | false") == 1,
          "propagate failure from the final pipeline command");

      test_file_descriptor_cleanup();

    printf("\nExecutor unit tests: %d passed, %d failed\n",
           passed, failed);

    return failed == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
