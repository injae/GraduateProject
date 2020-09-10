/* ************************************************************************************************************************************ *\
 * @file    crypt.h
 * @brief   a sample code for you who are working with C++
 * @author  Myungsun Kim
 * @note    I follow the comment style of doxygen
 *          So for the further information see https://www.doxygen.nl/index.html
 * 
\* ************************************************************************************************************************************ */

#ifndef __CrYpT_H
#define __CrYpT_H

#include <cstdint>

#include <openssl/bn.h>
#include <openssl/rand.h>

/**
 * @class
 * @brief
 * 
 */
class _openssl_BN
{
///<
public:
    ///< ctors and dtor
    _openssl_BN(void);
    _openssl_BN(const int rhs);
    _openssl_BN(const _openssl_BN& rhs);
    _openssl_BN(const u_int8_t* bytes, const size_t len);
    virtual ~_openssl_BN(void);

    static inline _openssl_BN _one(void) {return _openssl_BN(1);}          ///< singleton
    static inline _openssl_BN _zero(void) {return _openssl_BN(0);}         ///< singleton
    
protected:
private:

///<
public:
    BN_CTX* _ctx;       ///< context
    BIGNUM* _ptr;       ///< pointer to the big number 
    BIGNUM* _modp;      ///< the modulus prime p
protected:
private:
};

#endif //__CrYpT_H