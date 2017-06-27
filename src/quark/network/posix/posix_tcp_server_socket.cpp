/**
 * Class which describes the properties and actions of a listening
 * POSIX TCP socket.
 *
 * @date                    TODO
 * @author                  Joeri R. HERMANS
 * @version                 0.1
 *
 * Copyright 2016 Joeri R. HERMANS
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

#ifdef __unix__

// BEGIN Includes. /////////////////////////////////////////////////////////////

// Application dependencies.
#include <quark/network/posix/posix_tcp_server_socket.h>
#include <quark/network/posix/posix_tcp_socket.h>

// System dependencies.
#include <arpa/inet.h>
#include <cassert>
#include <cstring>
#include <ctime>
#include <netdb.h>
#include <netinet/in.h>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

// END Includes. ///////////////////////////////////////////////////////////////

inline void quark::posix_tcp_server_socket::initialize(void) {
    m_file_descriptor = -1;
}

inline void quark::posix_tcp_server_socket::set_file_descriptor(const int fd) {
    // Checking the precondition.
    assert(fd >= 0);

    m_file_descriptor = fd;
}

quark::posix_tcp_server_socket::posix_tcp_server_socket(const std::uint16_t port) {
    initialize();
    set_port(port);
}

quark::posix_tcp_server_socket::~posix_tcp_server_socket(void) {
    stop_listening();
}

bool quark::posix_tcp_server_socket::bind_to_port(void) {
    static int yes = 1;
    struct addrinfo hints;
    struct addrinfo * server_info;
    std::string port_string;
    bool bounded;
    int fd;

    if(is_bound()) {
        bounded = true;
    } else {
        bounded = false;
        memset(&hints, 0, sizeof hints);
        hints.ai_family   = AF_UNSPEC;
        hints.ai_socktype = SOCK_STREAM;
        hints.ai_flags    = AI_PASSIVE;
        port_string = std::to_string(get_port());
        int rc = getaddrinfo(nullptr, port_string.c_str(), &hints, &server_info);
        if(rc == 0) {
            fd = ::socket(server_info->ai_family, server_info->ai_socktype, server_info->ai_protocol);
            if(fd >= 0) {
                setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof yes);
                if(bind(fd, server_info->ai_addr, server_info->ai_addrlen) == 0 &&
                   listen(fd, 64) == 0) {
                    bounded = true;
                    set_file_descriptor(fd);
                }
            }
            freeaddrinfo(server_info);
        }
    }

    return bounded;
}

bool quark::posix_tcp_server_socket::is_bound(void) const{
    return (m_file_descriptor >= 0);
}

quark::socket * quark::posix_tcp_server_socket::accept_socket(const std::time_t seconds) {
    // Checking the precondition.
    assert(is_bound());

    return nullptr;
}

quark::socket * quark::posix_tcp_server_socket::accept_socket(void) {
    quark::socket *  s;
    int fd;

    // Checking the precondition.
    assert(is_bound());

    s = nullptr;
    if(is_bound()) {
        fd = accept(m_file_descriptor, &addr, &addr_length);
        if(fd >= 0)
            s = new quark::posix_tcp_socket(fd);
    }

    return s;
}

void quark::posix_tcp_server_socket::stop_listening(void) {
    if(is_bound()) {
        close(m_file_descriptor);
        m_file_descriptor = -1;
    }
}

#endif
