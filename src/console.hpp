#ifndef CONSOLE_HPP
#define CONSOLE_HPP

#include <string>

#include "cfind.hpp"

namespace cfind {

    class Console {
    public:
        void print_result(std::list<cfind::PathEntryResult>& result_list, const Options& options);
        void print_usage();
    };
}


#endif // CONSOLE_HPP
