cmake_minimum_required(VERSION 3.12)

set(CPPM_VERSION 0.0.12)
include(cmake/cppm_loader.cmake)
cppm_project()
include(HunterGate)
HunterGate(
   URL https://github.com/cpp-pm/hunter/archive/v0.23.269.tar.gz
   SHA1 64024b7b95b4c86d50ae05b926814448c93a70a0
)
project(jogyu VERSION 0.0.1 LANGUAGES C CXX)
cppm_setting()
cppm_cxx_standard(17)
cppm_compiler_option(DEFAULT)

find_cppkg(OpenSSL git  MODULE ${OPENSSL_LIBRARY} TYPE lib)
find_cppkg(asio latest  MODULE asio::asio_shared HUNTER TYPE lib)
find_cppkg(fmt 7.0.3  MODULE fmt::fmt TYPE lib)
find_cppkg(mariadbclientpp git  MODULE mariadbclientpp::mariadbclientpp TYPE lib)
find_cppkg(range-v3 0.11.0  MODULE range-v3::range-v3 TYPE lib)


cppm_target_define(client BINARY
SOURCES
    src/client/main.cpp
    src/db/connector.hpp
    src/db/connector.cpp
    src/secure/hash.hpp
    src/secure/crypt.h
    src/secure/crypt.cc
)

cppm_target_define(server BINARY
SOURCES
    src/server/server.hpp
    src/server/main.cpp
    src/db/connector.hpp
    src/db/connector.cpp
    src/secure/hash.hpp
    src/secure/crypt.h
    src/secure/crypt.cc
)


set(global_deps PUBLIC OpenSSL asio fmt mariadbclientpp range-v3)
cppm_target_dependencies(client
   ${global_deps})

cppm_target_dependencies(server
   ${global_deps})


cppm_target_install(client)
cppm_target_install(server)

