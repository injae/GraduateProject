#pragma once

#ifndef __SECURE_HASH_HPP__
#define __SECURE_HASH_HPP__

#include <openssl/sha.h>
#include <array>
#include <string>
#include <vector>
#include "secure/bn.hpp"

namespace ssl::sha256{
    std::string hash_to_str(const std::string& data);
    std::array<uint8_t, SHA256_DIGEST_LENGTH> hash(const std::string& data);
    Bn hash_to_Bn(const std::vector<uint8_t>& data);
    Bn hash_to_Bn(const std::string& data);
}



#endif
