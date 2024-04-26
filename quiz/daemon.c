#include "daemon.h"

#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/resource.h>
#include <sys/stat.h>

#include "log_err.h"

static int lock_file(int fd)
{
    struct flock fl;
    fl.l_type = F_WRLCK;
    fl.l_whence = SEEK_SET;
    fl.l_start = 0;
    fl.l_len = 0;
    return fcntl(fd, F_SETLK, &fl);
}

pid_t daemonize(const char *log_file)
{
    umask(0);
    struct rlimit rl;
    if (getrlimit(RLIMIT_NOFILE, &rl) < 0) {
        log_err("failed to get file limit: %s", strerror(errno));
        return -1;
    }
    pid_t pid = fork();
    if (pid < 0) {
        log_err("failed to fork new process: %s", strerror(errno));
        return -1;
    }
    if (pid > 0) { // parent
        return pid;
    }
    setsid();
    struct sigaction sa;
    sa.sa_handler = SIG_IGN;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    if (sigaction(SIGHUP, &sa, NULL) < 0) {
        log_err("failed to set signal: %s", strerror(errno));
        return -2;
    }
    if (chdir("/") < 0) {
        log_err("failed to chdir to root: %s", strerror(errno));
        return -2;
    }
    if (rl.rlim_max == RLIM_INFINITY) {
        rl.rlim_max = 1024;
    }
    for (rlim_t i = 0; i < rl.rlim_max; i++) {
        close(i);
    }
    int fd0 = -1;
    if (log_file != NULL) {
        fd0 = open(log_file, O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    }
    if (fd0 < 0) {
        fd0 = open("/dev/null", O_RDWR);
    }
    if (fd0 != 0) {
        // Normally this should not happen.
        return -2;
    }
    int fd1 = dup(0);
    int fd2 = dup(0);
    if (fd1 != 1 || fd2 != 2) {
        // Normally this should not happen.
        return -2;
    }
    return 0;
}

bool is_running(const char *pid_file)
{
    int fd = open(pid_file, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if (fd < 0) {
        log_err("can’t open %s: %s", pid_file, strerror(errno));
        exit(EXIT_FAILURE);
    }
    if (lock_file(fd) < 0) {
        if (errno == EACCES || errno == EAGAIN) {
            close(fd);
            return true;
        }
        log_err("can’t lock %s: %s", pid_file, strerror(errno));
        exit(EXIT_FAILURE);
    }
    if (ftruncate(fd, 0) < 0) {
        // This should not happen.
        log_err("can’t truncate %s: %s", pid_file, strerror(errno));
        return false;
    }
    char buf[16];
    int n = sprintf(buf, "%ld", (long)getpid());
    if (n > 0) {
        buf[n] = '\n';
        write(fd, buf, n + 1);
    }
    // Do not close the file, or the lock is released.
    return false;
}
