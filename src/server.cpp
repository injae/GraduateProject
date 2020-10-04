#include <iostream>
#include <memory>
#include <thread>

#include <fmt/format.h>
#include <fmt/ranges.h>
#include <openssl/sha.h>
#include <nlohmann/json.hpp>
#include <zmqpp/zmqpp.hpp>

#include "secure/hash.hpp"
#include "db/connector.hpp"
#include "db/migrate.hpp"
#include "network/util.hpp"
#include "secure/psi.hpp"
#include "utility/parallel.hpp"

#include <future>

using namespace nlohmann;
using namespace ranges;
using namespace ssl;
using namespace net::server;

int main(int argc, char* argv[]) {
    auto database = db::Connector("_PrivateSetY").setup();

    //database.drop_table();
    auto Y = database.infectors();
    fmt::print("infectors:{}\n",Y.size());
    if(Y.empty()) {
        db::migrate(database);
        Y = database.infectors();
    } 

    zmqpp::context context;
    zmqpp::socket socket (context, zmqpp::socket_type::rep);
    socket.bind("tcp://*:66555");

    while(true) {
    // s-2  auto [keys, B, an, on, pi_c]  = client_to_server;
        PublicKeys keys = receive_data(socket);
        Bn B = receive_data(socket);
        auto an = receive_large_data<Bn>(socket);
        auto on = receive_large_data<Bn>(socket);
        ProofValue pi_c = receive_data(socket);

    // s-3
        auto y = B.mul(an[0].mul(on[0], keys.p).inv(keys.p), keys.p);
        auto h = keys.g1.mul(keys.g2, keys.p);
        assert(psi::two_verifier(pi_c, keys.p, keys.g0, h, keys.q, y));

        // s-5
        auto rr = keys.r();
        auto S = keys.g1.exp(rr, keys.p);

        // s-7~8
        auto bn = an | par::transform(par::csize(an),[&keys, &rr](auto ai) {return ai.exp(rr,keys.p);}) | to_vector;

        // S-9~11
        auto Um = Y | par::transform(par::csize(Y), [&](auto it) {
                auto yj = sha256::hash_to_Bn(it);
                auto Sj = keys.H1(yj);
                auto kj = Sj.exp(rr, keys.p);
                return psi::H({kj, Sj, yj});
            }) | to_vector;

        // s-6
        auto a1 = an[0].exp(rr, keys.p);
        auto pi_s = psi::equal_prover(keys.p, keys.g1, an[0], keys.q, rr, S, a1); // pieq == pis

        //  s-12
        //  server_to_client(S, bn, Um, pi_s );
        fmt::print("s-12[S]\n");
        send_data(S, socket);
        fmt::print("s-12[bn]\n");
        send_large_data(bn, socket);
        fmt::print("s-12[Um]\n");
        send_large_data(Um, socket);
        fmt::print("s-12[pi_s]\n");
        send_data(pi_s, socket);

    }

    return 0;
}
