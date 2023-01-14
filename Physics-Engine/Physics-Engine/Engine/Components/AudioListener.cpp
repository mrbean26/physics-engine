#include <Engine/Engine.h>
#include <Engine/Components/AudioListener.h>

#include <Engine/Background/Shaders.h>

#include <GLM/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void AudioListener::Mainloop() {
	UpdateSourceVolumes();
}

void AudioListener::UpdateSourceVolumes() {
	Scene* currentScene = &PhysicsEngine::loadedScenes[PhysicsEngine::currentScene];
	map<const char*, Object>* sceneObjects = &currentScene->SceneObjects;

	// Prequisites
	mat4 listenerModelMatrix = parentObject->GetComponent<Transform*>()->getModelMatrix();
	mat4 inverseListenerModelMatrix = inverse(listenerModelMatrix);
	vec3 listenerPosition = parentObject->GetComponent<Transform*>()->position;

	vec3 forward = listenerModelMatrix * vec4(0.0f, 0.0f, -1.0f, 1.0f);
	vec3 up = listenerModelMatrix * vec4(0.0f, 1.0f, 0.0f, 1.0f);
	vec3 right = listenerModelMatrix * vec4(1.0f, 0.0f, 0.0f, 1.0f);

	// Prequisite Directions
	vec3 lookForwardDirection = forward - listenerPosition;
	vec3 lookUpDirection = up - listenerPosition;
	vec3 lookRightDirection = right - listenerPosition;

	vec3 normalizedUpDirection = normalize(lookUpDirection);

	mat3 vectorMatrix{
		lookForwardDirection.x, lookForwardDirection.y, lookForwardDirection.z,
		lookRightDirection.x, lookRightDirection.y, lookRightDirection.z,
		lookUpDirection.x, lookUpDirection.y, lookUpDirection.z
	};

	// Iterate
	for (map<const char*, Object>::iterator it = sceneObjects->begin(); it != sceneObjects->end(); it++) {
		if (it->second.HasComponent<AudioSource>()) {
			AudioSource* currentAudioSource = it->second.GetComponent<AudioSource*>();
			Transform* currentTransform = it->second.GetComponent<Transform*>();

			vec3 sourceDirection = currentTransform->position - listenerPosition;
			
			// Solve system of equations for axis scalars
			mat3 inverseMatrix = inverse(vectorMatrix);
			vec3 vectorScalars = inverseMatrix * sourceDirection;
			
			// Substitute scalar values into equation for two-axis pointing vector
			vec3 newSourcePosition = vec3(
				listenerPosition.x + lookForwardDirection.x * vectorScalars.x + lookRightDirection.x * vectorScalars.y,
				listenerPosition.y + lookForwardDirection.y * vectorScalars.x + lookRightDirection.y * vectorScalars.y,
				listenerPosition.z + lookForwardDirection.z * vectorScalars.x + lookRightDirection.z * vectorScalars.y
			);

			// Convert direction back into 2d x-z plane
			newSourcePosition = inverseListenerModelMatrix * vec4(newSourcePosition, 1.0f);
			newSourcePosition = normalize(newSourcePosition);
			
			// Calculate Forward Angle
			vec2 direction = vec2(newSourcePosition.x, newSourcePosition.z);
			vec2 newForward = vec2(0.0f, -1.0f);

			float forwardAngle = acosf(dot(direction, newForward));
			if (direction.x < 0.0f) {
				forwardAngle = 2 * glm::pi<float>() - forwardAngle; // Convert acute into obtuse angle
			}

			// Calculate Up Angle
			vec3 normalizedSourceDirection = normalize(sourceDirection);
			float upAngle = acosf(dot(normalizedSourceDirection, normalizedUpDirection));

			if (upAngle > 90.0f) {
				upAngle = 90.0f - upAngle;
			}

			// Calculate Left and Right Intensity Values
			float upMultiplier = sin(upAngle);
			
			float rightIntensity = upMultiplier * (0.5f + 0.5f * sin(forwardAngle));
			float leftIntensity = upMultiplier * (0.5f - 0.5f * sin(forwardAngle));

			if (upMultiplier == 0.0f) {
				rightIntensity = 0.0f;
				leftIntensity = 0.0f;
			}

			cout << "LEFT:   " << leftIntensity << "        " << "RIGHT:   " << rightIntensity << endl;
		}
	}
}