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

#include "crypt.h"

int 
main(int argc, char** argv)
{
    using std::cout;
    using std::endl;

    uint8_t     bytes[1000] = {0};
    _openssl_BN a, b(100), c = 1;
    int         len = 0, lambda = 2048, count = 0;

    

    ///< random test
    std::cout << "1. ## Random Generation ##" << std::endl;
    a._randomInplace(1024);
    std::cout << "size in bytes: " << a._getByteSize() << std::endl;
    std::cout << "number in hex: [" << a._bn2hex() << "]" << std::endl;
    a._bn2byte(bytes, &len);
    std::cout << "into a binary string of size " << len << " : [";
    for (auto i = 0; i < len; i++) {
        std::printf("%02X", bytes[i]);
    }
    std::cout << "]" << std::endl << std::endl;

    ///< assignment
    std::cout << "2. ## Assignment ##" << std::endl;
    _openssl_BN d = a;
    std::cout << "number in hex: [" << d._bn2hex() << "]" << std::endl << std::endl;

    ///< generate a prime of lenght lambda
    std::cout << "3. ## Prime generation ##" << std::endl;
    _openssl_BN p;
    p._randomInplace(lambda);
    while (true) {
        count += 1;
        if (p._isPrime()) break;
        p._randomInplace(lambda);
    }
    cout << "The total trial number: " << count << endl;
    cout << "A prime number: [" << p._bn2hex() << "]" << endl;

    ///< arithmetic
    _openssl_BN r, s, t, u, v, w;
    std::cout << "4. ## Addition and Subtraction ##" << std::endl;
    r._randomInplace(lambda);
    cout << "a =         [" << r._bn2hex() << "]" << endl;
    s = r._add(c, p);           
    cout << "c = a + 1 = [" << s._bn2hex() << "]" << endl;

    std::cout << "5. ## Multiplication and Division (= Inverse) ##" << std::endl;
    _openssl_BN one(1);
    t = s._gcd(p);                                          ///< t = gcd(s, p)
    while (true != t._isOne()) {
        s._add(one, p);                                     ///< s++
        t = s._gcd(p);
    }
    cout << "s =   [" << s._bn2hex() << "]" << endl;
    v = s._inv(p);
    cout << "1/s = [" << v._bn2hex() << "]" << endl;
    v._mulInplace(s, p);
    cout << "s * 1/s = [" << v._bn2hex() << "]" << endl;

    std::cout << "6. ## Exponentiation ##" << std::endl;
    _openssl_BN p_minus_1 = p._sub(one, p);

    w = v._exp(p_minus_1, p);
    cout << "s^{p-1} = [" << w._bn2hex() << "]" << endl;    ///< recall Fermat's little theorem

    return 1;
}
