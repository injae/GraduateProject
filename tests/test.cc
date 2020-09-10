/* ************************************************************************************************************************************ *\
 * @file    test.cc
 * @brief   The main entry
 * @author  Myungsun Kim
 * 
 * 
 * 
\* ************************************************************************************************************************************ */

#include <iostream>

#include "crypt.h"

int 
main(int argc, char** argv)
{
    // using std::cout;
    // using std::endl;

    _openssl_BN a, b(100);

    ///< random test
    std::cout << "1. Random value generation: " << std::endl;
    a._randomInplace(b);

    return 1;
}
