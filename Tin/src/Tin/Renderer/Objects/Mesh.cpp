#include "Tin/TinPCH.hpp"
#include "Tin/Renderer/Objects/Mesh.hpp"

#include "Tin/Core/Logger.hpp"

namespace Tin {
    Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices, const Tin::Shader& shader, const Tin::Material& material) : shader(shader), m_vertices(vertices), m_indices(indices), material(material) {
        CreateBuffers();
    }

    void Mesh::Draw() {
        // Set uniforms
        shader.Use();
		shader.SetUniformMat4("Model", transform.GetModelMatrix());

		shader.SetUniformVec3("Color", glm::vec3(material.color.r, material.color.g, material.color.b));
		// Check if the material has a color map
		if (!material.HasColorMap()) {
			shader.SetUniformInt("HasColorMap", 0);
		}
		else {
			shader.SetUniformInt("HasColorMap", 1);
			material.colorMap->TextureUnit(shader, "ColorMap");
			material.colorMap->Bind();
		}

		// Draw
        glBindVertexArray(m_vao);
		glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 0);
    }

    void Mesh::Destroy() {
        glDeleteVertexArrays(1, &m_vao);
		glDeleteBuffers(1, &m_vbo);
		glDeleteBuffers(1, &m_ebo);
        m_indices.clear();
        m_vertices.clear();
    }

    void Mesh::Reload(const std::vector<Tin::Vertex>& vertices, const std::vector<uint32_t>& indices) {
        m_vertices = vertices;
        m_indices = indices;
        ReloadBuffers(vertices, indices);
    }

    const std::vector<Vertex>& Mesh::GetVertices() const {
        return m_vertices;
    }

    const std::vector<uint32_t>& Mesh::GetIndices() const {
        return m_indices;
    }

    void Mesh::CreateBuffers() {
       // Creating the buffers
		glGenVertexArrays(1, &m_vao);
		glGenBuffers(1, &m_vbo);
		glGenBuffers(1, &m_ebo);

		// Binding the buffers and sending data
		glBindVertexArray(m_vao);

		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Vertex), m_vertices.data(), GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(uint32_t), m_indices.data(), GL_STATIC_DRAW);

		// Link attributes to the VAO
		// Position
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Position));
		glEnableVertexAttribArray(0);

		// Texture coordinates
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TextureUV));
		glEnableVertexAttribArray(1);
    }

    void Mesh::ReloadBuffers(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices) {
        // VBO update
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW); // Orphan the buffer
		glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());

		// EBO update
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint32_t), nullptr, GL_DYNAMIC_DRAW); // Orphan the buffer
		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, indices.size() * sizeof(uint32_t), indices.data());
    }
}