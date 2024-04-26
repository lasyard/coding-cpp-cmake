#ifndef _QUIZ_DAEMON_H_
#define _QUIZ_DAEMON_H_

#include <stdbool.h>
#include <unistd.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Fork a daemon process.
 *
 * @param log_file the file to redirect the stdard input, output and error to
 * @return pid_t the pid of the daemon
 * 0 means the daemon itself
 * -1 means error to create daemon
 * -2 means error in daemon
 */
pid_t daemonize(const char *log_file);

/**
 * @brief Check if an daemon is already running by a pid file, must called in the daemon process.
 *
 * @param pid_file the name of the pid file
 * @return true is running
 * @return false is not running
 */
bool is_running(const char *pid_file);

#ifdef __cplusplus
}
#endif

#endif /* _QUIZ_DAEMON_H_ */
