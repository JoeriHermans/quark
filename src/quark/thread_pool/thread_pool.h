/**
 * TODO
 *
 * @date                    TODO
 * @author                  Joeri R. HERMANS
 * @version                 0.1
 *
 * Copyright 2016 Joeri R. HERMANS
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

#ifndef QUARK_THREADPOOL_H_
#define QUARK_THREADPOOL_H_

// BEGIN Includes. /////////////////////////////////////////////////////////////

// Application dependencies.

// System dependencies.
#include <vector>
#include <condition_variable>
#include <thread>
#include <mutex>
#include <queue>

// END Includes. ///////////////////////////////////////////////////////////////

namespace quark {

class threadpool {

    public:

    // BEGIN Class constants. //////////////////////////////////////////////////
    // END Class constants. ////////////////////////////////////////////////////

    private:

    // BEGIN Private members. //////////////////////////////////////////////////

    /**
     * Flag which indicates whether the threadpool is allowed to continue.
     *
     * @note By default, this member if true.
     */
    bool m_running;

    std::condition_variable m_task_load;

    std::mutex m_mutes_sleeping_threads;

    std::mutex m_mutex_queue;

    std::mutex m_mutex_thread_lock;

    std::mutex m_mutex_working_threads;

    std::queue<quark::threadpool_task> m_task_queue;

    /**
     * Holds the number of sleeping (inactive) threads.
     *
     * @note 0 by default.
     */
    std::size_t m_num_inactive_threads;

    /**
     * Holds the number of active (working) threads.
     *
     * @note 0 by default.
     */
    std::size_t m_num_active_threads;

    std::vector<std::thread> m_threads;

    // END Private members. ////////////////////////////////////////////////////

    // BEGIN Private methods. //////////////////////////////////////////////////

    inline void initialize(void);

    // END Private methods. ////////////////////////////////////////////////////

    protected:

    // BEGIN Protected methods. ////////////////////////////////////////////////
    // END Protected methods. //////////////////////////////////////////////////

    public:

    // BEGIN Constructor. //////////////////////////////////////////////////////

    threadpool(const std::size_t num_threads);

    // END Constructor. ////////////////////////////////////////////////////////

    // BEGIN Destructor. ///////////////////////////////////////////////////////

    virtual ~threadpool(void);

    // END Destructor. /////////////////////////////////////////////////////////

    // BEGIN Public methods. ///////////////////////////////////////////////////

    bool is_running(void) const;

    std::size_t num_threads(void) const;

    void enqueue(quark::threadpool_task & task);

    void stop(void);

    // END Public methods. /////////////////////////////////////////////////////

    // BEGIN Public static methods. ////////////////////////////////////////////
    // END Public static methods. //////////////////////////////////////////////

};

};

#endif
