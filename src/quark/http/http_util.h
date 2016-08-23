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
#include <string>
#include <vector>
#include <utility>

// Application dependencies.
#include <quark/http/http_code.h>
#include <quark/http/http_method.h>

// END Includes. /////////////////////////////////////////////////////

#ifndef QUARK_HTTP_UTIL_H_
#define QUARK_HTTP_UTIL_H_

namespace quark {

quark::http_code parse_http_code(const std::string & s);

std::string http_method_to_string(const quark::http_method method);

std::pair<std::string, std::string> split_response(const std::string & s);

};

#endif
