#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>

#include "log_err.h"
#include "socket.h"

int main(int argc, char *argv[])
{
    if (argc < 3) {
        printf("Usage: %s <host> <port>\n", argv[0]);
        exit(1);
    }
    int sock = connect_to(argv[1], argv[2]);
    if (sock < 0) {
        log_err("failed to connect to %s:%s", argv[1], argv[2]);
        exit(1);
    }
    close(sock);
}
