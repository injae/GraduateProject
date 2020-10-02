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

#include <fmt/format.h>
#include <nlohmann/json.hpp>

/**
 * @class   BN
 * @brief   a wrapper class that gives an interface to the openssl::Big number functions
 * 
 *          In this class, the modulus p is explicitly given for intructive purpose
 *          If more reality is persued, the modulus p had better be embedded into the class
 *          Therefore, if possible I hope that you freely modify this class at your disposal
 */
namespace ssl {
    class Bn
    {
    ///<
    public:
        ///< ctors and dtor
        Bn(void);
        Bn(const int rhs);
        Bn(const Bn& rhs);
        Bn(const u_int8_t* bytes, const size_t len);
        virtual ~Bn(void);

        static Bn one(void) {return Bn(1);}           ///< singleton
        static Bn zero(void) {return Bn(0);}          ///< singleton
        bool is_one(void) const; 
        bool is_zero(void) const;    

        ///< size
        int byte_size(void) const;
        int bit_size(void) const;

        ///< choose a random and store itself
        void random_inplace(const Bn& range);
        void random_inplace(const int bits);
        void random_safe_prime_inplace(const int bits);

        ///< shift
        Bn rshift_one();
        Bn lshift_one();

        ///< arithmetic operations
        Bn mod(const Bn& p) const;
        void mod_inplace(const Bn& p);
        Bn negate(const Bn& p=NULL) const;                       ///< return -this mod p
        void negate_inplace(const Bn& p=NULL);                   ///< this = -this mod p
        Bn add(const Bn& x, const Bn& p=NULL) const;             ///< return this + x mod p
        void add_inplace(const Bn& x, const Bn& p=NULL);         ///< this = this + x mod p
        Bn sub(const Bn& x, const Bn& p=NULL) const;             ///< return this - x mod p
        void sub_inplace(const Bn& x, const Bn& p=NULL);         ///< this = this - x mod p
        Bn mul(const Bn& x, const Bn& p=NULL) const;             ///< return this * x mod p
        void mul_inplace(const Bn& x, const Bn& p=NULL);         ///< this = this * x mod p
        Bn div(const Bn& x) const;             ///< return this * x mod p
        Bn inv(const Bn& p=NULL) const;                          ///< return this^{-1} mod p
        void inv_inplace(const Bn& p=NULL);                      ///< this = this^{-1} mod p
        Bn exp(const Bn& x, const Bn& p=NULL) const;             ///< return this ^ x mod p
        void exp_inplace(const Bn& x, const Bn& p=NULL);         ///< this = this ^ x mod p
        ///< primality test
        bool is_prime(void) const;
        Bn gcd(const Bn& x) const;                          ///< gcd(this, x)

        ///< overloading operations
        Bn& operator=(const int rhs);                       ///< this <- rhs
        Bn& operator=(const Bn& rhs);     

        bool operator==(const Bn& rhs);
        bool operator!=(const Bn& rhs);

        // BN& operator+=(const BN& rhs);
        // BN& operator-=(const BN& rhs);
        // BN& operator*=(const BN& rhs);

        ///< input
        void from_dec(const char* dec);
        void from_hex(const char* hex);
        void from_bytes(const uint8_t* bytes, const int len);

        ///< output
        std::string bn_to_dec(const Bn& bn) const;
        std::string bn_to_hex(const Bn& bn) const;    
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
}

/// BN -> fmt, serializer
template<> struct fmt::formatter<ssl::Bn> : fmt::formatter<std::string> {
  template<typename FormatContext>
  auto format(ssl::Bn const& bn, FormatContext& ctx){ return fmt::formatter<std::string>::format(bn.to_hex(), ctx); }
};

/// BN -> json and json -> BN, serializer, deserializer
template <> struct nlohmann::adl_serializer<ssl::Bn> {
    static void to_json(json& j, const ssl::Bn& value) {j = value.to_hex();}
    static void from_json(const json& j, ssl::Bn& value) {value.from_hex(j.get<std::string>().c_str());}
};

#endif 
