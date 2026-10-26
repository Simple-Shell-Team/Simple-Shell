#include "parser.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int passed;
static int failed;

#define CHECK(condition, description) do { \
    if (condition) { \
        printf("PASS: %s\n", description); \
        passed++; \
    } else { \
        printf("FAIL: %s (line %d)\n", description, __LINE__); \
        failed++; \
    } \
} while (0)

static void test_simple_command(void)
{
    Command *cmd = NULL;
    char *error = NULL;
    int result = parse_line("echo hello world", &cmd, &error);

    CHECK(result == 0 && cmd != NULL, "parse a simple command");
    CHECK(cmd != NULL && cmd->argv != NULL &&
          strcmp(cmd->argv[0], "echo") == 0 &&
          strcmp(cmd->argv[1], "hello") == 0 &&
          strcmp(cmd->argv[2], "world") == 0 &&
          cmd->argv[3] == NULL, "preserve command arguments");

    free(error);
    free_commands(cmd);
}

static void test_quoted_arguments(void)
{
    Command *cmd = NULL;
    char *error = NULL;
    int result = parse_line("echo \"hello world\"", &cmd, &error);

    CHECK(result == 0 && cmd != NULL &&
          cmd->argv[1] != NULL &&
          strcmp(cmd->argv[1], "hello world") == 0 &&
          cmd->argv[2] == NULL, "preserve a quoted argument");

    free(error);
    free_commands(cmd);
}

static void test_pipeline(void)
{
    Command *cmd = NULL;
    char *error = NULL;
    int result = parse_line("echo hello | wc -c", &cmd, &error);

    CHECK(result == 0 && cmd != NULL && cmd->next != NULL,
          "parse a two-command pipeline");

    CHECK(cmd != NULL && cmd->next != NULL &&
          strcmp(cmd->argv[0], "echo") == 0 &&
          strcmp(cmd->next->argv[0], "wc") == 0 &&
          strcmp(cmd->next->argv[1], "-c") == 0,
          "preserve pipeline command order");

    free(error);
    free_commands(cmd);
}

static void test_redirection(void)
{
    Command *cmd = NULL;
    char *error = NULL;
    int result = parse_line("cat < input.txt >> output.txt",
                            &cmd, &error);

    CHECK(result == 0 && cmd != NULL &&
          cmd->input_file != NULL &&
          strcmp(cmd->input_file, "input.txt") == 0,
          "parse input redirection");

    CHECK(cmd != NULL && cmd->output_file != NULL &&
          strcmp(cmd->output_file, "output.txt") == 0 &&
          cmd->append_mode == 1,
          "parse append redirection");

    free(error);
    free_commands(cmd);
}

static void test_background_command(void)
{
    Command *cmd = NULL;
    char *error = NULL;
    int result = parse_line("sleep 1 &", &cmd, &error);

    CHECK(result == 0 && cmd != NULL && cmd->background == 1,
          "recognize a background command");

    free(error);
    free_commands(cmd);
}

static void test_environment_expansion(void)
{
    Command *cmd = NULL;
    char *error = NULL;

    setenv("UNIT_TEST_PARSER_VALUE", "expanded-value", 1);
    int result = parse_line("echo $UNIT_TEST_PARSER_VALUE",
                            &cmd, &error);

    CHECK(result == 0 && cmd != NULL &&
          cmd->argv[1] != NULL &&
          strcmp(cmd->argv[1], "expanded-value") == 0,
          "expand an environment variable");

    free(error);
    free_commands(cmd);
    unsetenv("UNIT_TEST_PARSER_VALUE");
}

static void test_empty_input(void)
{
    Command *cmd = NULL;
    char *error = NULL;
    int result = parse_line("   ", &cmd, &error);

    CHECK(result == 0 && cmd == NULL,
          "accept empty or whitespace-only input");

    free(error);
    free_commands(cmd);
}

static void test_invalid_syntax(void)
{
    Command *cmd = NULL;
    char *error = NULL;
    int result = parse_line("echo hello |", &cmd, &error);

    CHECK(result == -1 && cmd == NULL && error != NULL,
          "reject a pipeline missing its final command");

    free(error);
    free_commands(cmd);

    cmd = NULL;
    error = NULL;
    result = parse_line("cat >", &cmd, &error);

    CHECK(result == -1 && cmd == NULL && error != NULL,
          "reject redirection without a filename");

    free(error);
    free_commands(cmd);
}

int main(void)
{
    test_simple_command();
    test_quoted_arguments();
    test_pipeline();
    test_redirection();
    test_background_command();
    test_environment_expansion();
    test_empty_input();
    test_invalid_syntax();

    printf("\nParser unit tests: %d passed, %d failed\n",
           passed, failed);

    return failed == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
