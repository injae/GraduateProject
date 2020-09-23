#include <iostream>
#include <fmt/format.h>
#include <asio.hpp>
#include <secure/psi.hpp>
#include <secure/hash.hpp>
#include <range/v3/all.hpp>

int main(int argc, char* argv[]) {
    using namespace ranges;

    hash::Sha256 sha256;
    std::vector<std::string> X = {"hello1", "hello2", "hello3"};
    // 1
    auto keys = psi::setup(1024);
    auto Xh = X | views::transform([&sha256](auto it) { return sha256.hash_to_BN(it); }) | to_vector;
    auto As = Xh | views::transform([&keys](auto it) { return keys.H1(it); });
    auto A = accumulate(As, BN::one(), [&keys](auto it, auto acc) {return it.mul(acc, keys.p);});

    // 2
    auto r = keys.r();
    auto B = A.mul(keys.g0.exp(r, keys.p), keys.p);

    // 3~5
    auto aos = As | views::transform([&A, &keys](auto Ai) {
        auto Bi = A.mul(Ai.inv(keys.p), keys.p);
        auto ri  = keys.r();
        auto ai = Ai.mul(keys.g1.exp(ri, keys.p), keys.p);
        auto oi = Bi.mul(keys.g2.exp(ri, keys.p), keys.p);
        return std::make_tuple(ai, oi, ri);
    }) | to_vector;

    //6
    auto [a1, o1, r1] = aos[0];
    auto y = B.mul(a1.inv(keys.p).mul(o1.inv(keys.p), keys.p), keys.p);
    auto h = keys.g1.mul(keys.g2, keys.p);
    auto pi2 = psi::two_prover(keys.p, keys.g0, h, keys.q, r, r1.negate(keys.p) , y); // pi2 == pieq

    //7 send server keys B, as, os, pi2
    // auto client_to_server = make_cuple(keys, B, as, os, pi2);
    
    // server side
    {
        std::vector<std::string> Y = {"hello1", "hello3", "hello4"};

        // 2
        // auto [keys, B, as, os, pi2]  = client_to_server;

        // 3
        // auto y = B.mul(a1.inv(keys.p), o1.inv(keys.p), keys.p);
        // auto h = keys.g1.mul(keys.g2, keys.p);

        // 4
        if(not psi::two_verifier(pi2, keys.p, keys.g0, h, keys.q, y)) {
            fmt::print(stderr, "fail two verifier");
            exit(1);
        }

        // 5
        auto rr = keys.r();
        auto S = keys.g1.exp(rr, keys.p);

        // 6
        auto b1 = a1.exp(rr, keys.p); // bn = an^rr
        auto pieq = psi::equal_prover(keys.p, keys.g1, a1, keys.q, rr, S, b1); // pieq == pis

        // 7~8
        aos | views::transform([&keys, &rr](auto it) {
            auto ai = get<0>(it);
            return ai.exp(rr,keys.p);
        });
        
    }
    //auto [B, aos, pic] = client_to_server;
    


    //recive S, bs, us, pis
    
    


    fmt::print("generate g\n");

    return 0;
}

