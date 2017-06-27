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

// BEGIN Dependencies. /////////////////////////////////////////////////////////

// Application dependencies.
#include <quark/util/observable.h>

// System dependencies.
#include <algorithm>
#include <cassert>

// END Dependencies. ///////////////////////////////////////////////////////////

bool quark::observable::contains_observer(const quark::observer * observer) const {
    bool found;

    // Checking the precondition.
    assert(observer != nullptr);

    m_mutex_observers.lock();
    found = std::find(m_observers.begin(), m_observers.end(), observer) != m_observers.end();
    m_mutex_observers.unlock();

    return found;
}

void quark::observable::add_observer(quark::observer * observer) {
    // Checking the precondition.
    assert(observer != nullptr && !contains_observer(observer));

    m_mutex_observers.lock();
    m_observers.push_back(observer);
    m_mutex_observers.unlock();
}

void quark::observable::notify_obsevers(void * argument) {
    m_mutex_observers.lock();
    for(auto it = m_observers.begin(); it != m_observers.end(); ++it)
        (*it)->update(argument);
    m_mutex_observers.unlock();
}

void quark::observable::notify_obsevers(void) {
    m_mutex_observers.lock();
    for(auto it = m_observers.begin(); it != m_observers.end(); ++it)
        (*it)->update();
    m_mutex_observers.unlock();
}

void quark::observable::remove_observer(const quark::observer * observer) {
    // Checking the precondition.
    assert(observer != nullptr && contains_observer(observer));

    m_mutex_observers.lock();
    m_observers.erase(std::find(m_observers.begin(), m_observers.end(), observer));
    m_mutex_observers.unlock();
}

void quark::observable::remove_observers(void) {
    // Checking the precondition.
    assert(!m_observers.empty());

    m_mutex_observers.lock();
    m_observers.clear();
    m_mutex_observers.unlock();
}
