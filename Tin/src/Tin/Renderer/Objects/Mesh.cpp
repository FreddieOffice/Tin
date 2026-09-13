#include "Tin/TinPCH.hpp"
#include "Tin/Renderer/Objects/Mesh.hpp"

#include "Tin/Core/Logger.hpp"

namespace Tin {
    Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices, const Tin::Shader& shader, const Tin::Material& material) : MeshShader(shader), m_vertices(vertices), m_indices(indices), Mat(material) {
        CreateBuffers();
    }

    void Mesh::Draw() {
        MeshShader.Use();

        MeshShader.SetUniformMat4("Model", T.GetModelMatrix());

		MeshShader.SetUniformVec3("Color", glm::vec3(Mat.MatColor.r, Mat.MatColor.g, Mat.MatColor.b));

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
		glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Tin::Vertex), m_vertices.data(), GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(uint32_t), m_indices.data(), GL_STATIC_DRAW);

		// Link attributes to the VAO
		// Position
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Tin::Vertex), (void*)offsetof(Tin::Vertex, Position));
		glEnableVertexAttribArray(0);

		// Texture coordinates
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Tin::Vertex), (void*)offsetof(Tin::Vertex, TextureUV));
		glEnableVertexAttribArray(1);
    }
}