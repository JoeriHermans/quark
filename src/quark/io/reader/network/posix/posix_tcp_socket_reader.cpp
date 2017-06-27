/**
 * Reader which is able to read bytes from a POSIX TCP socket.
 *
 * @date                    28 June 2017
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

// BEGIN Includes. /////////////////////////////////////////////////////////////

// Application dependencies.
#include <quark/io/reader/network/posix/posix_tcp_socket_reader.h>

// System dependencies.
#include <cassert>
#include <unistd.h>

// END Includes. ///////////////////////////////////////////////////////////////

inline void quark::posix_tcp_socket_reader::set_socket(quark::posix_tcp_socket * socket) {
    // Checking the precondition.
    assert(socket != nullptr);

    m_socket = socket;
}

quark::posix_tcp_socket_reader::posix_tcp_socket_reader(quark::posix_tcp_socket * socket) {
    set_socket(socket);
}

std::ssize_t quark::posix_tcp_socket_reader::read_all(char * buffer, const std::size_t size) {
    std::ssize_t buffer_size;
    std::ssize_t num_read;
    std::ssize_t num_read_total;
    int fd;

    // Checking the precondition.
    assert(buffer != nullptr && size > 0 && m_socket->is_connected());

    num_read_total = 0;
    buffer_size = static_cast<std::ssize_t>(size);
    fd = m_socket->get_file_descriptor();
    while(num_read_total != buffer_size) {
        num_read = read(fd, buffer + num_read_total, buffer_size - num_read_total);
        if(num_read < 0) {
            m_socket->close_connection();
            num_read_total = -1;
            break;
        }
        num_read_total += num_read;
    }

    return num_read_total;
}

std::ssize_t quark::posix_tcp_socket_reader::read_byte(char * byte) {
    std::ssize_t result;

    // Checking the precondition.
    assert(byte != nullptr && m_socket->is_connected());

    result = read(m_socket->get_file_descriptor(), byte, 1);

    return result;
}

std::ssize_t quark::posix_tcp_socket_reader::read_bytes(char * buffer, const std::size_t size) {
    std::ssize_t result;
    int fd;

    // Checking the precondition.
    assert(buffer != nullptr && size > 0 && m_socket->is_connected());

    fd = m_socket->get_file_descriptor();
    result = read(fd, buffer, size);

    return result;
}

void quark::posix_tcp_socket_reader::close_reader(void) {
    m_socket->close_connection();
}

#endif
