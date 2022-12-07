// Copyright 2021 Proyectos y Sistemas de Mantenimiento SL (eProsima).
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef _MICROROS_CLIENT_ZEPHYR_TRANSPORT_H_
#define _MICROROS_CLIENT_ZEPHYR_TRANSPORT_H_

#include <unistd.h>

#include <sys/types.h>
#include <posix/sys/socket.h>
#include <posix/poll.h>

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct {
    struct pollfd poll_fd;
    char ip[16];
    char port[6];
} zephyr_transport_params_t;

#define MICRO_ROS_FRAMING_REQUIRED false
static zephyr_transport_params_t default_params = {{0,0,0}, "192.168.1.100", "8888"};

bool zephyr_transport_open(struct uxrCustomTransport * transport);
bool zephyr_transport_close(struct uxrCustomTransport * transport);
size_t zephyr_transport_write(struct uxrCustomTransport* transport, const uint8_t * buf, size_t len, uint8_t * err);
size_t zephyr_transport_read(struct uxrCustomTransport* transport, uint8_t* buf, size_t len, int timeout, uint8_t* err);

#ifdef __cplusplus
}
#endif

#endif //_MICROROS_CLIENT_ZEPHYR_TRANSPORT_H_