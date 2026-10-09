#ifndef TIN_RENDERER_OBJECTS_MESH_HPP
#define TIN_RENDERER_OBJECTS_MESH_HPP

#include "Tin/Renderer/DataStructures/Vertex.hpp"
#include "Tin/Renderer/DataStructures/Material.hpp"
#include "Tin/Renderer/DataStructures/Transform.hpp"

#include "Tin/Renderer/Resources/Shader.hpp"

namespace Tin {
    namespace Enum {
		enum class Shape {
			Custom,

			Block,
			Pyramid,
		};
	}

    class Mesh {
    public:
        Material* material;
        Transform transform;

        Mesh(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices, Material& material);

        Mesh(const Enum::Shape& shape, Material& material);

        // Destroys the mesh
        void Destroy();

        // Changes the mesh data
        void Reload(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices);
        // Changes the mesh shape
        void SetShape(const Enum::Shape& shape);

        // Returns the mesh vertices
        const std::vector<Vertex>& GetVertices() const;
        // Returns the amount of vertices the mesh has
        uint32_t GetVerticesCount() const;
        // Returns the mesh indices
        const std::vector<uint32_t>& GetIndices() const;
        // Returns the amount of indices the mesh has
        uint32_t GetIndicesCount() const;
        // Returns the mesh shape
        Enum::Shape GetShape() const;
        // Returns the mesh vertex array buffer object
        uint32_t GetVao() const;
    private:
        // Buffer ids
        uint32_t m_Vao = 0;
        uint32_t m_Vbo = 0;
        uint32_t m_Ebo = 0;

        // Mesh data
        std::vector<Vertex> m_vertices;
        std::vector<uint32_t> m_indices;
        Enum::Shape m_shape;

        // Helper function to create the VAO, VBO and EBO buffers
        void CreateBuffers();
        // Helper function to reload the buffers
        void ReloadBuffers(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices);
        // Helper function to change the shape
		void ChangeShape(Enum::Shape shape);
    };
}

#endif