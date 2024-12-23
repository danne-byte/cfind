#ifndef LOG_HPP_INCLUDED
#define LOG_HPP_INCLUDED

#include <sstream>
#include <string>

namespace logger {

#define LOG_DEBUG(msg) {std::ostringstream _s; _s << msg; log_print("DEBUG", __FILE__, __FUNCTION__, __LINE__, _s.str());}
#define LOG_WARNING(msg) {std::ostringstream _s; _s << msg; log_print("WARNING", __FILE__, __FUNCTION__, __LINE__, _s.str());}
#define LOG_ERROR(msg) {std::ostringstream _s; _s << msg; log_print("ERROR", __FILE__, __FUNCTION__, __LINE__, _s.str());}
#define TRACE_CALL log_print("TRACE", __FILE__, __FUNCTION__, __LINE__, "");

void log_print(const std::string& type, const std::string& file, const std::string& func, int line, const std::string& msg);

};

#endif // LOG_HPP_INCLUDED
