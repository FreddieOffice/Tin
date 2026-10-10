#include "Tin/TinPCH.hpp"
#include "Tin/Renderer/Objects/Mesh.hpp"

#include "Tin/Core/Logger.hpp"

namespace Tin {
    Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices, Material& material) : material(&material), m_vertices(vertices), m_indices(indices), m_shape(Enum::Shape::Custom) {
        CreateBuffers();
    }

	Mesh::Mesh(const Enum::Shape& shape, Material& material) : material(&material), m_shape(shape) {
		if (shape == Enum::Shape::Custom) {
			Logger::Log(Logger::Level::Warning, "Tin", "Cannot make a mesh with shape \"custom\", it is only for meshes that have custom mesh data");
			return;
		}

		ChangeShape(shape);
		CreateBuffers();
	}

    void Mesh::Destroy() {
        glDeleteVertexArrays(1, &m_Vao);
		glDeleteBuffers(1, &m_Vbo);
		glDeleteBuffers(1, &m_Ebo);
        m_indices.clear();
        m_vertices.clear();
    }

    void Mesh::Reload(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices) {
        m_vertices = vertices;
        m_indices = indices;
		m_shape = Enum::Shape::Custom;
        ReloadBuffers(vertices, indices);
    }

	void Mesh::SetShape(const Enum::Shape& shape) {
		if (shape == Enum::Shape::Custom) {
			Logger::Log(Logger::Level::Warning, "Tin", "Cannot set shape of mesh to be \"custom\", it is only for meshes that have custom mesh data");
			return;
		}

		SetShape(shape);
		m_shape = shape;
		ReloadBuffers(m_vertices, m_indices);
	}

    const std::vector<Vertex>& Mesh::GetVertices() const {
        return m_vertices;
    }

	uint32_t Mesh::GetVerticesCount() const {
		return m_vertices.size();
	}

    const std::vector<uint32_t>& Mesh::GetIndices() const {
        return m_indices;
    }

	uint32_t Mesh::GetIndicesCount() const {
		return m_indices.size();
	}

	Enum::Shape Mesh::GetShape() const {
		return m_shape;
	}

	uint32_t Mesh::GetVao() const {
		return m_Vao;
	}

	// Helper functions

    void Mesh::CreateBuffers() {
       // Creating the buffers
		glGenVertexArrays(1, &m_Vao);
		glGenBuffers(1, &m_Vbo);
		glGenBuffers(1, &m_Ebo);

		// Binding the buffers and sending data
		glBindVertexArray(m_Vao);

		glBindBuffer(GL_ARRAY_BUFFER, m_Vbo);
		glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Vertex), m_vertices.data(), GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(uint32_t), m_indices.data(), GL_STATIC_DRAW);

		// Link attributes to the VAO
		// Position
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, Position)));
		glEnableVertexAttribArray(0);

		// Texture coordinates
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, TextureUV)));
		glEnableVertexAttribArray(1);
    }

    void Mesh::ReloadBuffers(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices) {
        // VBO update
		glBindBuffer(GL_ARRAY_BUFFER, m_Vbo);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW); // Orphan the buffer
		glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());

		// EBO update
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint32_t), nullptr, GL_DYNAMIC_DRAW); // Orphan the buffer
		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, indices.size() * sizeof(uint32_t), indices.data());
    }

	void Mesh::ChangeShape(Enum::Shape shape) {
		switch (shape) {
		case Enum::Shape::Block:
			m_vertices = {
				// Front face
				Vertex(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec2(0.0f, 0.0f)),
				Vertex(glm::vec3( 0.5f, -0.5f, -0.5f), glm::vec2(1.0f, 0.0f)),
				Vertex(glm::vec3( 0.5f,  0.5f, -0.5f), glm::vec2(1.0f, 1.0f)),
				Vertex(glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec2(0.0f, 1.0f)),

				// Back face
				Vertex(glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec2(0.0f, 0.0f)),
				Vertex(glm::vec3( 0.5f, -0.5f,  0.5f), glm::vec2(1.0f, 0.0f)),
				Vertex(glm::vec3( 0.5f,  0.5f,  0.5f), glm::vec2(1.0f, 1.0f)),
				Vertex(glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec2(0.0f, 1.0f)),

				// Left face
				Vertex(glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec2(0.0f, 0.0f)),
				Vertex(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec2(1.0f, 0.0f)),
				Vertex(glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec2(1.0f, 1.0f)),
				Vertex(glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec2(0.0f, 1.0f)),

				// Right face
				Vertex(glm::vec3( 0.5f, -0.5f, -0.5f), glm::vec2(0.0f, 0.0f)),
				Vertex(glm::vec3( 0.5f,  0.5f, -0.5f), glm::vec2(1.0f, 0.0f)),
				Vertex(glm::vec3( 0.5f,  0.5f,  0.5f), glm::vec2(1.0f, 1.0f)),
				Vertex(glm::vec3( 0.5f, -0.5f,  0.5f), glm::vec2(0.0f, 1.0f)),

				// Bottom face
				Vertex(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec2(0.0f, 0.0f)),
				Vertex(glm::vec3( 0.5f, -0.5f, -0.5f), glm::vec2(1.0f, 0.0f)),
				Vertex(glm::vec3( 0.5f, -0.5f,  0.5f), glm::vec2(1.0f, 1.0f)),
				Vertex(glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec2(0.0f, 1.0f)),

				// Top face
				Vertex(glm::vec3( 0.5f,  0.5f, -0.5f), glm::vec2(0.0f, 0.0f)),
				Vertex(glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec2(1.0f, 0.0f)),
				Vertex(glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec2(1.0f, 1.0f)),
				Vertex(glm::vec3( 0.5f,  0.5f,  0.5f), glm::vec2(0.0f, 1.0f))
			};

			m_indices = {
				 0,  3,  2,  2,  1,  0, // Front
				 4,  5,  6,  6,  7,  4, // Back
				11,  8,  9,  9, 10, 11, // Left
				12, 13, 14, 14, 15, 12, // Right
				16, 17, 18, 18, 19, 16, // Bottom
				20, 21, 22, 22, 23, 20  // Top
			};

			break;
		case Enum::Shape::Pyramid:
			m_vertices = {
				// Front face
				Vertex(glm::vec3( 0.0f,  0.5f,  0.0f),  glm::vec2(0.5f, 1.0f)),
				Vertex(glm::vec3(-0.5f, -0.5f,  0.5f),  glm::vec2(0.0f, 0.0f)),
				Vertex(glm::vec3( 0.5f, -0.5f,  0.5f),  glm::vec2(1.0f, 0.0f)),

				// Right face
				Vertex(glm::vec3( 0.0f,  0.5f,  0.0f), glm::vec2(0.5f, 1.0f)),
				Vertex(glm::vec3( 0.5f, -0.5f,  0.5f), glm::vec2(0.0f, 0.0f)),
				Vertex(glm::vec3( 0.5f, -0.5f, -0.5f), glm::vec2(1.0f, 0.0f)),

				// Back face
				Vertex(glm::vec3( 0.0f,  0.5f,  0.0f), glm::vec2(0.5f, 1.0f)),
				Vertex(glm::vec3( 0.5f, -0.5f, -0.5f), glm::vec2(0.0f, 0.0f)),
				Vertex(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec2(1.0f, 0.0f)),

				// Left face
				Vertex(glm::vec3( 0.0f,  0.5f,  0.0f), glm::vec2(0.5f, 1.0f)),
				Vertex(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec2(0.0f, 0.0f)),
				Vertex(glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec2(1.0f, 0.0f)),

				// Bottom face (square base)
				Vertex(glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec2(0.0f, 0.0f)),
				Vertex(glm::vec3( 0.5f, -0.5f,  0.5f), glm::vec2(1.0f, 0.0f)),
				Vertex(glm::vec3( 0.5f, -0.5f, -0.5f), glm::vec2(1.0f, 1.0f)),
				Vertex(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec2(0.0f, 1.0f))
			};

			m_indices = {
				 0,  1,  2,
				 3,  4,  5,
				 6,  7,  8,
				 9, 10, 11,
				12, 14, 13,
				12, 15, 14
			};

			break;
		default:
			break;
		}
	}
}
