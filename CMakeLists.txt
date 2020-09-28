cmake_minimum_required(VERSION 3.12)

set(CPPM_VERSION 0.0.12)
include(cmake/cppm_loader.cmake)
cppm_project()

project(jogyu VERSION 0.0.1 LANGUAGES C CXX)
cppm_setting()
cppm_cxx_standard(17)
cppm_compiler_option(DEFAULT)

find_cppkg(OpenSSL git  MODULE ${OPENSSL_LIBRARY} TYPE lib)
find_cppkg(fmt 7.0.3  MODULE fmt::fmt TYPE lib)
find_cppkg(mariadbclientpp git  MODULE mariadbclientpp::mariadbclientpp TYPE lib)
find_cppkg(nlohmann_json 3.9.1  MODULE nlohmann_json::nlohmann_json TYPE lib)
find_cppkg(range-v3 0.11.0  MODULE range-v3::range-v3 TYPE lib)
find_cppkg(zmqpp git  MODULE zmqpp::zmq TYPE lib)


cppm_target_define(client BINARY
SOURCES
    src/client/main.cpp
    src/db/connector.hpp
    src/db/connector.cpp
    src/secure/crypt.cpp
    src/secure/hash.hpp
    src/secure/psi.cpp
    src/secure/crypt.h
    src/secure/hash.cpp
    src/secure/psi.hpp
)

cppm_target_define(server BINARY
SOURCES
    src/server/server.hpp
    src/server/main.cpp
    src/db/connector.hpp
    src/db/connector.cpp
    src/secure/crypt.cpp
    src/secure/hash.hpp
    src/secure/psi.cpp
    src/secure/crypt.h
    src/secure/hash.cpp
    src/secure/psi.hpp
)

cppm_unit_test_area()
if(JOGYU_BUILD_TESTING)

cppm_target_define(logic_test BINARY
SOURCES
    tests/logic_test.cpp
    src/secure/crypt.cpp
    src/secure/hash.hpp
    src/secure/psi.cpp
    src/secure/crypt.h
    src/secure/hash.cpp
    src/secure/psi.hpp
)

endif()
end_cppm_unit_test_area()


set(global_deps PUBLIC OpenSSL fmt mariadbclientpp nlohmann_json range-v3 zmqpp)
cppm_target_dependencies(client
   ${global_deps})

cppm_target_dependencies(server
   ${global_deps})

cppm_target_dependencies(logic_test
   ${global_deps})


cppm_target_install(client)
cppm_target_install(server)

