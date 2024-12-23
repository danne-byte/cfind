#ifndef CRYPTO_HPP_INCLUDED
#define CRYPTO_HPP_INCLUDED

#include <cstddef>

namespace crypto {

    size_t allocate_sha56_buffer(unsigned char** hash);
    size_t make_sha256(char* buf, size_t buf_size, size_t hash_size, unsigned char* hash);

}


#endif // CRYPTO_HPP_INCLUDED
