/* ************************************************************************************************************************************ *\
 * @file    test.cc
 * @brief   The main entry
 * @author  Myungsun Kim
 * 
 * 
 * 
\* ************************************************************************************************************************************ */

#include <iostream>
#include <cstdio>
#include <fmt/format.h>

#include "secure/bn.hpp"
#include "secure/psi.hpp"

int main(int argc, char** argv)
{
    using namespace ssl;
    using std::cout;
    using std::endl;

    uint8_t     bytes[1000] = {0};
    Bn a, b(100), c = 1;
    int         len = 0, lambda = 2048, count = 0;

    ///< random test
    std::cout << "1. ## Random Generation ##" << std::endl;
    a.random_inplace(1024);
    std::cout << "size in bytes: " << a.byte_size() << std::endl;
    std::cout << "number in hex: [" << a.to_hex() << "]" << std::endl;
    a.to_bytes(bytes, &len);
    std::cout << "into a binary string of size " << len << " : [";
    for (auto i = 0; i < len; i++) {
        std::printf("%02X", bytes[i]);
    }
    std::cout << "]" << std::endl << std::endl;

    ///< assignment
    std::cout << "2. ## Assignment ##" << std::endl;
    Bn d = a;
    std::cout << "number in hex: [" << d.to_hex() << "]" << std::endl << std::endl;

    ///< generate a prime of lenght lambda
    std::cout << "3. ## Prime generation ##" << std::endl;
    Bn p;
    p.random_inplace(lambda);
    while (true) {
        count += 1;
        if (p.is_prime()) break;
        p.random_inplace(lambda);
    }
    cout << "The total trial number: " << count << endl;
    cout << "A prime number: [" << p.to_hex() << "]" << endl;

    ///< arithmetic
    Bn r, s, t, u, v, w;
    std::cout << "4. ## Addition and Subtraction ##" << std::endl;
    r.random_inplace(lambda);
    cout << "a =         [" << r.to_hex() << "]" << endl;
    s = r.add(c, p);           
    cout << "c = a + 1 = [" << s.to_hex() << "]" << endl;

    std::cout << "5. ## Multiplication and Division (= Inverse) ##" << std::endl;
    Bn one(1);
    t = s.gcd(p);                                          ///< t = gcd(s, p)
    while (true != t.is_one()) {
        s.add(one, p);                                     ///< s++
        t = s.gcd(p);
    }
    cout << "one =   [" << one.to_hex() << "]" << endl;
    cout << "s =   [" << s.to_hex() << "]" << endl;
    v = s.inv(p);
    cout << "1/s = [" << v.to_hex() << "]" << endl;
    v.mul_inplace(s, p);
    cout << "s * 1/s = [" << v.to_hex() << "]" << endl;
    std::cout << "6. ## Exponentiation ##" << std::endl;
    Bn p_minus_1 = p.sub(one, p);

    w = v.exp(p_minus_1, p);
    cout << "s^{p-1} = [" << w.to_hex() << "]" << endl;    ///< recall Fermat's little theorem

    return 1;
}
