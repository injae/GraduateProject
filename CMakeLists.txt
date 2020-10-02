cmake_minimum_required(VERSION 3.12)

set(CPPM_VERSION 0.0.12)
include(cmake/cppm_loader.cmake)
cppm_project()

project(gp2020fall VERSION 0.0.1 LANGUAGES C CXX)
cppm_setting()
cppm_cxx_standard(17)
cppm_compiler_option(DEFAULT)

include(cmake/OpenSSLEnv.cmake)
find_cppkg(OpenSSL git  MODULE OpenSSL::SSL OpenSSL::Crypto TYPE lib)
find_cppkg(fmt 7.0.3  MODULE fmt::fmt TYPE lib)
find_cppkg(mariadbclientpp git  MODULE mariadbclientpp::mariadbclientpp TYPE lib)
find_cppkg(nlohmann_json 3.9.1  MODULE nlohmann_json::nlohmann_json TYPE lib)
find_cppkg(range-v3 0.11.0  MODULE range-v3::range-v3 TYPE lib)
find_cppkg(zmqpp git  MODULE zmqpp::zmq TYPE lib)


cppm_target_define(gp2020fall STATIC
SOURCES
    src/db/connector.cpp
    src/secure/psi.cpp
    src/secure/hash.cpp
    src/secure/bn.cpp
)

cppm_target_define(client BINARY
SOURCES
    src/client.cpp
)

cppm_target_define(server BINARY
SOURCES
    src/server.cpp
)

cppm_unit_test_area()
if(GP2020FALL_BUILD_TESTING)

cppm_target_define(crypt-test BINARY
SOURCES
    tests/test.cc
)

cppm_target_define(logic_test BINARY
SOURCES
    tests/logic_test.cpp
)

endif()
end_cppm_unit_test_area()


set(global_deps PUBLIC OpenSSL fmt mariadbclientpp nlohmann_json range-v3 zmqpp)
cppm_target_dependencies(gp2020fall
   ${global_deps})

cppm_target_dependencies(client
   ${global_deps}
   gp2020fall)

cppm_target_dependencies(server
   ${global_deps}
   gp2020fall)

cppm_target_dependencies(crypt-test
   ${global_deps}
   gp2020fall)

cppm_target_dependencies(logic_test
   ${global_deps}
   gp2020fall)


cppm_target_install(gp2020fall)
cppm_target_install(client)
cppm_target_install(server)

