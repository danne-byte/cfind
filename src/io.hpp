#ifndef IO_HPP_INCLUDED
#define IO_HPP_INCLUDED

#include <string>

namespace io {
    size_t read_file_content(const std::string& filename, size_t buf_size, char* buf);
}


#endif // IO_HPP_INCLUDED
