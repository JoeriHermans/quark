/**
 * Class describing the properties, and actions of an observable.
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

#ifndef QUARK_OBSERVABLE_H_
#define QUARK_OBSERVABLE_H_

// BEGIN Dependencies. /////////////////////////////////////////////////////////

// Application dependencies.
#include <quark/util/observer.h>

// System dependencies.
#include <mutex>
#include <vector>

// END Dependencies. ///////////////////////////////////////////////////////////

namespace quark {

class observable {

    public:

    // BEGIN Class constants. //////////////////////////////////////////////////
    // END Class constants. ////////////////////////////////////////////////////

    private:

    // BEGIN Private members. //////////////////////////////////////////////////

    /**
     * Holds list of observers subscribed to this object.
     */
    std::vector<quark::observer *> m_observers;

    /**
     * Mutex for synchronizing observer list.
     */
    mutable std::mutex m_mutex_observers;

    // END Private members. ////////////////////////////////////////////////////

    // BEGIN Private methods. //////////////////////////////////////////////////
    // END Private methods. ////////////////////////////////////////////////////

    protected:

    // BEGIN Protected methods. ////////////////////////////////////////////////
    // END Protected methods. //////////////////////////////////////////////////

    public:

    // BEGIN Constructor. //////////////////////////////////////////////////////

    observable(void) = default;

    // END Constructor. ////////////////////////////////////////////////////////

    // BEGIN Destructor. ///////////////////////////////////////////////////////

    virtual ~observable(void) = default;

    // END Destructor. /////////////////////////////////////////////////////////

    // BEGIN Public methods. ///////////////////////////////////////////////////

    bool contains_observer(const quark::observer * observer) const;

    void add_observer(quark::observer * observer);

    void notify_obsevers(void * argument);

    void notify_obsevers(void);

    void remove_observer(const quark::observer * observer);

    void remove_observers(void);

    // END Public methods. /////////////////////////////////////////////////////

    // BEGIN Public static methods. ////////////////////////////////////////////
    // END Public static methods. //////////////////////////////////////////////

};

};

#endif
