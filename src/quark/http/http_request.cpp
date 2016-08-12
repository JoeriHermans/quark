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
#include <cassert>

// Application dependencies.
#include <quark/http/http_request.h>

// END Includes. /////////////////////////////////////////////////////

inline void quark::http_request::set_http_method(const quark::http_method method) {
    mHttpMethod = method;
}

inline void quark::http_request::set_host(const std::string & host) {
    // Checking the precondition.
    assert(!host.empty());

    mHost = host;
}

inline void quark::http_request::set_uri(const std::string & uri) {
    // Checking the precondition.
    assert(!uri.empty());

    mUri = uri;
}

quark::http_request::http_request(const quark::http_method method,
                                  const std::string & host,
                                  const std::string & uri) {
    set_http_method(method);
    set_host(host);
    set_uri(uri);
}

quark::http_request::~http_request(void) {
    // Clear the header.
    mHeader.clear();
}

void quark::http_request::set_header(const std::string & key,
                                     const std::string & value) {
    // Checking the precondition.
    assert(!key.empty() && !value.empty());

    mHeader[key] = value;
}

std::string quark::http_request::get_header(const std::string & key) const {
    std::string value;

    auto it = mHeader.find(key);
    if(it != mHeader.end())
        value = it->second;

    return value;
}

quark::http_response * quark::http_request::execute(quark::socket * socket) {
    quark::http_response * response = nullptr;

    // Checking the precondition.
    assert(socket != nullptr);

    return response;
}
