/**
 * A class which describes the features and properties of an
 * HTTP response.
 *
 * @date                    10 08 2016
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
#include <quark/http/http_code.h>

// END Includes. /////////////////////////////////////////////////////

#ifndef QUARK_HTTP_RESPONSE_H_
#define QUARK_HTTP_RESPONSE_H_

namespace quark {

class http_response {

    public:

    // BEGIN Class constants. ////////////////////////////////////////////////
    // END Class constants. //////////////////////////////////////////////////

    private:

    // BEGIN Private members. ////////////////////////////////////////////////

    /**
     * Holds the HTTP response code.
     */
    quark::http_code mResponseCode;

    /**
     * Holds the unordered map from the HTTP response.
     */
    std::unordered_map<std::string, std::string> mHeader;

    /**
     * Holds the body of the HTTP response.
     */
    std::string mBody;

    // END Private members. //////////////////////////////////////////////////

    // BEGIN Private methods. ////////////////////////////////////////////////

    inline void set_http_code(const quark::http_code code);

    inline void set_header(const std::unordered_map<std::string, std::string> & header);

    inline void set_body(const std::string & body);

    // END Private methods. //////////////////////////////////////////////////

    protected:

    // BEGIN Protected methods. //////////////////////////////////////////////
    // END Protected methods. ////////////////////////////////////////////////

    public:

    // BEGIN Constructor. ////////////////////////////////////////////////////

    http_response(const quark::http_code code,
                  const std::unordered_map<std::string, std::string> & header,
                  const std::string & body);

    // END Constructor. //////////////////////////////////////////////////////

    // BEGIN Destructor. /////////////////////////////////////////////////////

    virtual ~http_response(void) = default;

    // END Destructor. ///////////////////////////////////////////////////////

    // BEGIN Public methods. /////////////////////////////////////////////////

    quark::http_code get_response_code(void) const;

    bool has_header(const std::string & key) const;

    std::size_t header_size(void) const;

    const std::string & get_header(const std::string & key) const;

    const std::string & get_body(void) const;

    bool has_body(void) const;

    // END Public methods. ///////////////////////////////////////////////////

    // BEGIN Public static methods. //////////////////////////////////////////
    // END Public static methods. ////////////////////////////////////////////

};

};

#endif
