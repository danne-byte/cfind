#include "io.hpp"

#include <cstdio>
#include <stdexcept>

io::io_error::io_error(const char* message) : std::runtime_error(message) {

}

io::io_error::io_error(const std::string& message) : std::runtime_error(message) {

}


std::size_t io::read_file(const std::string& filename, std::size_t offset, std::size_t size, io::Binary& data) {
    std::FILE* fp = std::fopen(filename.c_str(), "rb");

    if (!fp) {
        throw io_error("failed to open file: " + filename);
    }

    auto seek_failed = std::fseek(fp, static_cast<long>(offset), SEEK_SET);

    if (seek_failed) {
        throw io_error("failed to seek file: " + filename);
    }

    auto bytes_read = std::fread(&data[0], sizeof data[0], size, fp);

    if( bytes_read < size) {
        if (std::feof(fp)) {
            std::fclose(fp);
            throw io_error("failed to read end of file: " + filename);
        }

        if (std::ferror(fp)) {
            std::fclose(fp);
            throw io_error("failed to read: " + filename);
        }
    }

    std::fclose(fp);

    return bytes_read;
}
