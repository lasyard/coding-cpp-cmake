#include "run_cmd.h"

#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "log_err.h"

bool run_cmd(int argc, char *argv[])
{
    if (argc < 1) {
        log_err("no command given");
        return false;
    }
    pid_t pid = fork();
    if (pid < 0) {
        log_err("cannot run command: fork failed: %s", strerror(errno));
        return false;
    } else if (pid == 0) {
        if (execvp(argv[0], &argv[0]) < 0) {
            log_err("cannot run command: %s", strerror(errno));
        }
        exit(EXIT_FAILURE);
    }
    waitpid(pid, NULL, 0);
    return true;
}
