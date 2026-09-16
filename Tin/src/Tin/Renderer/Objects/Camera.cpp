#include "Tin/TinPCH.hpp"
#include "Tin/Renderer/Objects/Camera.hpp"

namespace Tin {
	Camera::Camera(glm::vec2 viewportSize, glm::vec3 position, glm::vec3 orientation, float fov, float nearPlane, float farPlane) : m_viewportSize(viewportSize), Position(position), Orientation(orientation), FOV(fov), NearPlane(nearPlane), FarPlane(farPlane) {}

	void Camera::UpdateMatrix(Shader& shader) {
		shader.Use();

		shader.SetUniformMat4("CamProjection", Camera::GetProjectionMatrix());
		shader.SetUniformMat4("CamView", Camera::GetViewMatrix());
		//shader.SetUniformVec3("CamPosition", Position);
	}

	void Camera::SetViewportSize(glm::vec2 size) {
		// This is to prevent crashing when minimizing the window
		if (size.x == 0 || size.y == 0) {
			return;
		}

		m_viewportSize = size;
	}

	glm::mat4 Camera::GetProjectionMatrix() const {
		return glm::perspective(glm::radians(FOV), (float)(m_viewportSize.x / m_viewportSize.y), NearPlane, FarPlane);
	}

	glm::mat4 Camera::GetViewMatrix() const {
		return glm::lookAt(Position, Position + Orientation, glm::vec3(0.0f, 1.0f, 0.0f));
	}

	glm::vec2 Camera::GetViewportSize() const {
		return m_viewportSize;
	}
}