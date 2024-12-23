#include "log.hpp"

#include <iostream>

#include <cstdlib>

namespace {

    enum LogLevel {
        NONE, ERROR, WARNING, DEBUG, TRACE
    };

    LogLevel to_log_level(const std::string& log_level) {
        if (log_level == "ERROR") {
            return LogLevel::ERROR;
        }

        if (log_level == "WARNING") {
            return LogLevel::WARNING;
        }

        if (log_level == "DEBUG") {
            return LogLevel::DEBUG;
        }

        if (log_level == "TRACE") {
            return LogLevel::TRACE;
        }

        return LogLevel::NONE;
    }

    LogLevel to_log_level(const char* p_log_level) {
        if (p_log_level == NULL) {
            return LogLevel::NONE;
        }

        const std::string log_level = p_log_level;

        return to_log_level(log_level);
    }

    LogLevel get_log_level() {
        const char* env_log_level = std::getenv("CFIND_LOG_LEVEL");

        if (env_log_level == NULL) {
            return LogLevel::NONE;
        }

        return to_log_level(env_log_level);
    }

    bool apply_log(const LogLevel& current_log_level, const LogLevel& apply_log_level) {
        return apply_log_level <= current_log_level;
    }
}

namespace logger {

// NOTE: see https://gist.github.com/johntyree/4718393

void log_print(const std::string& type, const std::string& file, const std::string& func, int line, const std::string& msg) {

    if (!apply_log(get_log_level(), to_log_level(type))) {
        return;
    }

    std::cout << "[" << type << "] " << file << "(" << line << "): " << func;

    if (msg.size()) {
        std::cout << "\t" << msg;
    }
    
    std::cout << std::endl;
}

}
