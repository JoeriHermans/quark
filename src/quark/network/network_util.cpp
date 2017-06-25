/**
 * Networking utility methods.
 *
 * @date                    26 June 2017
 * @author                  Joeri R. HERMANS
 * @version                 0.1
 *
 * Copyright 2017 Joeri R. HERMANS
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

// BEGIN Dependencies. /////////////////////////////////////////////////////////

// Application dependencies.
#include <quark/network/network_util.h>

// System dependencies.
#include <cassert>
#include <cstring>
#include <netdb.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

// END Dependencies. ///////////////////////////////////////////////////////////

int quark::connect(const std::string & address, const std::uint16_t port) {
    struct addrinfo hints;
    struct addrinfo * results;
    std::string port_string;
    int result;
    int fd;

    // Checking the precondition.
    assert(!address.empty() && port > 0);

    result = -1;
    // Clear the hints datastructure.
    memset(&hints, 0, sizeof hints);
    hints.ai_family   = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags    = AI_PASSIVE;
    // Convert the specified port to a string.
    port_string = std::to_string(port);
    // Fetch address records.
    int rc = getaddrinfo(address.c_str(), port_string.c_str(), &hints, &results);
    if(results != nullptr && rc >= 0) {
        fd = socket(results->ai_family, results->ai_socktype, results->ai_protocol);
        if(fd >= 0) {
            if(connect(fd, results->ai_addr, results->ai_addrlen) == 0)
                result = fd;
            else
                close(fd);
        }
    }

    return result;
}

bool quark::disable_cork(const int fd) {
    static const int optval = 0;
    bool success;

    // Checking precondition.
    assert(fd >= 0);

    success = (setsockopt(fd, SOL_SOCKET, TCP_CORK, &optval, sizeof optval) >= 0);

    return success;
}

bool quark::enable_cork(const int fd) {
    static const int optval = 1;
    bool success;

    // Checking precondition.
    assert(fd >= 0);

    success = (setsockopt(fd, SOL_SOCKET, TCP_CORK, &optval, sizeof optval) >= 0);

    return success;
}

bool quark::disable_keep_alive(const int fd) {
    static const int optval = 0;
    bool success;

    // Checking the precondition.
    assert(fd >= 0);

    success = (setsockopt(fd, SOL_SOCKET, SO_KEEPALIVE, &optval, sizeof optval) >= 0);

    return success;
}

bool quark::enable_keep_alive(const int fd) {
    static const int optval = 1;
    bool success;

    // Checking the precondition.
    assert(fd >= 0);

    success = (setsockopt(fd, SOL_SOCKET, SO_KEEPALIVE, &optval, sizeof optval) >= 0);

    return success;
}

bool quark::disable_nagle(const int fd) {
    static const int optval = 0;
    bool success;

    // Checking the precondition.
    assert(fd >= 0);

    success = (setsockopt(fd, IPPROTO_TCP, TCP_NODELAY, &optval, sizeof optval) >= 0);

    return success;
}

bool quark::enable_nagle(const int fd) {
    static const int optval = 1;
    bool success;

    // Checking the precondition.
    assert(fd >= 0);

    success = (setsockopt(fd, IPPROTO_TCP, TCP_NODELAY, &optval, sizeof optval) >= 0);

    return success;
}
