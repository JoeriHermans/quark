/**
 * A class which describes the properties and actions of an
 * HTTP request. In short, this class describes the properties
 * of an HTTP request.
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

// System dependencies.
#include <cassert>
#include <cstring>
#include <string>
#include <iostream>

// Application dependencies.
#include <quark/application/constants.h>
#include <quark/network/socket.h>
#include <quark/http/http_request.h>
#include <quark/http/http_util.h>
#include <quark/util/util.h>
#include <quark/http/http_util.h>

// END Includes. /////////////////////////////////////////////////////

inline void quark::http_request::set_http_method(const quark::http_method method) {
    mHttpMethod = method;
}

inline void quark::http_request::set_host(const std::string & host) {
    // Checking the precondition.
    assert(!host.empty());

    mHost = host;
}

inline void quark::http_request::set_uri(const std::string & uri) {
    // Checking the precondition.
    assert(!uri.empty());

    mUri = uri;
}

inline void quark::http_request::set_body(const std::string & body) {
    set_header(kHttpHeaderContentLength, std::to_string(body.length()));
    mBody = body;
}

void quark::http_request::add_default_headers(void) {
    set_header(kHttpHeaderConnection, kHttpHeaderClose);
    set_header(kHttpHeaderCacheControl, kHttpHeaderNoCache);
    set_header(kHttpHeaderAccept, kMimeAll);
}

quark::http_response * quark::http_request::build_response(const std::string & data) const {
    std::unordered_map<std::string, std::string> headerMap;
    std::vector<std::string> headerRows;
    quark::http_response * response;
    quark::http_code httpCode = HTTP_UNKNOWN;

    // Check if valid data has been specified.
    if(data.empty())
        return nullptr;

    std::pair<std::string, std::string> responseParts = quark::split_response(data);
    std::string header = responseParts.first;
    std::string body = responseParts.second;
    // Check if header data is available.
    if(!header.empty()) {
        headerRows = quark::split(header, kHttpSeparator);
        // Fetch the HTTP code from the first line of the header.
        httpCode = quark::parse_http_code(*headerRows.begin());
        // Parse the rest of the header rows.
        for(auto it = headerRows.begin() + 1; it != headerRows.end(); ++it) {
            std::pair<std::string, std::string> headerRow;

            headerRow = quark::split_pair(*it, kHttpHeaderKeyValueSeparator);
            std::string k = headerRow.first;
            std::string v = headerRow.second;
            quark::trim(k);
            quark::trim(v);
            headerMap[k] = v;
        }
    }
    // Allocate a new response instance.
    response = new quark::http_response(httpCode, headerMap, body);

    return response;
}

quark::http_response * quark::http_request::fetch_response(quark::socket * socket) const {
    quark::http_response * response;
    quark::reader * reader = socket->get_reader();
    bool allReceived = false;
    char buffer[BUFSIZ + 1];
    std::string data;

    // Checking the precondition.
    assert(socket != nullptr && reader != nullptr);

    reader->lock();
    while(!allReceived && socket->is_connected()) {
        std::size_t n = reader->read_bytes(buffer, BUFSIZ);
        buffer[n] = 0;

        if(n != 0)
            data += buffer;
        else
            allReceived = true;
    }
    reader->unlock();
    response = build_response(data);

    return response;
}

std::string quark::http_request::build_request(void) const {
    std::string request;

    request = http_method_to_string(mHttpMethod);
    request += " " + mUri + "\r\n";
    // Add all headers to the request.
    for(auto it = mHeader.begin(); it != mHeader.end(); ++it)
        request += it->first + ": " + it->second + "\r\n";
    // Append the body seperator and body.
    request += "\r\n\r\n" + mBody;

    return request;
}

quark::http_request::http_request(const quark::http_method method,
                                  const std::string & host,
                                  const std::string & uri) {
    set_http_method(method);
    add_default_headers();
    set_host(host);
    set_uri(uri);
    set_body("");
}

quark::http_request::http_request(const quark::http_method method,
                                  const std::string & host,
                                  const std::string & uri,
                                  const std::string & body) {
    set_http_method(method);
    add_default_headers();
    set_host(host);
    set_uri(uri);
    set_body(body);
}

quark::http_request::~http_request(void) {
    // Clear the header.
    mHeader.clear();
}

void quark::http_request::set_header(const std::string & key,
                                     const std::string & value) {
    // Checking the precondition.
    assert(!key.empty() && !value.empty());

    mHeader[key] = value;
}

std::string quark::http_request::get_header(const std::string & key) const {
    std::string value;

    auto it = mHeader.find(key);
    if(it != mHeader.end())
        value = it->second;

    return value;
}

quark::http_response * quark::http_request::execute(quark::socket * socket) {
    quark::http_response * response;
    quark::writer * writer;

    // Checking the precondition.
    assert(socket != nullptr && socket->is_connected());

    // Write the HTTP request to the remote host.
    writer = socket->get_writer();
    const std::string & request = build_request();
    writer->write_all(request.c_str(), request.length());
    response = fetch_response(socket);

    return response;
}
