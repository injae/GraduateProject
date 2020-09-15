#include <iostream>
#include <db/connector.hpp>
#include <fmt/format.h>
#include <asio.hpp>

int main(int argc, char* argv[]) {
    std::cout<<"gp2020fall client"<<std::endl;
    //auto database = db::Connector("_PrivateSetX").setup();
    //auto query = database.con()->query(db::search_infector_query(database.table_name()));
    //auto infectors = db::query_to_vec(query);

    asio::io_context ctx;
    auto ep = asio::ip::tcp::endpoint(asio::ip::address::from_string("127.0.0.1"),20001);
    asio::ip::tcp::socket socket(ctx);
    socket.async_connect(ep, [&](const asio::error_code& ec){
        if(ec) return;
        fmt::print("connect");
    });
    ctx.run();

    return 0; 
}
