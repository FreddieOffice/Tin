#pragma once

#include "Tin/Renderer/DataStructures/Vertex.hpp"
#include "Tin/Renderer/DataStructures/Material.hpp"
#include "Tin/Renderer/DataStructures/Transform.hpp"

#include "Tin/Renderer/Resources/Shader.hpp"

namespace Tin {
    enum class Shape {
        Custom,

        Block,
        Pyramid,
    };

    class Mesh {
    public:
        Material* material;
        Transform transform;

        Mesh(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices, Material& material);

        Mesh(const Shape& shape, Material& material);

        // Destroys the mesh
        void Destroy();

        // Changes the mesh data
        void Reload(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices);
        // Changes the mesh shape
        void SetShape(const Shape& shape);

        // Returns the mesh vertices
        [[nodiscard]] const std::vector<Vertex>& GetVertices() const;
        // Returns the amount of vertices the mesh has
        [[nodiscard]] uint32_t GetVerticesCount() const;
        // Returns the mesh indices
        [[nodiscard]] const std::vector<uint32_t>& GetIndices() const;
        // Returns the amount of indices the mesh has
        [[nodiscard]] uint32_t GetIndicesCount() const;
        // Returns the mesh shape
        [[nodiscard]] Shape GetShape() const;
        // Returns the mesh vertex array buffer object
        [[nodiscard]] uint32_t GetVao() const;
    private:
        // Buffer ids
        uint32_t m_vao = 0;
        uint32_t m_vbo = 0;
        uint32_t m_ebo = 0;

        // Mesh data
        std::vector<Vertex> m_vertices;
        std::vector<uint32_t> m_indices;
        Shape m_shape;

        // Helper function to create the VAO, VBO and EBO buffers
        void CreateBuffers();
        // Helper function to reload the buffers
        void ReloadBuffers(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices);
        // Helper function to change the shape
		void ChangeShape(Shape shape);
    };
}
