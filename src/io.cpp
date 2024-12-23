#include "io.hpp"

#include <fstream>
#include <iostream>

#include "log.hpp"
using namespace logger;

size_t io::read_file_content(const std::string& filename, size_t buf_size, char* buf) {
        TRACE_CALL;
        LOG_DEBUG("size: " << buf_size << " open path: " << filename);

        std::ifstream in(filename, std::ios::binary | std::ios::in);

        if (in.bad()) {
            LOG_ERROR("io error reading");
        }

        if (in.eof()) {
            LOG_ERROR("eof reading");
        }

        if (in.fail()) {
            LOG_ERROR("non integer data reading");
        }

        if (!in.is_open()) {
            LOG_ERROR("failed to open " << filename);
            return 0;
        }

        in.read(buf, static_cast<long>(buf_size));
        auto bytes_read = in.gcount();
        LOG_DEBUG("read bytes " << bytes_read);

        return static_cast<unsigned long>(bytes_read);
    }
