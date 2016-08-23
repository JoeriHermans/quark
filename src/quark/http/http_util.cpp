/**
 * A set of utility methods designed to help Quark's HTTP submodole
 * with handling remote HTTP connections and REST API requests.
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
#include <cstring>
#include <vector>
#include <sstream>
#include <iostream>

// Application dependencies.
#include <quark/application/constants.h>
#include <quark/http/http_util.h>
#include <quark/util/util.h>

// END Includes. /////////////////////////////////////////////////////

quark::http_code quark::parse_http_code(const std::string & s) {
    quark::http_code code;
    std::size_t pos;

    // Find the end of the protocol.
    pos = s.find(" ") + 1;
    // Find the status code.
    std::string statusCode = s.substr(pos, s.find(" ", pos) - pos);
    code = static_cast<quark::http_code>(std::stoi(statusCode));

    return code;
}

std::string quark::http_method_to_string(const quark::http_method method) {
    std::string str;

    switch(method) {
    case quark::http_method::GET:
        str = kHttpMethodGet;
        break;
    case quark::http_method::POST:
        str = kHttpMethodPost;
        break;
    case quark::http_method::DELETE:
        str = kHttpMethodDelete;
        break;
    default:
        str = kHttpMethodUnknown;
        break;
    }

    return str;
}

std::pair<std::string, std::string> quark::split_response(const std::string & s) {
    const static std::size_t delimiterLength = strlen(kHttpSeparator);
    std::pair<std::string, std::string> tuple;
    std::string token;
    std::string header;
    std::size_t ppos;
    std::size_t pos;

    ppos = pos = 0;
    while((pos = s.find(kHttpSeparator, ppos)) != std::string::npos) {
        token = s.substr(ppos, pos - ppos);
        // Check if the specified token is empty, this means we reached the body.
        if(token.empty()) {
            pos += delimiterLength;
            break;
        }
        header += token + kHttpSeparator;
        ppos = pos + delimiterLength;
    }
    // Check if pos is not a position.
    if(pos == std::string::npos)
        pos = 0;
    tuple.first = header;
    tuple.second = s.substr(pos, s.length() - pos);

    return tuple;
}
