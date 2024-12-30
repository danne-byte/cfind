#include "crypto.hpp"

//#include <iomanip>

#include <openssl/sha.h>

crypto::Digest crypto::sha256(const io::Binary& data) {
    Digest digest(SHA256_DIGEST_LENGTH);
    SHA256(data.data(), data.size(), digest.data());

    return digest;
}
