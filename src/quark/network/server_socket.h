/**
 * Abstract class which defines the properties of a listening socket.
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

#ifndef QUARK_SERVER_SOCKET_H_
#define QUARK_SERVER_SOCKET_H_

// BEGIN Dependencies. /////////////////////////////////////////////////////////

// Application dependencies.
#include <quark/network/socket.h>

// System dependencies.
#include <cassert>
#include <ctime>

// END Dependencies. ///////////////////////////////////////////////////////////

namespace quark {

class server_socket {

    public:

    // BEGIN Class constants. //////////////////////////////////////////////////
    // END Class constants. ////////////////////////////////////////////////////

    private:

    // BEGIN Private members. //////////////////////////////////////////////////

    /**
     * Holds the port which is currently assigned to the listening socket.
     */
    std::uint16_t m_port;

    // END Private members. ////////////////////////////////////////////////////

    // BEGIN Private methods. //////////////////////////////////////////////////
    // END Private methods. ////////////////////////////////////////////////////

    protected:

    // BEGIN Protected methods. ////////////////////////////////////////////////

    inline void set_port(const std::uint16_t port) {
        // Checking the precondition.
        assert(port > 0);

        m_port = port;
    }

    // END Protected methods. //////////////////////////////////////////////////

    public:

    // BEGIN Constructor. //////////////////////////////////////////////////////

    server_socket(void) = default;

    server_socket(const std::uint16_t port) {
        set_port(port);
    }

    // END Constructor. ////////////////////////////////////////////////////////

    // BEGIN Destructor. ///////////////////////////////////////////////////////

    virtual ~server_socket(void) = default;

    // END Destructor. /////////////////////////////////////////////////////////

    // BEGIN Public methods. ///////////////////////////////////////////////////

    std::uint16_t get_port(void) const {
        return m_port;
    }

    virtual bool bind_to_port(void) = 0;

    virtual bool is_bound(void) const = 0;

    virtual quark::socket * accept_socket(const std::time_t seconds) = 0;

    virtual quark::socket * accept_socket(void) = 0;

    virtual void stop_listening(void) = 0;

    // END Public methods. /////////////////////////////////////////////////////

    // BEGIN Public static methods. ////////////////////////////////////////////
    // END Public static methods. //////////////////////////////////////////////

};

};

#endif
