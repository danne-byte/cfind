#ifndef IO_HPP_INCLUDED
#define IO_HPP_INCLUDED

#include <stdexcept>
#include <string>
#include <vector>

namespace io {

    typedef std::vector<unsigned char> Binary;

    class io_error : public std::runtime_error {
    public:
        io_error(const char* message);
        io_error(const std::string& message);
    };

    std::size_t read_file(const std::string& filename, std::size_t offset, std::size_t size, Binary& data);
}


#endif // IO_HPP_INCLUDED
