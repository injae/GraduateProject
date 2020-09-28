#pragma once

#ifndef __SECURE_HASH_HPP__
#define __SECURE_HASH_HPP__

#include <openssl/sha.h>
#include <array>
#include <string>
#include <vector>
#include "secure/crypt.h"

namespace hash {
    class Sha256 {
    public:
        Sha256() { SHA256_Init(&ctx_); }
        std::string hash_to_str(const std::string& data);
        std::array<uint8_t, SHA256_DIGEST_LENGTH> hash(const std::string& data);
        BN hash_to_BN(const std::vector<uint8_t>& data);
        BN hash_to_BN(const std::string& data);
    private:
        SHA256_CTX ctx_;
    };
}



#endif
