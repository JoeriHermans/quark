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
#ifndef QUARK_POSIX_TCP_SERVER_SOCKET_H_
#define QUARK_POSIX_TCP_SERVER_SOCKET_H_

// BEGIN Includes. /////////////////////////////////////////////////////////////

// Application dependencies.
#include <quark/network/server_socket.h>

// END Includes. ///////////////////////////////////////////////////////////////

namespace quark {

class posix_tcp_server_socket : public server_socket {

    public:

    // BEGIN Class constants. //////////////////////////////////////////////////
    // END Class constants. ////////////////////////////////////////////////////

    private:

    // BEGIN Private members. //////////////////////////////////////////////////

    /**
     * Holds the file descriptor of the listening socket.
     */
    int m_file_descriptor;

    // END Private members. ////////////////////////////////////////////////////

    // BEGIN Private methods. //////////////////////////////////////////////////

    inline void initialize(void);

    inline void set_file_descriptor(const int fd);

    // END Private methods. ////////////////////////////////////////////////////

    protected:

    // BEGIN Protected methods. ////////////////////////////////////////////////
    // END Protected methods. //////////////////////////////////////////////////

    public:

    // BEGIN Constructor. //////////////////////////////////////////////////////

    posix_tcp_server_socket(const std::uint16_t port);

    // END Constructor. ////////////////////////////////////////////////////////

    // BEGIN Destructor. ///////////////////////////////////////////////////////

    virtual ~posix_tcp_server_socket(void);

    // END Destructor. /////////////////////////////////////////////////////////

    // BEGIN Public methods. ///////////////////////////////////////////////////

    virtual bool bind_to_port(void);

    virtual bool is_bound(void) const;

    virtual quark::socket * accept_socket(const std::time_t seconds);

    virtual quark::socket * accept_socket(void);

    virtual void stop_listening(void);

    // END Public methods. /////////////////////////////////////////////////////

    // BEGIN Public static methods. ////////////////////////////////////////////
    // END Public static methods. //////////////////////////////////////////////

};

};

#endif
#endif
