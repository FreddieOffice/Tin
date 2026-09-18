#ifndef TIN_CORE_LOGGER_HPP
#define TIN_CORE_LOGGER_HPP

#define TIN_DARK_GREEN 2
#define TIN_DARK_YELLOW 6
#define TIN_DARK_RED 4
#define TIN_GREEN 10
#define TIN_YELLOW 14
#define TIN_RED 12
#define TIN_WHITE 15

#include <string>

namespace Tin {
    namespace Logger {
        enum class Level {
            Info = 0, Warning, Error
        };

        void Log(Level level, const std::string& location, const std::string& message);
    }
}

#endif