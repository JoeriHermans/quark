/**
 * Set of general utility functions which can be used throughout the
 * application.
 *
 * @date                    02 05 2016
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
#include <algorithm>
#include <cassert>
#include <cctype>
#include <cstring>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <locale>
#include <openssl/sha.h>
#include <sstream>
#include <sys/stat.h>
#include <vector>

// Application dependencies.
#include <quark/application/constants.h>
#include <quark/logger/logger.h>
#include <quark/util/util.h>

// END Includes. /////////////////////////////////////////////////////

namespace quark {

    // BEGIN Globals. ////////////////////////////////////////////////

    std::string gSaltPre;
    std::string gSaltPost;

    // END Globals. //////////////////////////////////////////////////

    bool flag_specified(const int argc, const char ** argv, const char * flag) {
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

    bool file_exists(const std::string & path) {
        struct stat buffer;

        if(stat(path.c_str(), &buffer) != -1)
            return true;

        return false;
    }

    int flag_index(const int argc, const char ** argv, const char * flag) {
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

    bool read_configuration_file(const std::string & path,
                                 std::unordered_map<std::string, std::string> & c) {
        std::ifstream file(path);
        std::string line;
        std::string key;
        std::string value;
        std::size_t i;

        // Checking the precondition.
        assert(!path.empty());

        if(!quark::file_exists(path)) {
            loge("Could not open configuration file at " + path);
            return false;
        }
        logi("Reading configuration file at " + path);
        while(std::getline(file, line)) {
            quark::trim(line);
            if(line.empty() || line.at(0) == '#')
                continue;
            i = line.find('=');
            key = line.substr(0, i);
            value = line.substr(i + 1, line.length());
            trim(key); trim(value);
            if(!key.empty() && !value.empty())
                c[key] = value;
        }
        file.close();
        logi("Configuration file has been read.");

        return true;
    }

    void trim(std::string & s) {
        s.erase(0, s.find_first_not_of(kTrimCharacters));
        s.erase(s.find_last_not_of(kTrimCharacters) + 1);
    }

    std::string sha256(const std::string & str,
                       const std::string & presalt,
                       const std::string & postsalt) {
        unsigned char hash[SHA256_DIGEST_LENGTH];
        char nhash[65];
        std::string hashed;
        std::string toHash;

        toHash = presalt + str + postsalt;
        SHA256_CTX sha256;
        SHA256_Init(&sha256);
        SHA256_Update(&sha256, toHash.c_str(), toHash.length());
        SHA256_Final(hash, &sha256);
        for(int i = 0; i < SHA256_DIGEST_LENGTH; ++i)
            sprintf(nhash + (i * 2), "%02x", hash[i]);
        nhash[64] = 0;
        hashed = nhash;

        return hashed;
    }

    std::string sha256(const std::string & str) {
        return sha256(str, "", "");
    }

};
