#include <Engine/Engine.h>

#include <Engine/Components/Transform.h>
#include <Engine/Object/Object.h>

#include <algorithm>
using namespace std;

#include <GLM/gtc/matrix_transform.hpp>

#include <Engine/Components/ViewModel.h>

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
		map<string, Object>* sceneObjects = &currentScene->SceneObjects;

		for (map<string, Object>::iterator it = sceneObjects->begin(); it != sceneObjects->end(); it++) {
			if (it->first == ParentObjectName) {
				continue;
			}

			Transform* secondTransform = it->second.GetComponent<Transform*>();
			UpdateGravityElectricalForce(secondTransform);
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
	
	if (ParentTransform == nullptr) {
		return newMatrix;
	}
	
	return ParentTransform->getModelMatrix() * newMatrix;
}
mat4 Transform::getUIModelMatrix() {
	Transform* objectTransform = ParentObject()->GetComponent<Transform*>();

	mat4 newModelMatrix = mat4(1.0f);
	newModelMatrix = translate(newModelMatrix, objectTransform->position);

	newModelMatrix = glm::scale(newModelMatrix, vec3(PhysicsEngine::displayHeight / PhysicsEngine::displayWidth, 1.0f, 1.0f));

	vec3 rotation = objectTransform->rotation;
	newModelMatrix = rotate(newModelMatrix, radians(rotation.x), vec3(1.0f, 0.0f, 0.0f));
	newModelMatrix = rotate(newModelMatrix, radians(rotation.y), vec3(0.0f, 1.0f, 0.0f));
	newModelMatrix = rotate(newModelMatrix, radians(rotation.z), vec3(0.0f, 0.0f, 1.0f));

	newModelMatrix = glm::scale(newModelMatrix, vec3(1.0f) / vec3(PhysicsEngine::displayHeight / PhysicsEngine::displayWidth, 1.0f, 1.0f));

	newModelMatrix = glm::scale(newModelMatrix, objectTransform->scale);

	if (ParentTransform == nullptr) {
		newModelMatrix = glm::scale(newModelMatrix, vec3(PhysicsEngine::displayHeight / PhysicsEngine::displayWidth, 1.0f, 1.0f));
		return newModelMatrix;
	}

	return ParentTransform->getUIModelMatrix() * newModelMatrix;
}

void Transform::UpdateGravityElectricalForce(Transform* secondTransform) {
	float distanceApart = distance(position, secondTransform->position);

	if (distanceApart <= 0.01f) {
		distanceApart = INFINITY;
	}

	float gravitationalForceMagnitude = -GRAVITATIONAL_CONSTANT * ((mass * secondTransform->mass) / powf(distanceApart, 2.0f)); // universal law of gravitation
	float electricalForceMagnitude = ELECTRIC_CONSTANT * ((charge * secondTransform->charge) / powf(distanceApart, 2.0f)); // couloumbs law

	// update force
	vec3 unitDirectionVector = normalize(position - secondTransform->position);
	force = force + unitDirectionVector * (gravitationalForceMagnitude + electricalForceMagnitude);
}