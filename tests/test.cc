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
    _openssl_BN r, s, t;
    std::cout << "4. ## Addition ##" << std::endl;
    r._randomInplace(lambda);
    cout << "a =         [" << r._bn2hex() << endl;
    s = r._add(c, p);           
    cout << "c = a + 1 = [" << s._bn2hex() << endl;

    return 1;
}
