#include "crypto.hpp"

#include <iomanip>

#include <openssl/sha.h>

#include "log.hpp"
using namespace logger;


/* Allocate buffer **hash** to be of size for a sha256 hash. **Returns** length of buffer. */
size_t crypto::allocate_sha56_buffer(unsigned char** hash) {
    TRACE_CALL;

    *hash = new unsigned char[SHA256_DIGEST_LENGTH];
    LOG_DEBUG(*hash);
    return SHA256_DIGEST_LENGTH;
}

size_t crypto::make_sha256(char* buf, size_t buf_size, size_t hash_size, unsigned char* hash) {
    TRACE_CALL;

    if (hash_size != SHA256_DIGEST_LENGTH) {
        LOG_ERROR("incorrect sha256 buffer size");
        return 0;
    }

    if (buf_size < 1) {
        LOG_ERROR("incorrect buffer size");
        return 0;
    }


    LOG_DEBUG("buffer size: " << buf_size << " hash size: " << hash_size << "hash: " << hash);

    SHA256((unsigned char*) buf, buf_size, hash);
    std::stringstream ss;
    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++)
    {
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
    }

    LOG_DEBUG(ss.str());

    return hash_size;
}
