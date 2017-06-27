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
#include <cassert>

// END Includes. ///////////////////////////////////////////////////////////////

inline void quark::posix_tcp_server_socket::initialize(void) {
    m_file_descriptor = -1;
}

quark::posix_tcp_server_socket::posix_tcp_server_socket(void) {
    initialize();
}

quark::posix_tcp_server_socket::posix_tcp_server_socket(const std::uint16_t port) {
    initialize();
    set_port(port);
}

#endif
