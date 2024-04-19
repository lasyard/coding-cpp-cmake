#ifndef _QUIZ_DAEMON_H_
#define _QUIZ_DAEMON_H_

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

void daemonize();

/**
 * @brief Check if an daemon is already running by a pid file, must called after `daemonize`.
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
