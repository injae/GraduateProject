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
#include <fmt/format.h>

#include "secure/crypt.h"

namespace ssl {
    /**
    * @fn      _openssl_BN::_openssl_BN(void)
    * @brief   the default ctor
    * 
    */
    Bn::Bn(void)
    {
        _ctx = BN_CTX_new();
        _ptr = BN_new();
    }

    /**
    * @fn      _openssl_BN::_openssl_BN(const int rhs)
    * @brief   a copy ctor
    * 
    */
    Bn::Bn(const int rhs): Bn()
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
    Bn::Bn(const Bn& rhs): Bn()
    {
        BN_copy(_ptr, rhs._ptr);
    }

    /**
    * @fn      _openssl_BN::_openssl_BN(const u_int8_t* byyes, const size_t len)
    * @brief   a ctor
    * 
    */
    Bn::Bn(const u_int8_t* bytes, const size_t len)
    {
        BN_bin2bn(bytes, len, _ptr);            ///< store the given binary string into an openssl big num
    }

    /**
    * @fn      _openssl_BN::~_openssl_BN(void)
    * @brief   the default dtor
    *
    */
    Bn::~Bn(void)
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
    void Bn::random_inplace(const Bn& range)
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
    Bn::random_inplace(const int bits)
    {
        ///< pick a random value whose length is bits and store itself
        ///< the 3rd parameter 0: MSB can be set 1
        ///< the 4th parameter 1: LSB can be set 1 (i.e., an odd integer)
        BN_rand(_ptr, bits, 0, 1);

        return;
    }

    /**
    * @fn      void _openssl_BN::_randomSafePrimeInplace(int)
    * @brief   pick a random safe prime and store itself
    * 
    */
    void Bn::random_safe_prime_inplace(const int bits) {
        if(!BN_generate_prime_ex(_ptr, bits, 1, NULL, NULL, NULL)) {
            fmt::print(stderr, "can't generate safe prime"); exit(1);
        }
    }


    /**
    * @fn      _openssl_BN _openssl_BN::_rshift1()
    * @brief   self/2
    * 
    */
    Bn Bn::rshift_one() {
        Bn ret; 
        if(!BN_rshift1(ret._ptr, _ptr)){
            fmt::print(stderr, "can't right shift 1"); exit(1);
        }
        return ret;
    }
    /**
    * @fn      _openssl_BN _openssl_BN::_lshift1()
    * @brief   self*2
    * 
    */
    Bn Bn::lshift_one() {
        Bn ret; 
        if(!BN_lshift1(ret._ptr, _ptr)){
            fmt::print(stderr, "can't left shift 1"); exit(1);
        }
        return ret;
    }

    /**
    * @fn      _openssl_BN _openssl_BN::_add(const _openssl_BN& x, const _openssl_BN& p)
    * @brief   r = this + x mod p
    * @param   x   2nd operand
    * @param   p   modulus
    * @return  r
    * 
    */ 
    Bn 
    Bn::add(const Bn& x, const Bn& p) const
    {
        Bn res;

        ///< res = this + x mod p
        BN_mod_add(res._ptr, this->_ptr, x._ptr, p._ptr, _ctx);

        return res;
    }

    /**
    * @fn      void _openssl_BN::_addInplace(const _openssl_BN& x, const _openssl_BN& p)
    * @brief   this = this + x mod p
    * 
    */
    void
    Bn::add_inplace(const Bn& x, const Bn& p)
    {
        ///< this = this + x mod p
        BN_mod_add(this->_ptr, this->_ptr, x._ptr, p._ptr, _ctx);

        return;
    }

    /**
    * @fn      _openssl_BN _openssl_BN::_mod(const _openssl_BN& p) const
    * @brief   res = this mod p
    * 
    */
    Bn 
    Bn::mod(const Bn& p) const
    {
        Bn res;

        ///< res = x mod p
        BN_mod(res._ptr, this->_ptr, p._ptr, _ctx);

        return res;
    }

    void
    Bn::mod_inplace(const Bn& p)
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
    Bn::from_dec(const char* dec) 
    {
        BN_dec2bn(&this->_ptr, dec);

        return;
    }

    /**
    * @fn      void BN::from_hex(const char* hex)
    * @brief   convert a hex string into an openssl big num
    * 
    */
    void
    Bn::from_hex(const char* hex) 
    {
        BN_hex2bn(&this->_ptr, hex);
        return;
    }

    /**
    * @fn      void _openssl_BN::_byte2bn(_openssl_BN& bn, const uint8_t* bytes, const int len)
    * @brief   convert a byte string of size len into an openssl big num
    * @param   bytes   a byte string
    * @param   len     length
    * 
    */
    void Bn::from_bytes(const uint8_t* bytes, const int len)
    {
        assert(0 != _ptr);
        BN_bin2bn(bytes, len, this->_ptr);

        return;
    }

    /**
    * @fn      std::string _openssl_BN::_bn2dec(void) const
    * @brief   convert an openssl big num into a decimal string
    * 
    */
    std::string Bn::to_dec(void) const
    {
        std::string res = "";
        char*       dec = 0;

        dec = BN_bn2dec(this->_ptr);
        for (auto i = 0; i < std::strlen(dec); i++) {
            res = res + dec[i];
        }

        return res;
    }

    std::string Bn::bn_to_dec(const Bn& bn) const
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
    * @fn      std::string _openssl_BN::_bn2hex(void) const
    * @brief   convert an openssl big num into a hexdecimal string
    * 
    */
    std::string
    Bn::to_hex(void) const
    {
        std::string res = "";
        char*       hex = 0;

        hex = BN_bn2hex(this->_ptr);
        for (auto i = 0; i < std::strlen(hex); i++) {
            res = res + hex[i];
        }

        return res;
    }

    /**
    * @fn      std::string _openssl_BN::_bn2hex(const _openssl_BN& bn) const
    * @brief   convert an openssl big num into a hexdecimal string
    * 
    */
    std::string
    Bn::bn_to_hex(const Bn& bn) const
    {
        std::string res = "";
        char*       hex = 0;

        hex = BN_bn2hex(bn._ptr);
        for (auto i = 0; i < std::strlen(hex); i++) {
            res = res + hex[i];
        }

        return res;
    }

    /**
    * @fn      void _openssl_BN::_bn2byte(uint8_t* bytes, int* len) const
    * @brief   convert a big num into a byte sting of size len
    * 
    */
    void Bn::to_bytes(uint8_t* bytes, int* len) const
    {
        assert(0 != bytes);
        *len = BN_bn2bin(this->_ptr, bytes);

        return;
    }

    std::vector<uint8_t> Bn::to_bytes() {
        std::vector<uint8_t> result;
        uint8_t buffer[1000] = {0};
        auto len = BN_bn2bin(this->_ptr, buffer);
        result.resize(len);
        std::memcpy(&result[0], &buffer[0], len*sizeof(uint8_t));
        return result;
    }

    /**
    * @fn      int _openssl_BN::_getBitSize(void) const
    * @brief   count the big num size in bits
    * 
    */
    int Bn::bit_size(void) const
    {
        return BN_num_bits(this->_ptr);
    }

    /**
    * @fn      int _openssl_BN::_getByteSize(void) const
    * @brief   count the big num size in bytes
    * 
    */
    int
    Bn::byte_size(void) const
    {
        return BN_num_bytes(this->_ptr);
    }

    /**
    * @fn      _openssl_BN& _openssl_BN::operator=(const int rhs)
    * @brief   assignment by an integer
    * 
    */
    Bn&
    Bn::operator=(const int rhs)
    {
        if (0 < rhs) {
            BN_set_word(_ptr, static_cast<unsigned long>(rhs));
        }
        else {
            BN_set_word(_ptr, static_cast<unsigned long>(-rhs));
            BN_set_negative(_ptr, 1);
        }
        return *this;
    }

    /**
    * @fn      _openssl_BN& _openssl_BN::operator=(const _openssl_BN& rhs)
    * @brief   assignment
    * 
    */
    Bn&
    Bn::operator=(const Bn& rhs)
    {
        BN_copy(this->_ptr, rhs._ptr);

        return *this;
    }

    /**
    * @fn      _openssl_BN _openssl_BN::_sub(const _openssl_BN& x, const _openssl_BN& p) const
    * @brief   return this - x mod p
    * 
    */
    Bn 
    Bn::sub(const Bn& x, const Bn& p) const
    {
        Bn res;

        ///< res = this - x mod p
        BN_mod_sub(res._ptr, this->_ptr, x._ptr, p._ptr, _ctx);

        return res;
    }

    /**
    * @fn      void _openssl_BN::_subInplace(const _openssl_BN& x, const _openssl_BN& p)
    * @brief   this = this - x mod p
    * 
    */
    void 
    Bn::sub_inplace(const Bn& x, const Bn& p) 
    {
        ///< this = this - x mod p
        BN_mod_sub(_ptr, this->_ptr, x._ptr, p._ptr, _ctx);

        return;
    }

    /**
    * @fn      _openssl_BN _openssl_BN::_mul(const _openssl_BN& x, const _openssl_BN& p) const
    * @brief   return this * x mod p
    * 
    */
    Bn 
    Bn::mul(const Bn& x, const Bn& p) const
    {
        Bn res;

        ///< res = this * x mod p
        BN_mod_mul(res._ptr, this->_ptr, x._ptr, p._ptr, _ctx);

        return res;
    }

    /**
    * @fn      void _openssl_BN::_mulInplace(const _openssl_BN& x, const _openssl_BN& p) 
    * @brief   this = this * x mod p
    * 
    */
    void 
    Bn::mul_inplace(const Bn& x, const Bn& p)  
    {
        ///< this = this * x mod p
        BN_mod_mul(this->_ptr, this->_ptr, x._ptr, p._ptr, _ctx);

        return;
    }

    /**
    * @fn      _openssl_BN _openssl_BN::_inv(const _openssl_BN& p) const
    * @brief   return 1/this mod p
    * 
    */
    Bn 
    Bn::inv(const Bn& p) const
    {
        Bn res;

        ///< res = 1 /this mod p
        BN_mod_inverse(res._ptr, this->_ptr, p._ptr, _ctx);

        return res;
    }

    /**
    * @fn      void _openssl_BN::_invInplace(const _openssl_BN& p)
    * @brief   this = 1/this mod p
    * 
    */
    void Bn::inv_inplace(const Bn& p) 
    {
        ///< this = 1/this mod p
        BN_mod_inverse(this->_ptr, this->_ptr, p._ptr, _ctx);

        return;
    }

    /**
    * @fn      _openssl_BN _openssl_BN::_exp(const _openssl_BN& x, const _openssl_BN& p) const
    * @brief   return this ^ x mod p
    * 
    */    
    Bn Bn::exp(const Bn& x, const Bn& p) const
    {
        Bn res;

        ///< res = this ^ x mod p
        BN_mod_exp(res._ptr, this->_ptr, x._ptr, p._ptr, _ctx);

        return res;
    }

    /**
    * @fn      void _openssl_BN::_expInplace(const _openssl_BN& x, const _openssl_BN& p) 
    * @brief   this = this ^ x mod p
    * 
    */
    void 
    Bn::exp_inplace(const Bn& x, const Bn& p) 
    {
        ///< this = this ^ x mod p
        BN_mod_exp(this->_ptr, this->_ptr, x._ptr, p._ptr, _ctx);

        return;
    }

    /**
    * @fn      _openssl_BN _openssl_BN::_negate(const _openssl_BN& p) const
    * @brief   return p - this
    * 
    */
    Bn 
    Bn::negate(const Bn& p) const
    {
        Bn res;

        if (BN_is_zero(_ptr)) {
            return Bn();
        }
        ///< res = p - this
        BN_sub(res._ptr, p._ptr, _ptr);

        return res;
    }

    /**
    * @fn      void _openssl_BN::_negateInplace(const _openssl_BN& p)
    * @brief   this = p - this
    * 
    */
    void 
    Bn::negate_inplace(const Bn& p)
    {
        if (BN_is_zero(_ptr)) {
            return;
        }
        ///< this = p - this
        BN_sub(_ptr, p._ptr, _ptr);

        return;
    }

    /**
    * @fn      bool _openssl_BN::_isPrime(void) const
    * @brief   The Miller-Rabin primality test
    * 
    */
    bool Bn::is_prime(void) const
    {
        ///< run the Miller-Rabin probabilistic primality test
        ///< the iteration number is 64 by default
        if (0 < BN_is_prime_ex(this->_ptr, BN_prime_checks, _ctx, 0)) {
            return true;
        }
        else {
            return false;
        }
    }

    /**
    * @fn      bool _openssl_BN::_isOne(void) const
    * @brief   check if this == 1
    * 
    */
    bool Bn::is_one(void) const 
    { 
        if (BN_is_one(_ptr)) {
            return true;
        } else {
            return false;
        }
    } 

    /**
    * @fn      bool _openssl_BN::_isZero(void) const
    * @brief   check if this == 0
    * 
    */
    bool Bn::is_zero(void) const 
    { 
        if (BN_is_zero(_ptr)) {
            return true;
        }
        else {
            return false;
        }
    }

    /**
    * @fn      bool _openssl_BN::operator==(const _openssl_BN& rhs)
    * @brief   == operator
    * 
    */
    bool Bn::operator==(const Bn& rhs)
    {
        ///< check if this == rhs
        if (0 != BN_cmp(this->_ptr, rhs._ptr)) {
            return false;
        }
        else {
            return true;
        }
    }

    /**
    * @fn      bool _openssl_BN::operator!=(const _openssl_BN& rhs)
    * @brief   != operator
    * 
    */
    bool Bn::operator!=(const Bn& rhs)
    {
        if (*this == rhs) {
            return false;
        }
        else {
            return true;
        }
    }

    /**
    * @fn      _openssl_BN _openssl_BN::_gcd(const _openssl_BN& x) const
    * @brief   return gcd(this, x)
    * 
    */
    Bn Bn::gcd(const Bn& x) const
    {
        Bn res;

        ///< res = gcd(this, x)
        BN_gcd(res._ptr, this->_ptr, x._ptr, _ctx);

        return res;
    }


    Bn Bn::div(const Bn& x) const {
        Bn div;
        Bn rem;
        BN_div(div._ptr, rem._ptr, this->_ptr, x._ptr, _ctx);
        return div;
    }             

}
