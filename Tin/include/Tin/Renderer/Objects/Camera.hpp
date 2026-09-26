#ifndef TIN_RENDERER_OBJECTS_CAMERA_HPP
#define TIN_RENDERER_OBJECTS_CAMERA_HPP

#include "Tin/Renderer/Resources/Shader.hpp"

#include "glm/glm.hpp"

namespace Tin {
	class Camera {
	public:
		glm::vec3 Position, Orientation;
		float FOV, NearPlane, FarPlane;

		Camera(glm::ivec2 viewportSize, glm::vec3 position, glm::vec3 orientation, float fov = 90.0f, float nearPlane = 0.1f, float farPlane = 1000.0f);

		// Updates the projection and view matrix
		// Uniforms required: CamProjection (mat4), CamView (mat4)
		void UpdateMatrix(Shader& shader, glm::mat4 projectionMatrix, glm::mat4 viewMatrix) const;

		// Sets the camera viewport size
		void SetViewportSize(glm::ivec2 size);

		// Returns the projection matrix
		glm::mat4 GetProjectionMatrix() const;
		// Returns the view matrix
		glm::mat4 GetViewMatrix() const;
		// Returns the camera viewport size
		glm::ivec2 GetViewportSize() const;
	private:
		glm::ivec2 m_viewportSize;
	};
}

#endif