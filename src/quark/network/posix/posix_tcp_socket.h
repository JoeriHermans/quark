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
#ifndef QUARK_POSIX_TCP_SOCKET_H_
#define QUARK_POSIX_TCP_SOCKET_H_

// BEGIN Dependencies. /////////////////////////////////////////////////////////

// Application dependencies.
#include <quark/io/reader/reader.h>
#include <quark/io/writer/writher.h>

// END Dependencies. ///////////////////////////////////////////////////////////

namespace quark {

class posix_tcp_socket {

    public:

    // BEGIN Class constants. //////////////////////////////////////////////////
    // END Class constants. ////////////////////////////////////////////////////

    private:

    // BEGIN Private members. //////////////////////////////////////////////////

    /**
     * Holds the file descriptor of the opened socket.
     *
     * @note By default, this will be equal to -1. Same for a not-connected
     *       socket.
     */
    mutable int m_file_descriptor;

    /**
     * Reader associated with the POSIX TCP socket.
     *
     * @note Equal to the null reference if not connected.
     */
    quark::reader * m_reader;

    /**
     * Writer associated with the POSIX TCP socket.
     *
     * @note Equal to the null reference if not connected.
     */
    quark::writer * m_writer;

    // END Private members. ////////////////////////////////////////////////////

    // BEGIN Private methods. //////////////////////////////////////////////////
    // END Private methods. ////////////////////////////////////////////////////

    protected:

    // BEGIN Protected methods. ////////////////////////////////////////////////

    inline void initialize(void);

    void set_file_descriptor(const int fd);

    void poll_socket(void);

    // END Protected methods. //////////////////////////////////////////////////

    public:

    // BEGIN Constructor. //////////////////////////////////////////////////////

    posix_tcp_socket(void);

    posix_tcp_socket(const int file_descriptor);

    // END Constructor. ////////////////////////////////////////////////////////

    // BEGIN Destructor. ///////////////////////////////////////////////////////

    virtual ~posix_tcp_socket(void) = default;

    // END Destructor. /////////////////////////////////////////////////////////

    // BEGIN Public methods. ///////////////////////////////////////////////////

    virtual bool is_connected(void) const;

    virtual quark::reader * get_reader(void) const;

    virtual quark::writer * get_writer(void) const;

    virtual void create_connection(const std::string & address, const std::uint16_t port);

    virtual void set_receive_timeout(const std::time_t seconds);

    virtual void set_send_timeout(const std::time_t seconds);

    virtual void close_connection(void);

    // END Public methods. /////////////////////////////////////////////////////

    // BEGIN Public static methods. ////////////////////////////////////////////
    // END Public static methods. //////////////////////////////////////////////

};

};

#endif
#endif
