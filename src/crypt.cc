/* ************************************************************************************************************************************ *\
 * @file    crypt.cc
 * @brief   a sample code for you who are working with C++
 * @author  Myungsun Kim
 * 
 * 
 * 
\* ************************************************************************************************************************************ */

#include <cassert>
#include <cstring>

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

/**
 * @fn      void _openssl_BN::_randomInplace(void)
 * @brief   pick a random number and store itself
 * 
 */
void
_openssl_BN::_randomInplace(const _openssl_BN& range)
{
    ///< pick a random value between 0 and range and store itself
    BN_rand_range(_ptr, range._ptr);
    
    return;
}

/**
 * @fn      void _openssl_BN::_randomInplace(void)
 * @brief   pick a random number and store itself
 * 
 */
void
_openssl_BN::_randomInplace(const int bits)
{
    ///< pick a random value whose length is bits and store itself
    ///< the 3rd parameter 0: MSB can be set 1
    ///< the 4th parameter 1: LSB can be set 1 (i.e., an odd integer)
    BN_rand(_ptr, bits, 0, 1);
    
    return;
}

/**
 * @fn      _openssl_BN _openssl_BN::_add(const _openssl_BN& x, const _openssl_BN& p)
 * @brief   r = this + x mod p
 * @param   x   2nd operand
 * @param   p   modulus
 * @return  r
 * 
 */ 
_openssl_BN 
_openssl_BN::_add(const _openssl_BN& x, const _openssl_BN& p)
{
    _openssl_BN res;

    ///< res = this + x mod p
    BN_mod_add(res._ptr, _ptr, x._ptr, p._ptr, _ctx);

    return res;
}

/**
 * @fn      void _openssl_BN::_addInplace(const _openssl_BN& x, const _openssl_BN& p)
 * @brief   this = this + x mod p
 * 
 */
void
_openssl_BN::_addInplace(const _openssl_BN& x, const _openssl_BN& p)
{
    ///< res = this + x mod p
    BN_mod_add(_ptr, _ptr, x._ptr, p._ptr, _ctx);

    return;
}

/**
 * @fn      _openssl_BN _openssl_BN::_mod(const _openssl_BN& x, const _openssl_BN& p)
 * @brief   r = x mod p
 * 
 */
_openssl_BN 
_openssl_BN::_mod(const _openssl_BN& x, const _openssl_BN& p)
{
    _openssl_BN res;

    ///< res = x mod p
    BN_mod(res._ptr, x._ptr, p._ptr, _ctx);

    return res;
}

void
_openssl_BN::_modInplace(const _openssl_BN& p)
{
    ///< this = this mod p
    BN_mod(_ptr, _ptr, p._ptr, _ctx);

    return;
}

/**
 * @fn      void _openssl_BN::_dec2bn(const char* dec)
 * @brief   convert a decimal string into an openssl big num
 * 
 */
void
_openssl_BN::_dec2bn(const char* dec) 
{
    BN_dec2bn(&this->_ptr, dec);

    return;
}

/**
 * @fn      void _openssl_BN::_hex2bn(const char* dec)
 * @brief   convert a decimal string into an openssl big num
 * 
 */
void
_openssl_BN::_hex2bn(const char* hex) 
{
    BN_hex2bn(&this->_ptr, hex);

    return;
}

/**
 * @fn      std::string _openssl_BN::_bn2dec(const _openssl_BN& bn) const
 * @brief   convert an openssl big num into a decimal string
 * 
 */
std::string
_openssl_BN::_bn2dec(const _openssl_BN& bn) const
{
    std::string res = "";
    char*       dec = 0;

    dec = BN_bn2dec(bn._ptr);
    for (auto i = 0; i < std::strlen(dec); i++) {
        res = res + dec[i];
    }

    return res;
}

/**
 * @fn      std::string _openssl_BN::_bn2hex(const _openssl_BN& bn) const
 * @brief   convert an openssl big num into a hexdecimal string
 * 
 */
std::string
_openssl_BN::_bn2hex(const _openssl_BN& bn) const
{
    std::string res = "";
    char*       hex = 0;

    hex = BN_bn2hex(bn._ptr);
    for (auto i = 0; i < std::strlen(hex); i++) {
        res = res + hex[i];
    }

    return res;
}