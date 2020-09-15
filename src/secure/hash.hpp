#pragma once

#ifndef __SECURE_HASH_HPP__
#define __SECURE_HASH_HPP__

#include <openssl/sha.h>
#include <string>

namespace hash {

    class Sha256 {
    public:
        Sha256() { SHA256_Init(&ctx_); }
        std::string hash(const std::string& data) {
            std::string result(SHA256_DIGEST_LENGTH*2, ' ');
            unsigned char digest[SHA256_DIGEST_LENGTH];
            SHA256_Update(&ctx_, data.c_str(), strlen(data.c_str()));
            SHA256_Final(digest, &ctx_);
            for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
                sprintf(&result[i*2], "%02x", (unsigned int)digest[i]);
            return result;
        }

    private:
        SHA256_CTX ctx_;
    };
}



#endif
