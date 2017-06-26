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
#include <quark/network/posix/posix_tcp_socket.h>
#include <quark/network/network_util.h>

// System dependencies.
#include <cassert>

// END Dependencies. ///////////////////////////////////////////////////////////

inline void quark::posix_tcp_socket::initialize(void) {
    set_file_descriptor(-1);
    m_reader = nullptr;
    m_writer = nullptr;
}

inline void quark::posix_tcp_socket::set_file_descriptor(const int fd) {
    // Checking the precondition.
    assert(fd >= 0);

    m_file_descriptor = fd;
}

quark::posix_tcp_socket::posix_tcp_socket(void) {
    initialize();
}

quark::posix_tcp_socket::posix_tcp_socket(const int fd) {
    set_file_descriptor(fd);
    // TODO Implement.
}

#endif
