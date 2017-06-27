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
#ifndef QUARK_POSIX_TCP_SOCKET_WRITER_H_
#define QUARK_POSIX_TCP_SOCKET_WRITER_H_

// BEGIN Includes. /////////////////////////////////////////////////////////////

// Application dependencies.
#include <quark/io/writer/writer.h>
#include <quark/network/posix/posix_tcp_socket.h>

// END Includes. ///////////////////////////////////////////////////////////////

namespace quark {

class posix_tcp_socket_writer : public writer {

    public:

    // BEGIN Class constants. //////////////////////////////////////////////////
    // END Class constants. ////////////////////////////////////////////////////

    private:

    // BEGIN Private members. //////////////////////////////////////////////////

    /**
     * Holds the socket to write to.
     */
    quark::posix_tcp_socket * m_socket;

    // END Private members. ////////////////////////////////////////////////////

    // BEGIN Private methods. //////////////////////////////////////////////////

    inline void set_socket(quark::posix_tcp_socket * socket);

    // END Private methods. ////////////////////////////////////////////////////

    protected:

    // BEGIN Protected methods. ////////////////////////////////////////////////
    // END Protected methods. //////////////////////////////////////////////////

    public:

    // BEGIN Constructor. //////////////////////////////////////////////////////

    posix_tcp_socket_writer(quark::posix_tcp_socket * socket);

    // END Constructor. ////////////////////////////////////////////////////////

    // BEGIN Destructor. ///////////////////////////////////////////////////////

    virtual ~posix_tcp_socket_writer(void) = default;

    // END Destructor. /////////////////////////////////////////////////////////

    // BEGIN Public methods. ///////////////////////////////////////////////////

    virtual std::ssize_t write_all(const char * buffer, const std::size_t size);

    virtual std::ssize_t write_byte(const char byte);

    virtual std::ssize_t write_bytes(const char * buffer, const std::size_t size);

    virtual void close_writer(void);

    // END Public methods. /////////////////////////////////////////////////////

    // BEGIN Public static methods. ////////////////////////////////////////////
    // END Public static methods. //////////////////////////////////////////////

};

};

#endif
#endif
