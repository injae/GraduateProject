/* ************************************************************************************************************************************ *\
 * @file    crypt.h
 * @brief   a sample code for you who are working with C++
 * @author  Myungsun Kim
 * @note    I follow the comment style of doxygen
 *          So for the further information see https://www.doxygen.nl/index.html
 * 
\* ************************************************************************************************************************************ */

#ifndef __SECURE_CRYPT_H__
#define __SECURE_CRYPT_H__

#include <string>
#include <cstdint>

#include <openssl/bn.h>
#include <openssl/rand.h>

/**
 * @class   _openssl_BN
 * @brief   a wrapper class that gives an interface to the openssl::Big number functions
 * 
 *          In this class, the modulus p is explicitly given for intructive purpose
 *          If more reality is persued, the modulus p had better be embedded into the class
 *          Therefore, if possible I hope that you freely modify this class at your disposal
 */
class BN
{
///<
public:
    ///< ctors and dtor
    BN(void);
    BN(const int rhs);
    BN(const BN& rhs);
    // BN(const _openssl_BN& rhs, const _openssl_BN& modulus);
    BN(const u_int8_t* bytes, const size_t len);
    virtual ~BN(void);

    static BN one(void) {return BN(1);}           ///< singleton
    static BN zero(void) {return BN(0);}          ///< singleton
    bool is_one(void) const; 
    bool is_zero(void) const;    

    ///< size
    int byte_size(void) const;
    int bit_size(void) const;

    ///< choose a random and store itself
    void random_inplace(const BN& range);
    void random_inplace(const int bits);
    void random_safe_prime_inplace(const int bits);

    ///< shift
    BN rshift_one();
    BN lshift_one();

    ///< arithmetic operations
    BN mod(const BN& p) const;
    void mod_inplace(const BN& p);
    BN negate(const BN& p=NULL) const;                       ///< return -this mod p
    void negate_inplace(const BN& p=NULL);                   ///< this = -this mod p
    BN add(const BN& x, const BN& p=NULL) const;             ///< return this + x mod p
    void add_inplace(const BN& x, const BN& p=NULL);         ///< this = this + x mod p
    BN sub(const BN& x, const BN& p=NULL) const;             ///< return this - x mod p
    void sub_inplace(const BN& x, const BN& p=NULL);         ///< this = this - x mod p
    BN mul(const BN& x, const BN& p=NULL) const;             ///< return this * x mod p
    void mul_inplace(const BN& x, const BN& p=NULL);         ///< this = this * x mod p
    BN inv(const BN& p=NULL) const;                          ///< return this^{-1} mod p
    void inv_inplace(const BN& p=NULL);                      ///< this = this^{-1} mod p
    BN exp(const BN& x, const BN& p=NULL) const;             ///< return this ^ x mod p
    void exp_inplace(const BN& x, const BN& p=NULL);         ///< this = this ^ x mod p
    ///< primality test
    bool is_prime(void) const;
    BN gcd(const BN& x) const;                          ///< gcd(this, x)

    ///< overloading operations
    BN& operator=(const int rhs);                       ///< this <- rhs
    BN& operator=(const BN& rhs);     

    bool operator==(const BN& rhs);
    bool operator!=(const BN& rhs);

    // _openssl_BN& operator+=(const _openssl_BN& rhs);
    // _openssl_BN& operator-=(const _openssl_BN& rhs);
    // _openssl_BN& operator*=(const _openssl_BN& rhs);

    ///< input
    void from_dec(const char* dec);
    void from_hex(const char* hex);
    void from_bytes(const uint8_t* bytes, const int len);

    ///< output
    std::string bn_to_dec(const BN& bn) const;
    std::string bn_to_hex(const BN& bn) const;    
    std::string to_dec(void) const;
    std::string to_hex(void) const;
    void to_bytes(uint8_t* bytes, int* len) const;
    std::vector<uint8_t> to_bytes();

protected:
private:
    // void setModulus__(void);

///<
private:
    BN_CTX* _ctx;       ///< context
    BIGNUM* _ptr;       ///< pointer to the big number 
    // BIGNUM* _p;         ///< the modulus prime p
protected:
};
#endif 
