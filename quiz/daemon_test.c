#include <stdlib.h>
#include <unistd.h>

#include "daemon.h"
#include "log_err.h"

int main()
{
    pid_t pid = daemonize("/var/log/daemon_test.log");
    if (pid == 0) {
        if (is_running("/var/run/daemon_test.pid")) {
            log_err("daemon_test is already running");
            return EXIT_FAILURE;
        }
        sleep(10);
    }
    return pid > 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
