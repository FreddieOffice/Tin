#include "Tin/TinPCH.hpp"
#include "Tin/Renderer/DataStructures/Transform.hpp"

namespace Tin {
	Transform::Transform() : Position(glm::vec3(0.0f)), Rotation(glm::vec3(0.0f)), Scale(glm::vec3(1.0f)) {}

	Transform::Transform(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale) : Position(position), Rotation(rotation), Scale(scale) {}

	glm::mat4 Transform::GetModelMatrix() const {
		glm::mat4 transform = glm::mat4(1.0f);

		// Translation
		transform = glm::translate(transform, Position);

		// Rotate
		transform = glm::rotate(transform, glm::radians(Rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
		transform = glm::rotate(transform, glm::radians(Rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
		transform = glm::rotate(transform, glm::radians(Rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

		// Scale
		transform = glm::scale(transform, Scale);

		return transform;
	}
}
