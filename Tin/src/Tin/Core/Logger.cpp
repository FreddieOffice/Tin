#include "Tin/TinPCH.hpp"
#include "Tin/Core/Logger.hpp"

namespace Tin {
    namespace Logger {
        namespace {
            uint8_t DarkGreen = 2;
            uint8_t DarkRed = 4;
            uint8_t DarkYellow = 6;
            uint8_t Green = 10;
            uint8_t Red = 12;
            uint8_t Yellow = 14;
            uint8_t White = 15;

            std::array<uint8_t, 3> typeColors = {Green, Yellow, Red};
            std::array<uint8_t, 3> messageColors = {DarkGreen, DarkYellow, DarkRed};

            std::mutex logMutex;

            void SetTextColor(uint8_t color) {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
            }

            std::string LevelToString(Level level) {
                switch (level) {
                    case Level::Info: return "Info";
                    case Level::Warning: return "Warning";
                    case Level::Error: return "Error";
                }
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

            SetTextColor(White);
            std::cout << CurrentDateTime() << " " << location << ": "; // Location is where the error comes from
            SetTextColor(typeColors[static_cast<uint8_t>(level)]);
            std::cout << LevelToString(level) << ": ";
            SetTextColor(messageColors[static_cast<uint8_t>(level)]);
            std::cout << message << "\n";
            SetTextColor(White);
        }
    }
}