#include "Tin/TinPCH.hpp"
#include "Tin/Core/Utils.hpp"

#include "Tin/Core/Logger.hpp"

namespace Tin {
    namespace Utils {
        std::string ReadFile(const std::string& filepath) {
            std::ifstream in(filepath, std::ios::binary);

            if (in)
            {
                std::string contents;
                
                in.seekg(0, std::ios::end);
                contents.resize(in.tellg());
                in.seekg(0, std::ios::beg);
                in.read(&contents[0], contents.size());
                in.close();

                return(contents);
            }
            else {
                Logger::Log(Logger::Level::Error, "Tin", ("Failed to get file " + filepath));
            }
        }
    }
}