#include <stdlib.h>
#include <syslog.h>
#include <unistd.h>

#include "daemon.h"

int main()
{
    daemonize();
    openlog("daemon_test", LOG_CONS, LOG_DAEMON);
    if (is_running("/var/run/daemon_test.pid")) {
        syslog(LOG_DAEMON | LOG_ERR, "daemon_test is already running");
        exit(EXIT_FAILURE);
    }
    sleep(10);
}
