#include "executor.h"
#include "parser.h"

#include <stdio.h>
#include <stdlib.h>

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

    printf("\nExecutor unit tests: %d passed, %d failed\n",
           passed, failed);

    return failed == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
