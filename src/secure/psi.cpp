#include <fmt/format.h>
#include <range/v3/all.hpp>

#include "secure/psi.hpp"
#include "secure/hash.hpp"

namespace psi {

    // order = q g (- Zq*
    BN find_generator(BN& p, BN& q) {
        BN g; // generater
        auto one = BN::one();
        do {
            g.random_inplace(p); // random value in Zp
            if (g.is_zero() or g.is_one()) continue;
            if((one != g.mul(g, p)) && (one == g.exp(q,p)) && (one == g.exp(p.sub(one, p), p))) break;
        } while(true);
        return g;
    }

    PublicKeys setup(int bits) {
        PublicKeys keys;
        keys.p.random_safe_prime_inplace(bits);
        keys.q = keys.p.sub(BN::one(),keys.p).rshift_one();
        keys.g0 = psi::find_generator(keys.p,keys.q);
        keys.g1 = psi::find_generator(keys.p,keys.q);
        keys.g2 = psi::find_generator(keys.p,keys.q);

        return keys;
    }
    

    std::tuple<BN,BN,BN> equal_prover(BN& p, BN& g0, BN& g1, BN& q, BN& x, BN& y0, BN& y1) {
        BN b0, b1, z;
        auto r = PublicKeys::r(q);
        b0 = g0.exp(r, p);
        b1 = g1.exp(r, p);
        auto e = H({p, y0, y1 , b0, b1});
        z = r.sub(e.mul(x, q), q);
        return {b0, b1, z};
    }

    /// g1^r0*g2^r1
    ProofValue two_prover(BN& p, BN& g0, BN& g1, BN& q, BN& x0, BN x1, BN& y) { // namespace psi
        ProofValue pi;
        auto r0 = PublicKeys::r(q);
        auto r1 = PublicKeys::r(q);
        pi.b = g0.exp(r0, p).mul(g1.exp(r1, p), p);
        auto e = H({p, y, pi.b});
        pi.z0 = r0.sub(e.negate(q).mul(x0, q), q);
        pi.z1 = r1.sub(e.negate(q).mul(x1, q), q);
        return pi;
    }

    bool two_verifier(ProofValue& pi, BN& p, BN& g0, BN& g1, BN& q, BN& y) {
        auto [b, z0, z1] = pi;
        auto e = H({ p, y, b });
        auto v =  g0.exp(z0, p).mul(g1.exp(z1, p), p).mul(y.exp(e, p), p);
        return b == v;
    }

    BN H(std::vector<BN>&& bns) {
        using namespace ranges;
        return hash::Sha256()
            .hash_to_BN(bns
            | views::transform([](auto it) { return it.to_bytes(); })
            | views::cache1
            | views::join
            | to_vector);
    }
}
