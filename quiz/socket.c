#include <errno.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <arpa/inet.h>

#include "log_err.h"

static const char *ai_family_str(struct addrinfo *ai_p)
{
    switch (ai_p->ai_family) {
    case PF_INET:
        return "inet";
        break;
    case PF_INET6:
        return "inet6";
        break;
    case PF_UNIX:
        return "unix";
        break;
    case AF_UNSPEC:
        return "unspecified";
        break;
    default:
        return "unknown";
    }
}

static const char *ai_socktype_str(struct addrinfo *ai_p)
{
    switch (ai_p->ai_socktype) {
    case SOCK_STREAM:
        return "stream";
        break;
    case SOCK_DGRAM:
        return "dgram";
        break;
    case SOCK_SEQPACKET:
        return "seqpacket";
        break;
    case SOCK_RAW:
        return "raw";
        break;
    default:
        return "unknown";
    }
}

static const char *ai_protocol_str(struct addrinfo *ai_p)
{
    switch (ai_p->ai_protocol) {
    case 0:
        return "default";
        break;
    case IPPROTO_TCP:
        return "TCP";
        break;
    case IPPROTO_UDP:
        return "UDP";
        break;
    case IPPROTO_RAW:
        return "raw";
        break;
    default:
        return "unknown";
    }
}

#define AI_ADDR_BUF_LEN INET6_ADDRSTRLEN + 1 + 17

static const char *get_ai_addr(struct addrinfo *ai_p, char *buf)
{
    const char *addr = NULL;
    if (ai_p->ai_family == PF_INET) {
        struct sockaddr_in *addr_p = (struct sockaddr_in *)ai_p->ai_addr;
        addr = inet_ntop(PF_INET, &addr_p->sin_addr, buf, INET_ADDRSTRLEN);
        if (addr != NULL) {
            sprintf(buf + strlen(addr), ":%d", ntohs(addr_p->sin_port));
        }
    } else if (ai_p->ai_family == PF_INET6) {
        struct sockaddr_in6 *addr_p = (struct sockaddr_in6 *)ai_p->ai_addr;
        addr = inet_ntop(PF_INET6, &addr_p->sin6_addr, buf, INET6_ADDRSTRLEN);
        if (addr != NULL) {
            sprintf(buf + strlen(addr), ":%d", ntohs(addr_p->sin6_port));
        }
    }
    if (addr == NULL) {
        sprintf(buf, "unknown");
        return buf;
    }
    return addr;
}

int connect_to(const char *host, const char *port)
{
    struct addrinfo *ai_list;
    struct addrinfo *ai_p;
    struct addrinfo hint;
    memset(&hint, 0, sizeof(hint));
    hint.ai_flags = AI_ADDRCONFIG;
    hint.ai_family = PF_UNSPEC;
    hint.ai_socktype = SOCK_STREAM;
    int err = getaddrinfo(host, port, &hint, &ai_list);
    if (err != 0) {
        log_err("failed to getaddrinfo for \"%s:%s\": %s", host, port, gai_strerror(err));
        return -1;
    }
    int sock = -1;
    for (ai_p = ai_list; ai_p != NULL; ai_p = ai_p->ai_next) {
        sock = socket(ai_p->ai_family, ai_p->ai_socktype, ai_p->ai_protocol);
        if (sock < 0) {
            log_err(
                "failed to create socket of %s family, %s type, %s protocol: %s",
                ai_family_str(ai_p),
                ai_socktype_str(ai_p),
                ai_protocol_str(ai_p),
                strerror(errno)
            );
            continue;
        }
        if (connect(sock, ai_p->ai_addr, ai_p->ai_addrlen) < 0) {
            char buf[AI_ADDR_BUF_LEN];
            log_err("failed to connect to %s: %s", get_ai_addr(ai_p, buf), strerror(errno));
            close(sock);
            sock = -1;
            continue;
        }
        break;
    }
    freeaddrinfo(ai_list);
    return sock;
}
