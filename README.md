# quark

Quark is boilerplate for C++ applications. It provides several core functionalities including asynchronous (secure) networking, threadpooling, message channeling, IO, and logging.

## Building your application

Before actually building your application. One should modify the makefile in order to fit your needs. This includes the name of the output binary (defined in APPLICATION_NAME), the compiler, linker, compiler flags and linker flags.

After all these have been configured, just run `make all`, and the compiled binary will be available in the `bin` folder.

### Modifying your compiler
By default, quark makes use of the `g++` compiler. However, it is not a problem if you would like to change to `clang`. One just needs to modify the CC, and LD variable.
