#include "Tin/TinPCH.hpp"
#include "Tin/Renderer/Resources/Shader.hpp"

#include "Tin/Core/Logger.hpp"
#include "Tin/Core/Utils.hpp"

namespace Tin {
    Shader::Shader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath) {
        CreateProgram(vertexShaderPath, fragmentShaderPath);
    }
    
    void Shader::Use() const {
        glUseProgram(m_Id);
    }

    void Shader::Destroy() const {
        glDeleteProgram(m_Id);
    }

    void Shader::Reload(const std::string& vertexShaderPath, const std::string& fragmentShaderPath) {
        glDeleteProgram(m_Id);
        CreateProgram(vertexShaderPath, fragmentShaderPath);
    }

    void Shader::SetUniformInt(const std::string& name, int32_t x) const {
		glUniform1i(GetUniformLocation(name), x);
	}

	void Shader::SetUniformIvec2(const std::string& name, const glm::ivec2& ivec2) const {
		glUniform2i(GetUniformLocation(name), ivec2.x, ivec2.y);
	}

	void Shader::SetUniformIvec3(const std::string& name, const glm::ivec3& ivec3) const {
		glUniform3i(GetUniformLocation(name), ivec3.x, ivec3.y, ivec3.z);
	}

	void Shader::SetUniformIvec4(const std::string& name, const glm::ivec4& ivec4) const {
		glUniform4i(GetUniformLocation(name), ivec4.x, ivec4.y, ivec4.z, ivec4.w);
	}

	void Shader::SetUniformUint(const std::string& name, uint32_t x) const {
		glUniform1ui(GetUniformLocation(name), x);
	}

	void Shader::SetUniformUvec2(const std::string& name, const glm::uvec2& uvec2) const {
		glUniform2ui(GetUniformLocation(name), uvec2.x, uvec2.y);
	}

	void Shader::SetUniformUvec3(const std::string& name, const glm::uvec3& uvec3) const {
		glUniform3ui(GetUniformLocation(name), uvec3.x, uvec3.y, uvec3.z);
	}

	void Shader::SetUniformUvec4(const std::string& name, const glm::uvec4& uvec4) const {
		glUniform4ui(GetUniformLocation(name), uvec4.x, uvec4.y, uvec4.z, uvec4.w);
	}

	void Shader::SetUniformFloat(const std::string& name, float x) const {
		glUniform1f(GetUniformLocation(name), x);
	}

	void Shader::SetUniformVec2(const std::string& name, const glm::vec2& vec2) const {
		glUniform2f(GetUniformLocation(name), vec2.x, vec2.y);
	}

	void Shader::SetUniformVec3(const std::string& name, const glm::vec3& vec3) const {
		glUniform3f(GetUniformLocation(name), vec3.x, vec3.y, vec3.z);
	}

	void Shader::SetUniformVec4(const std::string& name, const glm::vec4& vec4) const {
		glUniform4f(GetUniformLocation(name), vec4.x, vec4.y, vec4.z, vec4.w);
	}

    void Shader::SetUniformMat2(const std::string& name, const glm::mat2& mat2) const {
		glUniformMatrix2fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(mat2));
	}

    void Shader::SetUniformMat3(const std::string& name, const glm::mat3& mat3) const {
		glUniformMatrix3fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(mat3));
	}

	void Shader::SetUniformMat4(const std::string& name, const glm::mat4& mat4) const {
		glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(mat4));
	}

    uint32_t Shader::GetId() const {
        return m_Id;
    }

    void Shader::CreateProgram(const std::string& vertexShaderSource, const std::string& fragmentShaderSource) {
        uint32_t vertexShader = CreateShader(GL_VERTEX_SHADER, vertexShaderSource.c_str());
        uint32_t fragmentShader = CreateShader(GL_FRAGMENT_SHADER, fragmentShaderSource.c_str());

        // Create the shader program
        m_Id = glCreateProgram();
        glAttachShader(m_Id, vertexShader);
        glAttachShader(m_Id, fragmentShader);
        glLinkProgram(m_Id);

        // Detach and delete the shaders
		glDetachShader(m_Id, vertexShader);
		glDetachShader(m_Id, fragmentShader);
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		// Check link status
		int32_t linked;
		glGetProgramiv(m_Id, GL_LINK_STATUS, &linked);

        if (!linked) {
            // Get info log length
			int32_t length;
			glGetProgramiv(m_Id, GL_INFO_LOG_LENGTH, &length);

            // Length-2 to remove the random blank lines
            std::vector<char> infoLog(length-2);
            glGetProgramInfoLog(m_Id, length-2, nullptr, infoLog.data());

            // Output the info log
            Logger::Log(Logger::Level::Error, "Tin", ("Shader program with id " + std::to_string(m_Id) + " linking error:\n" + infoLog.data()));
            return;
        } else {
            Logger::Log(Logger::Level::Info, "Tin", ("Shader program with id " + std::to_string(m_Id) + " was successfully linked"));
        }
    }

    uint32_t Shader::CreateShader(uint32_t type, const char* source) const {
        uint32_t shader = glCreateShader(type);
        glShaderSource(shader, 1, &source, nullptr);
        glCompileShader(shader);

        // The name of the shader that will be printed when an error is found/when shader is successfully created
		std::string name = "";

        switch (type) {
        case GL_VERTEX_SHADER:
            name = "Vertex shader";
            break;
        case GL_FRAGMENT_SHADER:
            name = "Fragment shader";
            break;
        }

        // Check compile status
        int32_t compiled;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);

        if (!compiled) {
            // Get info log length
            int32_t length;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);

            // Length-2 to remove the random blank lines
            std::vector<char> infoLog(length-2);
            glGetShaderInfoLog(shader, length-2, nullptr, infoLog.data());

            // Output the info log
            Logger::Log(Logger::Level::Error, "Tin", ("Shader compilation error for " + name + " with id " + std::to_string(shader) + ":\n" + infoLog.data()));
        } else {
            Logger::Log(Logger::Level::Info, "Tin", (name + " with id " + std::to_string(shader) + " was successfully compiled"));
        }

        return shader;
    }

    int32_t Shader::GetUniformLocation(const std::string& name) const {
        int32_t location = glGetUniformLocation(m_Id, name.c_str());
        if (location == -1) {
            Logger::Log(Logger::Level::Error, "Tin", ("Failed to get uniform location with name " + name));
        }

        return location;
    }
}