#include <uxr/client/transport.h>

#include <version.h>

#if ZEPHYR_VERSION_CODE >= ZEPHYR_VERSION(3,1,0)
#include <zephyr/kernel.h>
#include <zephyr/posix/unistd.h>
#include <zephyr/posix/arpa/inet.h>
#include <zephyr/posix/netdb.h>
#else
#include <zephyr.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>
#endif

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>

#include <microros_transports.h>

bool zephyr_transport_open(struct uxrCustomTransport * transport){
    zephyr_transport_params_t * params = (zephyr_transport_params_t*) transport->args;

    bool rv = false;
    params->poll_fd.fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    if (-1 != params->poll_fd.fd)
    {
        struct addrinfo hints;
        struct addrinfo* result;
        struct addrinfo* ptr;

        memset(&hints, 0, sizeof(hints));
        hints.ai_family = AF_INET;
        hints.ai_socktype = SOCK_DGRAM;

        if (0 == getaddrinfo(params->ip, params->port, &hints, &result))
        {
            for (ptr = result; ptr != NULL; ptr = ptr->ai_next)
            {
                if (0 == connect(params->poll_fd.fd, ptr->ai_addr, ptr->ai_addrlen))
                {
                    params->poll_fd.events = POLLIN;
                    rv = true;
                    break;
                }
            }
        }
        freeaddrinfo(result);
    }
    return rv;
}

bool zephyr_transport_close(struct uxrCustomTransport * transport){
    zephyr_transport_params_t * params = (zephyr_transport_params_t*) transport->args;

    return (-1 == params->poll_fd.fd) ? true : (0 == close(params->poll_fd.fd));
}

size_t zephyr_transport_write(struct uxrCustomTransport* transport, const uint8_t * buf, size_t len, uint8_t * err){
    zephyr_transport_params_t * params = (zephyr_transport_params_t*) transport->args;

    size_t rv = 0;
    ssize_t bytes_sent = send(params->poll_fd.fd, (void*)buf, len, 0);
    if (-1 != bytes_sent)
    {
        rv = (size_t)bytes_sent;
        *err = 0;
    }
    else
    {
        *err = 1;
    }
    return rv;
}

size_t zephyr_transport_read(struct uxrCustomTransport* transport, uint8_t* buf, size_t len, int timeout, uint8_t* err){
    zephyr_transport_params_t * params = (zephyr_transport_params_t*) transport->args;

    size_t rv = 0;
    int poll_rv = poll(&params->poll_fd, 1, timeout);
    if (0 < poll_rv)
    {
        ssize_t bytes_received = recv(params->poll_fd.fd, (void*)buf, len, 0);
        if (-1 != bytes_received)
        {
            rv = (size_t)bytes_received;
            *err = 0;
        }
        else
        {
            *err = 1;
        }
    }
    else
    {
        *err = (0 == poll_rv) ? 0 : 1;
    }
    return rv;
}