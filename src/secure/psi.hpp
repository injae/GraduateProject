#pragma once

#ifndef __SECURE_PSI_HPP__
#define __SECURE_PSI_HPP__

#include "secure/crypt.h"
#include <tuple>

namespace psi {
    /// public keys p g0 g1 g2 q
    struct PublicKeys {
        BN p;
        BN g0;
        BN g1;
        BN g2;
        BN q;
        // random in range(q)
        inline BN r() { return PublicKeys::r(q); }

        // random in range(q)
        inline static BN r(const BN& q) { BN r;
            do {r.random_inplace(q);}while(r.is_zero());
            return r;
        }
        // H1(x) = h = g0^x (mod p)
        inline BN H1(BN &x) {return g0.exp(x, p);}
    };

    struct ProofValue {
        BN b;
        BN z0;
        BN z1;
    };

    struct EqualValue {
        BN b0;
        BN b1;
        BN z;
    };

    // H(bsn), ex) H3(a || b|| c) == H(vector{a, b,c})
    BN H(std::vector<BN>&& bns); 

    // return g
    BN find_generator(BN& p, BN& q);

    PublicKeys setup(int bits);

    // h = H1(x),  x (- Zq, h (- G
    BN H1(PublicKeys& keys, BN& x);

    // pi_eq := (β0, β1, z) pub keys (p,g,q,y0,y1) y0 = g0^x (mod p), y1 = g1^x (mod p)
    EqualValue equal_prover(BN& p, BN& g0, BN& g1, BN& q, BN& x, BN& y0, BN& y1);
    bool equal_verifier(EqualValue& pi, BN& p, BN& g0, BN& g1, BN& q, BN y0, BN y1);

    // pi2(β, z0, z1) = g1^r0*g2^r1
    ProofValue two_prover(BN& p, BN& g0, BN& g1, BN& q, BN& x0, BN x1, BN& y);
    
    // true or false,  pub keys (pi2, p, g0, g1, q, y)
    bool two_verifier(ProofValue& pi, BN& p, BN& g0, BN& g1, BN& q, BN& y);
}

#endif
