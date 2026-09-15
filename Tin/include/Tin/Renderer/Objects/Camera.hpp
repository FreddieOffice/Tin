#ifndef TIN_RENDERER_OBJECTS_CAMERA_HPP
#define TIN_RENDERER_OBJECTS_CAMERA_HPP

#include "Tin/Renderer/Resources/Shader.hpp"

#include "glm/glm.hpp"

namespace Tin {
	class Camera {
	public:
		glm::vec3 Position, Orientation;
		float FOV, NearPlane, FarPlane;

		Camera(glm::vec2 viewportSize, glm::vec3 position, glm::vec3 orientation, float fov = 90.0f, float nearPlane = 0.1f, float farPlane = 1000.0f);

		// Updates the projection and view matrix
		// Uniforms required: CamProjection (mat4), CamView (mat4)
		void UpdateMatrix(Shader& shader);

		// Sets the camera viewport size
		void SetViewportSize(glm::vec2 size);

		// Returns the projection matrix
		glm::mat4 GetProjectionMatrix() const;
		// Returns the view matrix
		glm::mat4 GetViewMatrix() const;
		// Returns the camera viewport size
		glm::vec2 GetViewportSize() const;
	private:
		glm::vec2 m_viewportSize;
	};
}

#endif