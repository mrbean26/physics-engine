#include <Engine/Engine.h>

#include <Engine/Components/Camera.h>
#include <Engine/Components/Transform.h>

#include <GLM/gtc/matrix_transform.hpp>

mat4 Camera::viewMatrix() {
	// Projection
	mat4 projectionMatrix = mat4(1.0f);
	projectionMatrix = perspective(radians(45.0f), PhysicsEngine::displayWidth / PhysicsEngine::displayHeight, nearViewProjection, farViewProjection);
	
	// View
	Transform* cameraTransform = parentObject->GetComponent<Transform*>("Transform");

	vec3 cameraPosition = cameraTransform->position;
	vec3 cameraRotation = cameraTransform->rotation;
	
	// View Matrix
	mat4 viewMatrix = mat4(1.0f);
	viewMatrix = rotate(viewMatrix, -radians(cameraRotation.x), vec3(0.0f, 1.0f, 0.0f));
	viewMatrix = rotate(viewMatrix, -radians(cameraRotation.y), vec3(1.0f, 0.0f, 0.0f));
	viewMatrix = rotate(viewMatrix, radians(cameraRotation.z), vec3(0.0f, 0.0f, 1.0f));
	
	viewMatrix = translate(viewMatrix, -cameraPosition);
	
	return projectionMatrix * viewMatrix;
}