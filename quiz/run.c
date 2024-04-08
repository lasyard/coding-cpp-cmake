#include <errno.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/wait.h>

static void log_err(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    fputc('\n', stderr);
    va_end(args);
}

static bool run_cmd(int argc, char *argv[])
{
    if (argc < 2) {
        log_err("No command given");
        return false;
    }
    pid_t pid = fork();
    if (pid < 0) {
        log_err("Cannot run command: fork failed: %s", strerror(errno));
        return false;
    } else if (pid == 0) {
        /* Generally the first argument is itself, so skip it */
        if (execvp(argv[1], &argv[1]) < 0) {
            log_err("Cannot run command: %s", strerror(errno));
        }
        exit(EXIT_FAILURE);
    }
    return true;
}

int main(int argc, char *argv[])
{
    run_cmd(argc, argv);
    wait(NULL);
}
