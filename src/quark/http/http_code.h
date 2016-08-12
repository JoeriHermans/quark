/**
 * Enumeration which describes the different HTTP return codes in
 * a human readable way.
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
// END Includes. /////////////////////////////////////////////////////

#ifndef QUARK_HTTP_CODE_H_
#define QUARK_HTTP_CODE_H_

namespace quark {

    enum http_code {
        HTTP_OK                = 200,
        HTTP_FROBIDDEN         = 403,
        HTTP_NOT_FOUND         = 404,
        HTTP_INTERNAL_ERROR    = 500
    };

};

#endif
