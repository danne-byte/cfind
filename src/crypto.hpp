#ifndef CRYPTO_HPP_INCLUDED
#define CRYPTO_HPP_INCLUDED

#include <cstddef>
#include <vector>

#include "io.hpp"

namespace crypto {

    typedef std::vector<unsigned char> Digest;

    Digest sha256(const io::Binary& data);

}


#endif // CRYPTO_HPP_INCLUDED
