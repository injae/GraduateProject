#include <iostream>
#include <db/connector.hpp>
#include <fmt/format.h>
#include <secure/psi.hpp>
#include <secure/hash.hpp>
#include <range/v3/all.hpp>
#include <nlohmann/json.hpp>

#include <zmqpp/zmqpp.hpp>


int main(int argc, char* argv[]) {
    using namespace ranges;
    using namespace nlohmann;

    //auto database = db::Connector("_PrivateSetX").setup();
    //auto query = database.con()->query(db::search_infector_query(database.table_name()));
    //auto infectors = db::query_to_vec(query);
    
    zmqpp::context context;
    zmqpp::socket socket (context, zmqpp::socket_type::req);
    socket.connect("tcp://localhost:66555");

    zmqpp::message msg;
    json pk = {{"p", "1234"}, {"q", "444"}};
    msg << pk.dump();
    socket.send(msg);
    std::string buf;
    socket.receive(buf);
    fmt:: print("{}", buf);

    return 0; 
}
