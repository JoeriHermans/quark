/**
 * Utility functions used in the startup process of QUARK. This will
 * initialise all crypographic libraries and start the application
 * requested by the user.
 *
 * @date                    28 04 2016
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
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <openssl/conf.h>
#include <openssl/engine.h>
#include <openssl/bio.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

// Application dependencies.
#include <quark/main.h>
#include <quark/application/constants.h>
#include <quark/logger/logger.h>
#include <quark/logger/console/console_logger.h>
#include <quark/util/util.h>

// END Includes. /////////////////////////////////////////////////////

// BEGIN Tests. //////////////////////////////////////////////////////

// Test dependencies.
#include <quark/http/http_request.h>
#include <quark/http/http_response.h>
#include <quark/network/socket.h>
#include <quark/network/posix/posix_tcp_socket.h>

void execute_tests(void) {
    quark::http_request request(quark::http_method::GET, "joerihermans.com", "/");
    quark::http_response * response;
    quark::posix_tcp_socket socket;

    if(socket.create_connection("joerihermans.com", 80)) {
        response = request.execute(&socket);
        std::cout << "Number of header elements: " << response->header_size() << std::endl;
        std::cout << response->get_body() << std::endl;
        delete response;
        socket.close_connection();
    } else {
        std::cout << "Could not create connection." << std::endl;
    }
}

// END Tests. ////////////////////////////////////////////////////////

int main(const int argc, const char ** argv) {
    // Initialize dependencies.
    initialize_random_number_generator();
    initialize_ssl();
    // TODO Initialize and start application.
    execute_tests();
    // Do some cleanup.
    cleanup_logger();
    cleanup_ssl();

    return EXIT_SUCCESS;
}

void initialize_random_number_generator(void) {
    srand(static_cast<unsigned int>(time(0)));
}

void initialize_ssl(void) {
    SSL_load_error_strings();
    SSL_library_init();
    OpenSSL_add_all_algorithms();
}

void cleanup_logger(void) {
    quark::logger::flush();
    quark::logger::cleanup();
}

void cleanup_ssl(void) {
    CONF_modules_free();
    ERR_remove_state(0);
    ENGINE_cleanup();
    CONF_modules_unload(1);
    ERR_free_strings();
    EVP_cleanup();
    CRYPTO_cleanup_all_ex_data();
}
