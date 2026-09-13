#ifndef TIN_RENDERER_RESOURCES_SHADER_HPP
#define TIN_RENDERER_RESOURCES_SHADER_HPP

namespace Tin {
    class Shader {
    public:
        Shader(const std::string& vertexShaderSource, const std::string& fragmentShaderSource);

        // Uses the shader
        void Use() const;
        // Destroys the shader
        void Destroy() const;
        
        // Changes the shader to have new vertex and fragment code
        void Reload(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);

        // Sets an int uniform
        void SetUniformInt(const std::string& name, int32_t x) const;
        // Sets an ivec2 uniform
		void SetUniformIvec2(const std::string& name, const glm::ivec2& ivec2) const;
        // Sets an ivec3 uniform
		void SetUniformIvec3(const std::string& name, const glm::ivec3& ivec3) const;
        // Sets an ivec4 uniform
		void SetUniformIvec4(const std::string& name, const glm::ivec4& ivec4) const;

        // Sets an uint uniform
		void SetUniformUint(const std::string& name, uint32_t x) const;
        // Sets an uvec2 uniform
		void SetUniformUvec2(const std::string& name, const glm::uvec2& uvec2) const;
        // Sets an uvec3 uniform
		void SetUniformUvec3(const std::string& name, const glm::uvec3& uvec3) const;
        // Sets an uvec4 uniform
		void SetUniformUvec4(const std::string& name, const glm::uvec4& uvec4) const;

        // Sets a float uniform
		void SetUniformFloat(const std::string& name, float x) const;
        // Sets a vec2 uniform
		void SetUniformVec2(const std::string& name, const glm::vec2& vec2) const;
        // Sets a vec3 uniform
		void SetUniformVec3(const std::string& name, const glm::vec3& vec3) const;
        // Sets a vec4 uniform
		void SetUniformVec4(const std::string& name, const glm::vec4& vec4) const;

        // Sets a mat2 uniform
        void SetUniformMat2(const std::string& name, const glm::mat2& mat2) const;
        // Sets a mat3 uniform
        void SetUniformMat3(const std::string& name, const glm::mat3& mat3) const;
        // Sets a mat4 uniform
		void SetUniformMat4(const std::string& name, const glm::mat4& mat4) const;

        // Returns the shader id
        uint32_t GetID() const;
    private:
        uint32_t m_id;

        // Helper function to create a shader program
        void CreateProgram(const std::string& vertexShaderSource, const std::string& fragmentShaderSource);
        // Helper function to create a shader
        uint32_t CreateShader(uint32_t type, const char* source) const;
        // Helper function to get uniform location
        int32_t GetUniformLocation(const std::string& name) const;
    };
}

#endif