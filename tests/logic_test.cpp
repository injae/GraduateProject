#include <iostream>
#include <fmt/format.h>
#include <secure/psi.hpp>
#include <secure/hash.hpp>
#include <range/v3/all.hpp>
#include <fmt/ranges.h>
#include <vector>

int main(int argc, char* argv[]) {
    using namespace ranges;

    //safe prime check
    //{
    //    BN p;
    //    p.random_safe_prime_inplace(300);
    //    auto q = p.sub(BN::one(),p).rshift_one();
    //    fmt::print("p size:{}, is_prime {}, data:{}\n",p.byte_size(), p.is_prime(), p.to_dec());
    //    fmt::print("q size:{}, is_prime {}, data:{}\n",q.byte_size(), q.is_prime(), q.to_dec());
    //    fmt::print("2q ,  data:{}\n",q.lshift_one().to_dec());
    //    fmt::print("2q+1 ,  data:{}\n",q.lshift_one().add(BN::one(), NULL).to_dec());
    //}
    hash::Sha256 sha256;
    std::vector<std::string> X = {"hello1", "hello2", "hello3"};

    // c-1
    auto keys = psi::setup(1024);
    auto HX = X  | views::transform([&sha256](auto it) { return sha256.hash_to_BN(it); }) | to_vector;
    auto As = HX | views::transform([&keys](auto it) { return keys.H1(it); });
    auto A = accumulate(As, BN::one(), [&keys](auto it, auto acc) {return it.mul(acc, keys.p);});

    // c-2
    auto r = keys.r();
    auto B = A.mul(keys.g0.exp(r), keys.p);

    // c-3~5
    auto aon = As | views::transform([&A, &keys](auto Ai) {
        auto Bi = A.mul(Ai.inv(), keys.p);
        auto ri  = keys.r();
        auto ai = Ai.mul(keys.g1.exp(ri), keys.p);
        auto oi = Bi.mul(keys.g2.exp(ri), keys.p);
        return std::make_tuple(ai, oi, ri);
    }) | to_vector;
    auto an = aon | views::transform([&](auto it){ return get<0>(it); });

    // c-6
    auto [a1, o1, r1] = aon[0];
    auto y = B.mul(a1.inv().mul(o1.inv()), keys.p);
    auto h = keys.g1.mul(keys.g2, keys.p);
    auto pi_c = psi::two_prover(keys.p, keys.g0, h, keys.q, r, r1.negate() , y); // pi2 == pic
    // c-7 send server keys B, an, on, pi2
    // auto client_to_server = make_tuple(keys, B, an, on, pi2);
    
    // server side =========================

    // s-2
    // auto [keys, B, an, on, pi_c]  = client_to_server;

    // s-3
    // auto y = B.mul(a1.inv(keys.p), o1.inv(keys.p), keys.p);
    // auto h = keys.g1.mul(keys.g2, keys.p);
    if(not psi::two_verifier(pi_c, keys.p, keys.g0, h, keys.q, y)) {
        fmt::print(stderr, "fail two verifier\n");
        exit(1);
    } 
    fmt::print("proved\n");

    // s-5
    auto rr = keys.r();
    auto S = keys.g1.exp(rr, keys.p);

    // s-6
    auto b1 = a1.exp(rr); // bn = an^rr
    auto pi_s = psi::equal_prover(keys.p, keys.g1, a1, keys.q, rr, S, b1); // pieq == pis

    // s-7~8
    auto bn = an | views::transform([&keys, &rr](auto ai) {
        return ai.exp(rr,keys.p);
    });

    std::vector<std::string> Y = {"hello1", "hello3", "hello4"};
    // s-9~11
    auto Um = Y | views::transform([&](auto it) {
        auto yj = sha256.hash_to_BN(it);
        auto Sj = keys.H1(yj);
        auto kj = Sj.exp(rr, keys.p);
        return psi::H({kj, Sj, yj});
    }) | to_vector;

    // s-12
    // server_to_client(S, bn, Um, pi_s );
    // ================================================

    // c-8
    //auto [S, bn, Um, pi_s] =  server_to_client;

    // c-9~10
    if(psi::equal_verifier(pi_s, keys.p, keys.g1, a1, keys.q ,S ,b1)) {
        fmt::print(stderr, "fail equal verifier\n");
        exit(1);
    }

    // c-11~12
    auto Cn = views::zip(bn, an) | views::transform([&](auto it){
        auto& [bi, ai]= it;
        auto ki = bi.mul(S.exp(r.inv()), keys.p);
        return psi::H({ki, ai});
    }) | to_vector;

    // c-13~14
    
    std::vector<int> infector;
    for(auto&& [i, ci] :  Cn | views::enumerate) {
        for(auto& uj : Um) {
            if(ci == uj) infector.emplace_back(i);
            else { fmt::print("|"); }
        }
    }

    fmt::print("\n{}\n", infector | views::transform([&](auto it) { return X[it]; }));



    fmt::print("finish\n");

    return 0;
}
