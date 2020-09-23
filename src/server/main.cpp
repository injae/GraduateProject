#include <iostream>
#include <server/server.hpp>
#include <db/connector.hpp>

#include <memory>
#include <openssl/sha.h>
#include "secure/hash.hpp"
#include <fmt/format.h>

using socket_ptr = std::shared_ptr<asio::ip::tcp::socket>;

int main(int argc, char* argv[]) {
    
    std::string data = "aaaaaaaaaaa";
    auto hash = hash::Sha256().hash(data);
    //auto data = db::PrivateSet{"hello",10,20};

    asio::io_context ctx;
    auto acceptor = asio::ip::tcp::acceptor(ctx, {asio::ip::tcp::v4(), 20001});
    auto socket = std::make_shared<asio::ip::tcp::socket>(asio::ip::tcp::socket(ctx));

    acceptor.async_accept(*socket, [](const auto& e) {
        if(e) {fmt::print("{}",e.message()); return;}
        fmt::print("connect");
    });
    //        asio::async_write(socket, asio::buffer(hash), [](auto e) { });

    ctx.run();

    return 0; 
}
