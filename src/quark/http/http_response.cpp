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
#include <cassert>

// Application dependencies.
#include <quark/http/http_response.h>

// END Includes. /////////////////////////////////////////////////////

inline void quark::http_response::set_http_code(const quark::http_code code) {
    mResponseCode = code;
}

inline void quark::http_response::set_header(const std::unordered_map<std::string, std::string> & header) {
    mHeader = header;
}

inline void quark::http_response::set_body(const std::string & body) {
    mBody = body;
}

quark::http_response::http_response(const quark::http_code code,
                                    const std::unordered_map<std::string, std::string> & header,
                                    const std::string & body) {
    set_http_code(code);
    set_header(header);
    set_body(body);
}

quark::http_code quark::http_response::get_response_code(void) const {
    return mResponseCode;
}

bool quark::http_response::has_header(const std::string & key) const {
    auto it = mHeader.find(key);

    return it != mHeader.end();
}

const std::string & quark::http_response::get_header(const std::string & key) const {
    auto it = mHeader.find(key);

    return it->second;
}

const std::string & quark::http_response::get_body(void) const {
    return mBody;
}

bool quark::http_response::has_body(void) const {
    return !mBody.empty();
}
