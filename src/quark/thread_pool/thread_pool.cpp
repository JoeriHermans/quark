/**
 * Highly efficient threadpool with dynamic resource allocation.
 *
 * @date                    23 June 2017
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

// BEGIN Includes. /////////////////////////////////////////////////////////////

// Application dependencies.
#include <quark/thread_pool/thread_pool.h>

// System dependencies.
#include <cassert>

// END Includes. ///////////////////////////////////////////////////////////////

bool quark::thread_pool::tasks_left(void) const {
    bool not_empty;

    m_mutex_queue.lock();
    not_empty = !m_task_queue.empty();
    m_mutex_queue.unlock();

    return not_empty;
}

inline void quark::thread_pool::initialize(void) {
    m_flag_running = true;
    m_num_active_threads = 0;
    m_num_inactive_threads = 0;
}

inline void quark::thread_pool::lock_queue(void) {
    m_mutex_queue.lock();
}

inline void quark::thread_pool::unlock_queue(void) {
    m_mutex_queue.unlock();
}

quark::thread_pool_task * quark::thread_pool::next_task(void) {
    quark::thread_pool_task * task;

    m_mutex_queue.lock();
    if(m_task_queue.size() > 0) {
        task = m_task_queue.front();
        m_task_queue.pop();
    } else {
        task = nullptr;
    }
    m_mutex_queue.unlock();

    return task;
}

std::size_t quark::thread_pool::num_threads(void) const {
    return m_threads.size();
}

std::size_t quark::thread_pool::num_threads_active(void) const {
    std::size_t n;

    m_mutex_active_threads.lock();
    n = m_num_active_threads;
    m_mutex_active_threads.unlock();

    return n;
}

std::size_t quark::thread_pool::num_threads_inactive(void) const {
    std::size_t n;

    m_mutex_inactive_threads.lock();
    n = m_num_inactive_threads;
    m_mutex_inactive_threads.unlock();

    return n;
}

void quark::thread_pool::cleanup_tasks(void) {
    while(!m_task_queue.empty()) {
        delete m_task_queue.front();
        m_task_queue.pop();
    }
}

void quark::thread_pool::decrement_active_threads(void) {
    m_mutex_active_threads.lock();
    --m_num_active_threads;
    m_mutex_active_threads.unlock();
}

void quark::thread_pool::decrement_inactive_threads(void) {
    m_mutex_inactive_threads.lock();
    --m_num_inactive_threads;
    m_mutex_inactive_threads.unlock();
}

void quark::thread_pool::increment_active_threads(void) {
    m_mutex_active_threads.lock();
    ++m_num_active_threads;
    m_mutex_active_threads.unlock();
}

void quark::thread_pool::increment_inactive_threads(void) {
    m_mutex_inactive_threads.lock();
    ++m_num_inactive_threads;
    m_mutex_inactive_threads.unlock();
}

void quark::thread_pool::join(void) {
    std::thread * thread;
    std::size_t num_threads;

    // Stop the thread pool.
    stop();
    // Wait until all worker threads are done.
    num_threads = m_threads.size();
    // Notify all workers to wake-up.
    m_workers.notify_all();
    for(std::size_t i = 0; i < num_threads; ++i) {
        thread = m_threads.at(i);
        thread->join();
        delete thread;
    }
}

void quark::thread_pool::spawn_threads(const std::size_t num_threads) {
    std::thread * thread;

    // Check the precondition.
    assert(num_threads > 0);

    // Allocate the specified number of worker threads.
    for(std::size_t i = 0; i < num_threads; ++i) {
        thread = new std::thread(quark::thread_pool::process, this);
        m_threads.push_back(thread);
    }
}

bool quark::thread_pool::wakeup_required(void) const {
    std::size_t num_active;
    std::size_t num_inactive;
    std::size_t num_total;
    std::size_t num_active_not_working;
    bool wakeup;

    num_inactive = num_threads_inactive();
    num_active = num_threads_active();
    num_total = num_threads();
    num_active_not_working = num_total - num_active - num_inactive;
    wakeup = (num_active_not_working == 0);

    return wakeup;
}

quark::thread_pool::thread_pool(const std::size_t num_workers) {
    initialize();
    spawn_threads(num_workers);
}

quark::thread_pool::~thread_pool(void) {
    join();
    cleanup_tasks();
}

bool quark::thread_pool::is_running(void) const {
    return m_flag_running;
}

std::size_t quark::thread_pool::num_workers(void) const {
    return m_threads.size();
}

void quark::thread_pool::enqueue(quark::thread_pool_task * task) {
    std::size_t num_active_threads;
    std::size_t num_total_threads;

    // Checking the precondition.
    assert(task != nullptr);

    // Add the task to the queue.
    lock_queue();
    m_task_queue.push(task);
    unlock_queue();
    // Fetch the number of active, and total number of threads.
    num_active_threads = num_threads_active();
    num_total_threads = num_threads();
    // Check if a thread needs to be woken up to increase processing throughput.
    if(num_active_threads < num_total_threads && wakeup_required())
        m_workers.notify_one();
}

void quark::thread_pool::stop(void) {
    m_flag_running = false;
}

void quark::thread_pool::process(quark::thread_pool * pool) {
    std::unique_lock<std::mutex> lock(pool->m_mutex_worker);
    quark::thread_pool_task * task;

    while(pool->is_running()) {
        task = pool->next_task();
        if(task != nullptr) {
            pool->increment_active_threads();
            task->execute();
            delete task;
            pool->decrement_active_threads();
            continue;
        }
        if(!pool->tasks_left()) {
            pool->increment_inactive_threads();
            pool->m_workers.wait(lock);
            pool->decrement_inactive_threads();
        }
    }
}
