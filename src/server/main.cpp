#include <iostream>
#include <memory>


#include <fmt/format.h>
#include <openssl/sha.h>
#include <nlohmann/json.hpp>

#include "secure/hash.hpp"
#include "server/server.hpp"
#include "db/connector.hpp"

#include <thread>
#include <zmqpp/zmqpp.hpp>


int main(int argc, char* argv[]) {
    using namespace nlohmann;

    zmqpp::context context;
    zmqpp::socket socket (context, zmqpp::socket_type::rep);
    socket.bind("tcp://*:66555");
    while(true) {
        zmqpp::message msg;
        socket.receive(msg);
        std::string pk;
        msg >> pk;
        std::cout << pk << std::endl;
        fmt::print("{}",pk);
        socket.send("hello");
        std::cout << "send all" << std::endl;
    }

    return 0;
}
