/**
 * Highly efficient threadpool with dynamic resource allocation.
 *
 * @date                    23 June 2017
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

#ifndef QUARK_THREAD_POOL_H_
#define QUARK_THREAD_POOL_H_

// BEGIN Dependencies. /////////////////////////////////////////////////////////

// Application dependencies.
#include <quark/thread_pool/thread_pool_task.h>

// System dependencies.
#include <vector>
#include <condition_variable>
#include <thread>
#include <mutex>
#include <queue>

// END Dependencies. ///////////////////////////////////////////////////////////

namespace quark {

class thread_pool {

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
    bool m_flag_running;

    /**
     * Condition variable for waking up inactive threads.
     */
    std::condition_variable m_workers;

    /**
     * Mutex for accessing the inactive threads registry.
     */
    mutable std::mutex m_mutex_active_threads;

    /**
     * Mutex for accessing the task queue.
     */
    mutable std::mutex m_mutex_queue;

    /**
     * Mutex for accessing the active threads registry.
     */
    mutable std::mutex m_mutex_inactive_threads;

    /**
     * Mutable assigned to a thread pool worker.
     */
    mutable std::mutex m_mutex_worker;

    /**
     * Threadpool task queue.
     */
    std::queue<quark::thread_pool_task *> m_task_queue;

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

    /**
     * Thread registry.
     */
    std::vector<std::thread *> m_threads;

    // END Private members. ////////////////////////////////////////////////////

    // BEGIN Private methods. //////////////////////////////////////////////////

    bool tasks_left(void) const;

    inline void initialize(void);

    inline void lock_queue(void);

    inline void unlock_queue(void);

    quark::thread_pool_task * next_task(void);

    std::size_t num_threads(void) const;

    std::size_t num_threads_active(void) const;

    std::size_t num_threads_inactive(void) const;

    void cleanup_tasks(void);

    void decrement_active_threads(void);

    void decrement_inactive_threads(void);

    void increment_active_threads(void);

    void increment_inactive_threads(void);

    void join(void);

    void spawn_threads(const std::size_t num_threads);

    bool wakeup_required(void) const;

    // END Private methods. ////////////////////////////////////////////////////

    protected:

    // BEGIN Protected methods. ////////////////////////////////////////////////
    // END Protected methods. //////////////////////////////////////////////////

    public:

    // BEGIN Constructor. //////////////////////////////////////////////////////

    thread_pool(const std::size_t num_workers);

    // END Constructor. ////////////////////////////////////////////////////////

    // BEGIN Destructor. ///////////////////////////////////////////////////////

    virtual ~thread_pool(void);

    // END Destructor. /////////////////////////////////////////////////////////

    // BEGIN Public methods. ///////////////////////////////////////////////////

    bool is_running(void) const;

    std::size_t num_workers(void) const;

    void enqueue(quark::thread_pool_task * task);

    void stop(void);

    // END Public methods. /////////////////////////////////////////////////////

    // BEGIN Public static methods. ////////////////////////////////////////////

    static void process(quark::thread_pool * thread_pool);

    // END Public static methods. //////////////////////////////////////////////

};

};

#endif
