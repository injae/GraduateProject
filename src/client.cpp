#include <iostream>
#include <fmt/format.h>
#include <range/v3/all.hpp>
#include <nlohmann/json.hpp>
#include <fmt/ranges.h>

#include <zmqpp/zmqpp.hpp>

#include "db/connector.hpp"
#include "db/migrate.hpp"

#include "secure/psi.hpp"
#include "secure/hash.hpp"

#include "network/util.hpp"

using namespace ranges;
using namespace nlohmann;
using namespace ssl;
using namespace net::client;


int main(int argc, char* argv[]) {
    auto database = db::Connector("_PrivateSetX").setup();
    zmqpp::context context;
    zmqpp::socket socket (context, zmqpp::socket_type::req);
    socket.connect("tcp://localhost:66555");

    auto X = database.visitor();
    if(X.empty()) {
        db::migrate(database);
        X = database.visitor();
    }

    // c-1
    auto keys = psi::setup(1024);
    auto HX = X  | views::transform([](auto it) { return sha256::hash_to_Bn(it); }) | to_vector;
    auto An = HX | views::transform([&keys](auto it) { return keys.H1(it); });
    auto A = accumulate(An, Bn::one(), [&keys](auto it, auto acc) {return it.mul(acc, keys.p);});

    // c-2
    auto r = keys.r();
    auto B = A.mul(keys.g0.exp(r,keys.p), keys.p);

    // c-3~5
    auto aon = An | views::transform([&A, &keys](auto Ai) {
        auto Bi = A.mul(Ai.inv(keys.p),keys.p);
        auto ri  = keys.r();
        auto ai = Ai.mul(keys.g1.exp(ri,keys.p), keys.p);
        auto oi = Bi.mul(keys.g2.exp(ri,keys.p), keys.p);
        return std::make_tuple(ai, oi, ri);
    }) | to_vector;
    auto an = aon | views::transform([&](auto it){ return get<0>(it); });
    auto on = aon | views::transform([&](auto it){ return get<1>(it); });
    auto rn = aon | views::transform([&](auto it){ return get<2>(it); });

    // c-6
    auto [a1, o1, r1] = aon[0];
    auto y = B.mul(a1.mul(o1, keys.p).inv(keys.p), keys.p);
    auto h = keys.g1.mul(keys.g2, keys.p);
    auto pi_c = psi::two_prover(keys.p, keys.g0, h, keys.q, r, r1.negate() , y); // pi2 == pic


    // c-7 send server keys B, an, on, pi2
    send_data(keys, socket);
    send_data(B, socket);
    send_large_data(an | to_vector, socket);
    send_large_data(on | to_vector, socket);
    send_data(pi_c, socket);

    // c-8
    //auto [S, bn, Um, pi_s] =  server_to_client;
    Bn S = receive_data(socket);
    auto bn = receive_large_data<Bn>(socket);
    auto Um = receive_large_data<Bn>(socket);
    EqualValue pi_s = receive_data(socket);

    // c-9~10
    assert(psi::equal_verifier(pi_s, keys.p, keys.g1, a1, keys.q ,S ,bn[0]));

    // c-11~12
    auto Cn = views::zip(bn, An, HX, rn) | views::transform([&](auto it){
        auto& [bi, Ai, xi, ri]= it;
        auto ki = bi.mul(S.exp(ri,keys.p).inv(keys.p), keys.p);
        return psi::H({ki, Ai, xi});
    }) | to_vector;

    // c-13~14
    
    std::vector<int> I;

    for(auto&& [i, ci] :  Cn | views::enumerate) {
        for(auto& uj : Um) {
            if(ci == uj) { I.emplace_back(i); }
        }
    }

    fmt::print("infecters[{}]:{}\n", I.size(), I | views::transform([&](auto it) { return X[it]; }));

    fmt::print("finish\n");

    return 0; 
}
