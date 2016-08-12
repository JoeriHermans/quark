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

// Application dependencies.
#include <quark/application/constants.h>
#include <quark/http/http_util.h>

// END Includes. /////////////////////////////////////////////////////

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