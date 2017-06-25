/**
 * Networking utility methods.
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

#ifndef QUARK_NETWORK_UTIL_H_
#define QUARK_NETWORK_UTIL_H_

// BEGIN Dependencies. /////////////////////////////////////////////////////////

// System dependencies.
#include <string>

// END Dependencies. ///////////////////////////////////////////////////////////

namespace quark {

    int connect(const std::string & address, const std::uint16_t port);

    bool disable_cork(const int fd);

    bool enable_cork(const int fd);

    bool disable_keep_alive(const int fd);

    bool enable_keep_alive(const int fd);

    bool disable_nagle(const int fd);

    bool enable_nagle(const int fd);

};

#endif
