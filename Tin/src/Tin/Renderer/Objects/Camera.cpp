#include "Tin/TinPCH.hpp"
#include "Tin/Renderer/Objects/Camera.hpp"

namespace Tin {
	Camera::Camera(glm::ivec2 viewportSize, glm::vec3 position, glm::vec3 orientation, float fieldOfView, float nearPlane, float farPlane) : m_viewportSize(viewportSize), position(position), orientation(orientation), fieldOfView(fieldOfView), nearPlane(nearPlane), farPlane(farPlane) {}

	void Camera::SetViewportSize(glm::ivec2 size) {
		// This is to prevent crashing when minimizing the window
		if (size.x == 0 || size.y == 0) { return; }

		m_viewportSize = size;
	}

	glm::mat4 Camera::GetProjectionMatrix() const {
		return glm::perspective(glm::radians(fieldOfView), static_cast<float>(m_viewportSize.x) / m_viewportSize.y, nearPlane, farPlane);
	}

	glm::mat4 Camera::GetViewMatrix() const {
		return glm::lookAt(position, position + orientation, glm::vec3(0.0f, 1.0f, 0.0f));
	}

	glm::ivec2 Camera::GetViewportSize() const {
		return m_viewportSize;
	}
}
