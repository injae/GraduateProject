#include "secure/hash.hpp"

namespace hash::sha256 {
        std::string hash_to_str(const std::string& data) {
            std::string result(SHA256_DIGEST_LENGTH*2, ' ');
            uint8_t digest[SHA256_DIGEST_LENGTH];
            SHA256_CTX ctx_;
            SHA256_Init(&ctx_);
            SHA256_Update(&ctx_, data.c_str(), strlen(data.c_str()));
            SHA256_Final(digest, &ctx_);
            for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
                sprintf(&result[i*2], "%02x", (unsigned int)digest[i]);
            return result;
        }

        std::array<uint8_t, SHA256_DIGEST_LENGTH> hash(const std::string& data) {
            std::array<uint8_t,SHA256_DIGEST_LENGTH> digest;
            SHA256_CTX ctx_;
            SHA256_Init(&ctx_);
            SHA256_Update(&ctx_, data.c_str(), strlen(data.c_str()));
            SHA256_Final(digest.data(), &ctx_);
            return digest;
        }

        BN hash_to_BN(const std::vector<uint8_t>& data) {
            BN bn;
            uint8_t digest[SHA256_DIGEST_LENGTH];
            SHA256_CTX ctx_;
            SHA256_Init(&ctx_);
            SHA256_Update(&ctx_, &data[0], data.size());
            SHA256_Final(digest, &ctx_);
            bn.from_bytes(digest, SHA256_DIGEST_LENGTH);
            return bn;
        }

        BN hash_to_BN(const std::string& data) {
            BN bn;
            uint8_t digest[SHA256_DIGEST_LENGTH];
            SHA256_CTX ctx_;
            SHA256_Init(&ctx_);
            SHA256_Update(&ctx_, data.c_str(), data.length());
            SHA256_Final(digest, &ctx_);
            bn.from_bytes(digest, SHA256_DIGEST_LENGTH);
            return bn;
        }
}
