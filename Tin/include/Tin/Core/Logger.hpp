#pragma once

#include <string>

namespace Tin {
    namespace Logger {
        enum class Level {
            Info,
            Warning,
            Error
        };

        void Log(Level level, const std::string& location, const std::string& message);
    }
}
