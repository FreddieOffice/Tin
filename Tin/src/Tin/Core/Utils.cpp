#include "Tin/TinPCH.hpp"
#include "Tin/Core/Utils.hpp"

namespace Tin::Utils {
    std::string ReadFile(const std::string& filepath) {
        std::ifstream file(filepath, std::ios::binary | std::ios::ate);

        if (file) {
            std::string contents;
            contents.resize(file.tellg());

            file.seekg(0, std::ios::beg);
            file.read(&contents[0], contents.size());
            file.close();

            return contents;
        } else {
            Logger::Log(Logger::Level::Error, "Tin", ("Failed to read file " + filepath));
            return "";
        }
    }
}
