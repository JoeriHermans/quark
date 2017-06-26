/**
 * Class representing the properties and actions of a TCP socket.
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

#ifdef __unix__

// BEGIN Dependencies. /////////////////////////////////////////////////////////

// Application dependencies.
#include <quark/network/network_util.h>
#include <quark/network/posix/posix_tcp_socket.h>

// System dependencies.
#include <cassert>
#include <cstddef>
#include <poll.h>
#include <sys/socket.h>
#include <unistd.h>

// END Dependencies. ///////////////////////////////////////////////////////////

inline void quark::posix_tcp_socket::initialize(void) {
    set_file_descriptor(-1);
    m_reader = nullptr;
    m_writer = nullptr;
}

inline void quark::posix_tcp_socket::set_file_descriptor(const int fd) {
    m_file_descriptor = fd;
}

void quark::posix_tcp_socket::poll_socket(void) {
    struct pollfd pfd;

    // Check if the file descriptor is assigned.
    if(m_file_descriptor >= 0) {
        pfd.fd = m_file_descriptor;
        pfd.events = POLLNVAL | POLLHUP | POLLRDHUP;
        pfd.revents = 0;
        if(poll(&pfd, 1, 0) >= 1) {
            close(m_file_descriptor);
            set_file_descriptor(-1);
            delete m_reader; m_reader = nullptr;
            delete m_writer; m_writer = nullptr;
        }
    }
}

quark::posix_tcp_socket::posix_tcp_socket(void) {
    initialize();
}

quark::posix_tcp_socket::posix_tcp_socket(const int fd) {
    set_file_descriptor(fd);
    m_reader = new quark::posix_tcp_socket_reader(this);
    m_writer = new quark::posix_tcp_socket_writer(this);
}

quark::posix_tcp_socket::~posix_tcp_socket(void) {
    close_connection();
    delete m_reader; m_reader = nullptr;
    delete m_writer; m_writer = nullptr;
}

bool quark::posix_tcp_socket::is_connected(void) const {
    // Poll the file descriptor.
    poll_socket();

    return (m_file_descriptor >= 0);
}

quark::reader * quark::posix_tcp_socket::get_reader(void) const {
    return m_reader;
}

quark::writer * quark::posix_tcp_socket::get_writer(void) const {
    return m_writer;
}

bool quark::posix_tcp_socket::create_connection(const std::string & address, const std::uint16_t port) {
    int fd;

    // Checking the precondition.
    assert(!address.empty() && port > 0);

    close_connection();
    fd = quark::connect(address, port);
    if(fd >= 0) {
        // Set the file descriptor.
        set_file_descriptor(fd);
        // Allocate reader and writer.
        m_reader = new quark::posix_tcp_socket_reader(this);
        m_writer = new quark::posix_tcp_socket_writer(this);
    }

    return (fd >= 0);
}

void quark::posix_tcp_socket::set_send_timeout(const std::time_t seconds) {
    struct timeval tv;

    if(is_connected()) {
        tv.tv_sec = seconds;
        tv.tv_usec = 0;
        setsockopt(m_file_descriptor, SOL_SOCKET, SO_SNDTIMEO, &tv, sizeof tv);
    }
}

void quark::posix_tcp_socket::set_receive_timeout(const std::time_t seconds) {
    struct timeval tv;

    if(is_connected()) {
        tv.tv_sec = seconds;
        tv.tv_usec = 0;
        setsockopt(m_file_descriptor, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof tv);
    }
}

void quark::posix_tcp_socket::close_connection(void) {
    // Check if the file descriptor is assigned.
    if(m_file_descriptor >= 0) {
        // Close the file descriptor.
        close(m_file_descriptor);
        set_file_descriptor(-1);
        // Free allocated memory.
        delete m_reader; m_reader = nullptr;
        delete m_writer; m_writer = nullptr;
    }
}

#endif
