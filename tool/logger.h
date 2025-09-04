#ifndef LOGGER_H
#define LOGGER_H

#include <boost/log/trivial.hpp>
#include <string>

// Định nghĩa macro cho log
#define LOG(severity) BOOST_LOG_TRIVIAL(severity)

namespace logger {
    void init_logging();
}

#endif // LOGGER_H