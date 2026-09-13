#ifndef TIN_RENDERER_OBJECTS_MESH_HPP
#define TIN_RENDERER_OBJECTS_MESH_HPP

#include "Tin/Renderer/DataStructures/Vertex.hpp"
#include "Tin/Renderer/DataStructures/Material.hpp"
#include "Tin/Renderer/DataStructures/Transform.hpp"

#include "Tin/Renderer/Resources/Shader.hpp"

namespace Tin {
    class Mesh {
    public:
        Shader MeshShader;
        Material Mat;
        Transform T;
        Mesh(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices, const Shader& shader, const Tin::Material& material);

        // Draws the mesh
        void Draw();
        // Destroys the mesh
        void Destroy();

        // Returns the mesh vertices
        const std::vector<Vertex>& GetVertices() const;
        // Returns the mesh indices
        const std::vector<uint32_t>& GetIndices() const;
    private:
        // Buffer ids
        uint32_t m_vao, m_vbo, m_ebo;

        // Mesh data
        std::vector<Vertex> m_vertices;
        std::vector<uint32_t> m_indices;

        // Helper function to create the VAO, VBO and EBO buffers
        void CreateBuffers();
    };
}

#endif