#include <Engine/Components/Transform.h>

#include <GLM/gtc/matrix_transform.hpp>

Transform::Transform() {
	position = vec3(0.0f);
	scale = vec3(1.0f);
	rotation = vec3(0.0f);
}

mat4 Transform::getModelMatrix() {
	mat4 newMatrix = mat4(1.0f);

	newMatrix = translate(newMatrix, position);

	newMatrix = glm::scale(newMatrix, this->scale);
	
	newMatrix = rotate(newMatrix, radians(rotation.x), vec3(1.0f, 0.0f, 0.0f));
	newMatrix = rotate(newMatrix, radians(rotation.y), vec3(0.0f, 1.0f, 0.0f));
	newMatrix = rotate(newMatrix, radians(rotation.z), vec3(0.0f, 0.0f, 1.0f));

	return newMatrix;
}