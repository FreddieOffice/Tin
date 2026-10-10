#ifndef TIN_RENDERER_DATASTRUCTURES_TRANSFORM_HPP
#define TIN_RENDERER_DATASTRUCTURES_TRANSFORM_HPP

#include "glm/glm.hpp"

namespace Tin {
	struct Transform {
		glm::vec3 Position = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec3 Rotation = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec3 Scale = glm::vec3(1.0f, 1.0f, 1.0f);

		// Default constructor
		// Position and rotation are set to 0, scale is set to 1
		Transform() = default;

		Transform(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale);

		// Returns the model matrix of the transform
		glm::mat4 GetModelMatrix() const;
	};
}

#endif
