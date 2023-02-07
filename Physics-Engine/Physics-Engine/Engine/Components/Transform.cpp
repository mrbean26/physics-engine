#include <Engine/Engine.h>

#include <Engine/Components/Transform.h>
#include <Engine/Object/Object.h>

#include <algorithm>
using namespace std;

#include <GLM/gtc/matrix_transform.hpp>

#include <Engine/Components/ViewModel.h>

#define GRAVITATIONAL_CONSTANT 6.67e-11f
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
		vector<Object*> AllSceneObjects = PhysicsEngine::GetAllSceneObjects();
		int SceneObjectCount = int(AllSceneObjects.size());

		for (int i = 0; i < SceneObjectCount; i++) {
			Object* CurrentObject = AllSceneObjects[i];

			if (CurrentObject->name == ParentObjectName) {
				continue;
			}

			Transform* secondTransform = CurrentObject->GetComponent<Transform*>();
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

vec3 Transform::GetFullWorldPosition() {
	return getModelMatrix() * vec4(0.0f, 0.0f, 0.0f, 1.0f);
}
vec3 Transform::GetFullWorldScale() {
	vec3 ResultantScale = this->scale;

	if (ParentTransform == nullptr) {
		return ResultantScale;
	}

	return ParentTransform->GetFullWorldScale() * ResultantScale;
}
vec3 Transform::GetFullWorldRotation() {
	vec3 ResultantRotation = this->rotation;

	if (ParentTransform == nullptr) {
		return ResultantRotation;
	}

	return ParentTransform->GetFullWorldRotation() + ResultantRotation;
}

void Transform::UpdateGravityElectricalForce(Transform* secondTransform) {
	float distanceApart = distance(position, secondTransform->position);

	if (distanceApart <= 0.25f) {
		return;
	}

	float gravitationalForceMagnitude = -GRAVITATIONAL_CONSTANT * ((mass * secondTransform->mass) / powf(distanceApart, 2.0f)); // universal law of gravitation
	float electricalForceMagnitude = ELECTRIC_CONSTANT * ((charge * secondTransform->charge) / powf(distanceApart, 2.0f)); // couloumbs law

	// update force
	vec3 unitDirectionVector = normalize(position - secondTransform->position);
	force = force + unitDirectionVector * (gravitationalForceMagnitude + electricalForceMagnitude);
}