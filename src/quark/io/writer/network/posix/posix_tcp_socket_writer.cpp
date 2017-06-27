/**
 * Class which is responsible for writing bytes to POSIX sockets.
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
#include <quark/io/writer/network/posix/posix_tcp_socket_writer.h>

// System dependencies.
#include <cassert>
#include <unistd.h>

// END Includes. ///////////////////////////////////////////////////////////////

inline void quark::posix_tcp_socket_writer::set_socket(quark::posix_tcp_socket * socket) {
    // Checking the precondition.
    assert(socket != nullptr);

    m_socket = socket;
}

quark::posix_tcp_socket_writer::posix_tcp_socket_writer(quark::posix_tcp_socket * socket) {
    set_socket(socket);
}

std::ssize_t quark::posix_tcp_socket_writer::write_all(const char * buffer, const std::size_t size) {
    std::ssize_t buffer_size;
    std::ssize_t num_written;
    std::ssize_t num_written_total;
    int fd;

    // Checking the predicition.
    assert(buffer != nullptr && size > 0 && m_socket->is_connected());

    num_written_total = 0;
    buffer_size = static_cast<std::ssize_t>(size);
    fd = m_socket->get_file_descriptor();
    while(num_written_total != buffer_size) {
        num_written = write(fd, buffer + num_written_total, buffer_size - num_written_total);
        if(num_written < 0) {
            m_socket->close_connection();
            num_written_total = -1;
            break;
        }
        num_written_total += num_written;
    }

    return num_written_total;
}

std::ssize_t quark::posix_tcp_socket_writer::write_byte(const char byte) {
    std::ssize_t result;

    // Checking prediction.
    assert(m_socket->is_connected());

    result = write(m_socket->get_file_descriptor(), &byte, 1);

    return result;
}

std::ssize_t quark::posix_tcp_socket_writer::write_bytes(const char * buffer, const std::size_t size) {
    std::size_t result;

    // Checking the precondition.
    assert(buffer != nullptr && size > 0 && m_socket->is_connected());

    result = write(m_socket->get_file_descriptor(), buffer, size);

    return result;
}

void quark::posix_tcp_socket_writer::close_writer(void) {
    m_socket->close_connection();
}

#endif
