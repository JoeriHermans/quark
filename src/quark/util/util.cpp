/**
 * General utility functions which can be used throughout an
 * application.
 *
 * @date                    28 June 2017
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

// BEGIN Dependencies. /////////////////////////////////////////////////////////

// Application dependencies.
#include <quark/util/util.h>

// System dependencies.
#include <cassert>
#include <cstring>
#include <sys/stat.h>

// END Dependencies. ///////////////////////////////////////////////////////////

bool quark::file_exists(const std::string & path) {
    struct stat buffer;

    // Checking the precondition.
    assert(!path.empty());

    if(stat(path.c_str(), &buffer) != -1)
        return true;

    return false;
}

bool quark::flag_specified(const int argc, const char ** argv, const char * flag) {
    bool specified;

    // Checking the precondition.
    assert(argc > 0 && argv != nullptr && flag != nullptr);

    specified = false;
    for(int i = 0; i < argc; ++i) {
        if(strcmp(argv[i], flag) == 0) {
            specified = true;
            break;
        }
    }

    return specified;
}

int quark::flag_index(const int argc, const char ** argv, const char * flag) {
    int index;

    // Checking the precondition.
    assert(argc > 0 && argv != nullptr && flag != nullptr);

    index = -1;
    for(int i = 0; i < argc; ++i) {
        if(strcmp(argv[i], flag) == 0) {
            index = i;
            break;
        }
    }

    return index;
}
