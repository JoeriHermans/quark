/**
 * Abstract class defining the interface of the reader, and general behaviour.
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

#ifndef QUARK_READER_H_
#define QUARK_READER_H_

// BEGIN Dependencies. /////////////////////////////////////////////////////////

// Application dependencies.
#include <quark/types.h>

// System Dependencies.
#include <cstddef>
#include <mutex>

// END Dependencies. ///////////////////////////////////////////////////////////

namespace quark {

class reader {

    public:

    // BEGIN Class constants. //////////////////////////////////////////////////
    // END Class constants. ////////////////////////////////////////////////////

    private:

    // BEGIN Private members. //////////////////////////////////////////////////

    /**
     * Mutex which is responsible for locking the reader during asynchronous
     * operations.
     */
    std::mutex m_lock;

    // END Private members. ////////////////////////////////////////////////////

    // BEGIN Private methods. //////////////////////////////////////////////////
    // END Private methods. ////////////////////////////////////////////////////

    protected:

    // BEGIN Protected methods. ////////////////////////////////////////////////
    // END Protected methods. //////////////////////////////////////////////////

    public:

    // BEGIN Constructor. //////////////////////////////////////////////////////

    reader(void) = default;

    // END Constructor. ////////////////////////////////////////////////////////

    // BEGIN Destructor. ///////////////////////////////////////////////////////

    virtual ~reader(void) = default;

    // END Destructor. /////////////////////////////////////////////////////////

    // BEGIN Public methods. ///////////////////////////////////////////////////

    virtual std::ssize_t read_all(char * buffer, const std::size_t size) = 0;

    virtual std::ssize_t read_byte(char * byte) = 0;

    virtual std::ssize_t read_bytes(char * buffer, const std::size_t size) = 0;

    virtual void close_reader(void) = 0;

    virtual void lock(void) {
        m_lock.lock();
    }

    virtual void unlock(void) {
        m_lock.unlock();
    }

    // END Public methods. /////////////////////////////////////////////////////

    // BEGIN Public static methods. ////////////////////////////////////////////
    // END Public static methods. //////////////////////////////////////////////

};

};

#endif
