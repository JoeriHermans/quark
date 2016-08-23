/**
 * A list of all global constants in QUARK.
 *
 * @date                    24 05 2016
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
#include <cstdio>

// Application dependencies.
#include <quark/application/constants.h>

// END Includes. /////////////////////////////////////////////////////

// BEGIN Utility characters. /////////////////////////////////////////

const char kTrimCharacters[] = " \t\n\r";

const char kHttpSeparator[] = "\r\n";
const char kHttpMethodDelete[] = "DELETE";
const char kHttpMethodGet[] = "GET";
const char kHttpMethodPost[] = "POST";
const char kHttpMethodUnknown[] = "UNKNOWN";

const char kHttpHeaderContentLength[] = "Content-length";
const char kHttpHeaderCacheControl[] = "Cache-Control";
const char kHttpHeaderNoCache[] = "no-cache";
const char kHttpHeaderConnection[] = "Connection";
const char kHttpHeaderClose[] = "close";
const char kHttpHeaderKeepAlive[] = "keep-alive";
const char kHttpHeaderAccept[] = "Accept";
const char kHttpHeaderKeyValueSeparator[] = ":";

const char kMimeTextPlain[] = "text/plain";
const char kMimeTextHtml[] = "text/html";
const char kMimeTextJson[] = "text/json";
const char kMimeAll[] = "*/*";

// END Utility characters. ///////////////////////////////////////////
