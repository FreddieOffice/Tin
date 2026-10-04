#include "Tin/TinPCH.hpp"
#include "Tin/Renderer/Objects/Skybox.hpp"

#include "Tin/Core/Logger.hpp"

namespace Tin {
    Skybox::Skybox(const std::vector<std::string>& faces) : m_faces(faces) {
        // Generate the cubemap texture
        glGenTextures(1, &m_cubemapId);
        glBindTexture(GL_TEXTURE_CUBE_MAP, m_cubemapId);

        // Set the parameters
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);  

        // Create textures for the faces
        stbi_set_flip_vertically_on_load(false);

        for (int32_t i = 0; i < faces.size(); i++) {
            int32_t width, height;
            unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, nullptr, 3);

            if (data) {
                glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
                Logger::Log(Logger::Level::Info, "Tin", ("Image for skybox with filename " + faces[i] + " was successfully created"));
            } else {
                Logger::Log(Logger::Level::Error, "Tin", ("Failed to load image for skybox with filename " + faces[i] + ":\n" + stbi_failure_reason()));
            }

            stbi_image_free(data);
        }

        Logger::Log(Logger::Level::Info, "Tin", "Successfully created skybox");
    }

    void Skybox::Destroy() {
        glDeleteTextures(1, &m_cubemapId);
    }

    std::vector<std::string> Skybox::GetFaces() const {
        return m_faces;
    }

    uint32_t Skybox::GetCubemapId() const {
        return m_cubemapId;
    }
}