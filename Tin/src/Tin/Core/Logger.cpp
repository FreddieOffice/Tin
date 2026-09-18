#include "Tin/TinPCH.hpp"
#include "Tin/Core/Logger.hpp"

namespace Tin {
    namespace Logger {
        namespace {
            static constexpr uint32_t typeColors[] = {TIN_GREEN, TIN_YELLOW, TIN_RED};
            static constexpr uint32_t messageColors[] = {TIN_DARK_GREEN, TIN_DARK_YELLOW, TIN_DARK_RED};

            std::mutex logMutex;

            void SetTextColor(uint32_t color) {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
            }

            const char* LevelToString(Level level) {
                switch (level) {
                    case Level::Info: return "Info";
                    case Level::Warning: return "Warning";
                    case Level::Error: return "Error";
                }
                return "";
            }

            std::string CurrentDateTime() {
                auto now = std::chrono::system_clock::now();
                std::time_t time = std::chrono::system_clock::to_time_t(now);
                
                // Get time in the local timezone
                std::tm local_tm;
                localtime_s(&local_tm, &time);

                // Get the string
                std::ostringstream oss;
                oss << std::put_time(&local_tm, "%d-%m-%Y %H:%M:%S");

                return oss.str();
            }
        }

        void Log(Level level, const std::string& location, const std::string& message) {
            std::lock_guard<std::mutex> lock(logMutex);

            SetTextColor(TIN_WHITE);
            std::cout << CurrentDateTime() << " " << location << ": "; // Location is where the error comes from
            SetTextColor(typeColors[static_cast<std::uint32_t>(level)]);
            std::cout << LevelToString(level) << ": ";
            SetTextColor(messageColors[static_cast<std::uint32_t>(level)]);
            std::cout << message << "\n";
            SetTextColor(TIN_WHITE);
        }
    }
}