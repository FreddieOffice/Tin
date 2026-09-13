#ifndef TIN_RENDERER_DATASTRUCTURES_TRANSFORM_HPP
#define TIN_RENDERER_DATASTRUCTURES_TRANSFORM_HPP

#include "glm/glm.hpp"

namespace Tin {
	struct Transform {
		glm::vec3 Position;
		glm::vec3 Rotation;
		glm::vec3 Scale;

		// Default constructor
		// Position and rotation are set to 0, scale is set to 1
		Transform();

		Transform(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale);

		// Returns the model matrix of the transform
		glm::mat4 GetModelMatrix() const;
	};
}

#endif