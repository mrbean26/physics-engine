#include <Engine/Components/Transform.h>
#include <Engine/Engine.h>
#include <Engine/Object/Object.h>

#include <algorithm>
using namespace std;

#include <GLM/gtc/matrix_transform.hpp>

#define GRAVITATIONAL_CONSTANT 0.00000606743
#define ELECTRIC_CONSTANT 8998000000

Transform::Transform() {
	position = vec3(0.0f);
	scale = vec3(1.0f);
	rotation = vec3(0.0f);

	velocity = vec3(0.0f);
}
void Transform::Mainloop() {
	force = vec3(0.0f);

	// update gravitational and electric force
	if (mass != 0.0f || charge != 0.0f) {
		Scene* currentScene = &PhysicsEngine::loadedScenes[PhysicsEngine::currentScene];
		map<const char*, Object>* sceneObjects = &currentScene->SceneObjects;

		for (map<const char*, Object>::iterator it = sceneObjects->begin(); it != sceneObjects->end(); it++) {
			if (it->first == componentObjectParentName) {
				continue;
			}

			Transform* secondTransform = it->second.GetComponent<Transform*>("Transform");
			float distanceApart = distance(position, secondTransform->position);

			if (distanceApart <= 0.01f) {
				distanceApart = INFINITY;
			}

			float gravitationalForceMagnitude = -GRAVITATIONAL_CONSTANT * ((mass * secondTransform->mass) / powf(distanceApart, 2.0f)); // universal law of gravitation
			float electricalForceMagnitude = ELECTRIC_CONSTANT * ((charge * secondTransform->charge) / powf(distanceApart, 2.0f)); // couloumbs law
			
			// get unit vector between two positions
			vec3 unitDirectionVector = normalize(position - secondTransform->position);
			
			force = force + unitDirectionVector * (gravitationalForceMagnitude + electricalForceMagnitude);
		}
	}

	// update velocity
	vec3 acceleration = vec3(0.0f);
	if (mass != 0.0f) {
		acceleration = force / mass;
	}

	velocity = velocity + acceleration * PhysicsEngine::deltaTime;
	
	// update position
	position = position + velocity * PhysicsEngine::deltaTime;
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