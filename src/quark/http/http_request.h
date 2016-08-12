/**
 * A class which describes the properties and actions of an
 * HTTP request. In short, this class describes the properties
 * of an HTTP request.
 *
 * @date                    09 08 2016
 * @author                  Joeri HERMANS
 * @version                 0.1
 *
 * Copyright 2016 Joeri HERMANS
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

// BEGIN Includes. ///////////////////////////////////////////////////

// System dependencies.
#include <string>
#include <unordered_map>

// Application dependencies.
#include <quark/network/socket.h>
#include <quark/http/http_code.h>
#include <quark/http/http_method.h>
#include <quark/http/http_response.h>
#include <quark/http/http_util.h>

// END Includes. /////////////////////////////////////////////////////

#ifndef QUARK_HTTP_REQUEST_H_
#define QUARK_HTTP_REQUEST_H_

namespace quark {

class http_request {

    public:

    // BEGIN Class constants. ////////////////////////////////////////////////
    // END Class constants. //////////////////////////////////////////////////

    private:

    // BEGIN Private members. ////////////////////////////////////////////////

    /**
     * Describes the HTTP method of the request.
     */
    quark::http_method mHttpMethod;

    /**
     * HTTP header elements. The header values are stored in a
     * key-value fashion.
     */
    std::unordered_map<std::string, std::string> mHeader;

    /**
     * Holds the hostname of the remote server.
     */
    std::string mHost;

    /**
     * Holds the URI of the resource we are trying to access.
     */
    std::string mUri;

    // END Private members. //////////////////////////////////////////////////

    // BEGIN Private methods. ////////////////////////////////////////////////

    inline void set_http_method(const quark::http_method method);

    inline void set_host(const std::string & host);

    inline void set_uri(const std::string & uri);

    std::string build_request(void) const;

    // END Private methods. //////////////////////////////////////////////////

    protected:

    // BEGIN Protected methods. //////////////////////////////////////////////
    // END Protected methods. ////////////////////////////////////////////////

    public:

    // BEGIN Constructor. ////////////////////////////////////////////////////

    http_request(const quark::http_method method,
                 const std::string & host,
                 const std::string & uri);

    // END Constructor. //////////////////////////////////////////////////////

    // BEGIN Destructor. /////////////////////////////////////////////////////

    virtual ~http_request(void);

    // END Destructor. ///////////////////////////////////////////////////////

    // BEGIN Public methods. /////////////////////////////////////////////////

    void set_header(const std::string & key, const std::string & value);

    std::string get_header(const std::string & key) const;

    quark::http_response * execute(quark::socket * socket);

    // END Public methods. ///////////////////////////////////////////////////

    // BEGIN Public static methods. //////////////////////////////////////////
    // END Public static methods. ////////////////////////////////////////////

};

};

#endif
