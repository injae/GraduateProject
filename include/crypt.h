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

#include <string>
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

    ///< size
    int _getByteSize(void) const;
    int _getBitSize(void) const;

    ///< choose a random
    void _randomInplace(const _openssl_BN& range);
    void _randomInplace(const int bits);
    ///< arithmetic operations
    _openssl_BN _mod(const _openssl_BN& x, const _openssl_BN& p);
    void _modInplace(const _openssl_BN& p);
    _openssl_BN _add(const _openssl_BN& x, const _openssl_BN& p);           ///< return this + x mod p
    void _addInplace(const _openssl_BN& x, const _openssl_BN& p);           ///< this = this + x mod p
    ///< overloading arith. operations
    _openssl_BN& operator=(const int rhs);                                  ///< this <- rhs
    _openssl_BN& operator=(const _openssl_BN& rhs);     

    ///< input
    void _dec2bn(const char* dec);
    void _hex2bn(const char* hex);
    void _byte2bn(const uint8_t* bytes, const int len);                
    ///< output
    std::string _bn2dec(const _openssl_BN& bn) const;
    std::string _bn2hex(const _openssl_BN& bn) const;    
    std::string _bn2dec(void) const;
    std::string _bn2hex(void) const;
    void _bn2byte(uint8_t* bytes, int* len) const;

protected:
private:
    void setModulus__(void);

///<
public:
    BN_CTX* _ctx;       ///< context
    BIGNUM* _ptr;       ///< pointer to the big number 
    // BIGNUM* _modp;      ///< the modulus prime p
protected:
private:
};

#endif //__CrYpT_H