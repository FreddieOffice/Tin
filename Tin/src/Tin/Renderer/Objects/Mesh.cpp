#include "Tin/TinPCH.hpp"
#include "Tin/Renderer/Objects/Mesh.hpp"

#include "Tin/Core/Logger.hpp"

namespace Tin {
    Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices, const Shader& shader, const Material& material) : shader(shader), material(material), m_vertices(vertices), m_indices(indices), m_shape(Enum::Shape::CUSTOM) {
        CreateBuffers();
    }

	Mesh::Mesh(const Enum::Shape& shape, const Shader& shader, const Material& material) : shader(shader), material(material), m_shape(shape) {
		if (shape == Enum::Shape::CUSTOM) {
			Logger::Log(Logger::Level::Warning, "Tin", "Cannot make a mesh with shape \"custom\", it is only for meshes that have custom mesh data");
			return;
		}

		ChangeShape(shape);
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

    void Mesh::Reload(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices) {
        m_vertices = vertices;
        m_indices = indices;
		m_shape = Enum::Shape::CUSTOM;
        ReloadBuffers(vertices, indices);
    }

	void Mesh::SetShape(const Enum::Shape& shape) {
		if (shape == Enum::Shape::CUSTOM) {
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

    const std::vector<uint32_t>& Mesh::GetIndices() const {
        return m_indices;
    }

	Enum::Shape Mesh::GetShape() const {
		return m_shape;
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

	void Mesh::ChangeShape(Enum::Shape shape) {
		switch (shape) {
		case Enum::Shape::PLANE:
			m_vertices = {
            	Vertex(glm::vec3(-1.0f, 0.0f,  1.0f), glm::vec2(0.0f, 0.0f)),
            	Vertex(glm::vec3( 1.0f, 0.0f,  1.0f), glm::vec2(1.0f, 0.0f)),
            	Vertex(glm::vec3( 1.0f, 0.0f, -1.0f), glm::vec2(1.0f, 1.0f)),
            	Vertex(glm::vec3(-1.0f, 0.0f, -1.0f), glm::vec2(0.0f, 1.0f))
			};

			m_indices = {
				0, 1, 2,
				0, 2, 3
			};

			break;
		case Enum::Shape::BLOCK:
			m_vertices = {
				Vertex(glm::vec3(-0.5f, -0.5f, 0.5f),  glm::vec2(0.0f, 0.0f)),
				Vertex(glm::vec3( 0.5f, -0.5f, 0.5f),  glm::vec2(1.0f, 0.0f)),
				Vertex(glm::vec3( 0.5f,  0.5f, 0.5f),  glm::vec2(1.0f, 1.0f)),
				Vertex(glm::vec3(-0.5f,  0.5f, 0.5f),  glm::vec2(0.0f, 1.0f)),

				Vertex(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec2(1.0f, 0.0f)),
				Vertex(glm::vec3( 0.5f, -0.5f, -0.5f), glm::vec2(0.0f, 0.0f)),
				Vertex(glm::vec3( 0.5f,  0.5f, -0.5f), glm::vec2(0.0f, 1.0f)),
				Vertex(glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec2(1.0f, 1.0f)),

				Vertex(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec2(0.0f, 0.0f)),
				Vertex(glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec2(0.0f, 1.0f)),
				Vertex(glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec2(1.0f, 1.0f)),
				Vertex(glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec2(1.0f, 0.0f)),

				Vertex(glm::vec3(0.5f, -0.5f, -0.5f),  glm::vec2(1.0f, 0.0f)),
				Vertex(glm::vec3(0.5f,  0.5f, -0.5f),  glm::vec2(1.0f, 1.0f)),
				Vertex(glm::vec3(0.5f,  0.5f,  0.5f),  glm::vec2(0.0f, 1.0f)),
				Vertex(glm::vec3(0.5f, -0.5f,  0.5f),  glm::vec2(0.0f, 0.0f)),

				Vertex(glm::vec3(-0.5f, 0.5f,  0.5f),  glm::vec2(0.0f, 0.0f)),
				Vertex(glm::vec3( 0.5f, 0.5f,  0.5f),  glm::vec2(1.0f, 0.0f)),
				Vertex(glm::vec3( 0.5f, 0.5f, -0.5f),  glm::vec2(1.0f, 1.0f)),
				Vertex(glm::vec3(-0.5f, 0.5f, -0.5f),  glm::vec2(0.0f, 1.0f)),

				Vertex(glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec2(0.0f, 1.0f)),
				Vertex(glm::vec3( 0.5f, -0.5f,  0.5f), glm::vec2(1.0f, 1.0f)),
				Vertex(glm::vec3( 0.5f, -0.5f, -0.5f), glm::vec2(1.0f, 0.0f)),
				Vertex(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec2(0.0f, 0.0f))
			};

			m_indices = {
				0, 1, 2, 2, 3, 0,
				4, 5, 6, 6, 7, 4,
				8, 9, 10, 10, 11, 8,
				12, 13, 14, 14, 15, 12,
				16, 17, 18, 18, 19, 16,
				20, 21, 22, 22, 23, 20
			};

			break;
		case Enum::Shape::PYRAMID:
			m_vertices = {
				Vertex(glm::vec3(-0.5f, -0.5f, 0.5f),  glm::vec2(0.0f, 0.0f)),
				Vertex(glm::vec3( 0.5f, -0.5f, 0.5f),  glm::vec2(1.0f, 0.0f)),
				Vertex(glm::vec3( 0.0f,  0.5f, 0.0f),  glm::vec2(0.5f, 1.0f)),

				Vertex(glm::vec3(0.5f, -0.5f,  0.5f),  glm::vec2(0.0f, 0.0f)),
				Vertex(glm::vec3(0.5f, -0.5f, -0.5f),  glm::vec2(1.0f, 0.0f)),
				Vertex(glm::vec3(0.0f,  0.5f,  0.0f),  glm::vec2(0.5f, 1.0f)),

				Vertex(glm::vec3( 0.5f, -0.5f, -0.5f), glm::vec2(0.0f, 0.0f)),
				Vertex(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec2(1.0f, 0.0f)),
				Vertex(glm::vec3( 0.0f,  0.5f,  0.0f), glm::vec2(0.5f, 1.0f)),

				Vertex(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec2(0.0f, 0.0f)),
				Vertex(glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec2(1.0f, 0.0f)),
				Vertex(glm::vec3( 0.0f,  0.5f,  0.0f), glm::vec2(0.5f, 1.0f)),

				Vertex(glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec2(0.0f, 0.0f)),
				Vertex(glm::vec3( 0.5f, -0.5f,  0.5f), glm::vec2(1.0f, 0.0f)),
				Vertex(glm::vec3( 0.5f, -0.5f, -0.5f), glm::vec2(1.0f, 1.0f)),
				Vertex(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec2(0.0f, 1.0f))
			};

			m_indices = {
				0, 1, 2,
				3, 4, 5,
				6, 7, 8,
				9, 10, 11,
				12, 13, 14,
				14, 15, 12
			};

			break;
		}
	}
}