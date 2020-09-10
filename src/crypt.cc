/* ************************************************************************************************************************************ *\
 * @file    crypt.cc
 * @brief   a sample code for you who are working with C++
 * @author  Myungsun Kim
 * 
 * 
 * 
\* ************************************************************************************************************************************ */

#include "crypt.h"

/**
 * @fn      _openssl_BN::_openssl_BN(void)
 * @brief   the default ctor
 * 
 */
_openssl_BN::_openssl_BN(void)
{
    _ctx = BN_CTX_new();
    _ptr = BN_new();
}

/**
 * @fn      _openssl_BN::_openssl_BN(const int rhs)
 * @brief   a copy ctor
 * 
 */
_openssl_BN::_openssl_BN(const int rhs): _openssl_BN()
{
    if (0 <= rhs) { ///< a positive integer or zero
        BN_set_word(_ptr, static_cast<unsigned long>(rhs));
    }
    else {
        BN_set_word(_ptr, static_cast<unsigned long>(-rhs));
        BN_set_negative(_ptr, 1);
    }
}

/**
 * @fn      _openssl_BN::_openssl_BN(const _openssl_BN& rhs)
 * @brief   a copy ctor
 * 
 */
_openssl_BN::_openssl_BN(const _openssl_BN& rhs): _openssl_BN()
{
    BN_copy(_ptr, rhs._ptr);
}

/**
 * @fn      _openssl_BN::_openssl_BN(const u_int8_t* byyes, const size_t len)
 * @brief   a ctor
 * 
 */
_openssl_BN::_openssl_BN(const u_int8_t* bytes, const size_t len)
{
    BN_bin2bn(bytes, len, _ptr);            ///< store the given binary string into an openssl big num
    BN_nnmod(_ptr, _ptr, _modp, _ctx);      ///< if it is greater than p, then mod p
                                            ///< see the below
                                            ///< BN_nnmod(rem, a, m, ctx) means rem = a % m under the given ctx
}

/**
 * @fn      _openssl_BN::~_openssl_BN(void)
 * @brief   the default dtor
 *
 */
_openssl_BN::~_openssl_BN(void)
{
    ///< destroy all objects
    BN_CTX_free(_ctx);
    BN_clear_free(_ptr);
}


