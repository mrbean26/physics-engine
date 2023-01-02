#include <Engine/Engine.h>

#include <Engine/Components/Collider.h>
#include <Engine/Components/Transform.h>
#include <Engine/Components/ViewModel.h>

int decimalPlacesRound = 2;
float roundFloat(float input) {
	int roundedInteger = (int)(input * 10 * decimalPlacesRound + 0.5f);
	return float(roundedInteger) / (10 * decimalPlacesRound);
}

void Collider::InitialiseShapeVertices() {
	if (colliderType == COLLIDER_CUBE) {
		triangleFaceVertices = { vec3(1, -1, 1), vec3(-1, -1, -1), vec3(1, -1, -1), vec3(-1, 1, -1), vec3(1, 1, 1), vec3(1, 1, -1), vec3(1, 1, -1), vec3(1, -1, 1), vec3(1, -1, -1), vec3(1, 1, 1), vec3(-1, -1, 1), vec3(1, -1, 1), vec3(-1, -1, 1), vec3(-1, 1, -1), vec3(-1, -1, -1), vec3(1, -1, -1), vec3(-1, 1, -1), vec3(1, 1, -1), vec3(1, -1, 1), vec3(-1, -1, 1), vec3(-1, -1, -1), vec3(-1, 1, -1), vec3(-1, 1, 1), vec3(1, 1, 1), vec3(1, 1, -1), vec3(1, 1, 1), vec3(1, -1, 1), vec3(1, 1, 1), vec3(-1, 1, 1), vec3(-1, -1, 1), vec3(-1, -1, 1), vec3(-1, 1, 1), vec3(-1, 1, -1), vec3(1, -1, -1), vec3(-1, -1, -1), vec3(-1, 1, -1) };
	}
	if (colliderType == COLLIDER_SPHERE) {
		triangleFaceVertices = { vec3(0, -1, 0), vec3(0.7236, -0.447215, 0.52572), vec3(-0.276385, -0.447215, 0.85064), vec3(0.7236, -0.447215, 0.52572), vec3(0, -1, 0), vec3(0.7236, -0.447215, -0.52572), vec3(0, -1, 0), vec3(-0.276385, -0.447215, 0.85064), vec3(-0.894425, -0.447215, 0), vec3(0, -1, 0), vec3(-0.894425, -0.447215, 0), vec3(-0.276385, -0.447215, -0.85064), vec3(0, -1, 0), vec3(-0.276385, -0.447215, -0.85064), vec3(0.7236, -0.447215, -0.52572), vec3(0.7236, -0.447215, 0.52572), vec3(0.7236, -0.447215, -0.52572), vec3(0.894425, 0.447215, 0), vec3(-0.276385, -0.447215, 0.85064), vec3(0.7236, -0.447215, 0.52572), vec3(0.276385, 0.447215, 0.85064), vec3(-0.894425, -0.447215, 0), vec3(-0.276385, -0.447215, 0.85064), vec3(-0.7236, 0.447215, 0.52572), vec3(-0.276385, -0.447215, -0.85064), vec3(-0.894425, -0.447215, 0), vec3(-0.7236, 0.447215, -0.52572), vec3(0.7236, -0.447215, -0.52572), vec3(-0.276385, -0.447215, -0.85064), vec3(0.276385, 0.447215, -0.85064), vec3(0.7236, -0.447215, 0.52572), vec3(0.894425, 0.447215, 0), vec3(0.276385, 0.447215, 0.85064), vec3(-0.276385, -0.447215, 0.85064), vec3(0.276385, 0.447215, 0.85064), vec3(-0.7236, 0.447215, 0.52572), vec3(-0.894425, -0.447215, 0), vec3(-0.7236, 0.447215, 0.52572), vec3(-0.7236, 0.447215, -0.52572), vec3(-0.276385, -0.447215, -0.85064), vec3(-0.7236, 0.447215, -0.52572), vec3(0.276385, 0.447215, -0.85064), vec3(0.7236, -0.447215, -0.52572), vec3(0.276385, 0.447215, -0.85064), vec3(0.894425, 0.447215, 0), vec3(0.276385, 0.447215, 0.85064), vec3(0.894425, 0.447215, 0), vec3(0, 1, 0), vec3(-0.7236, 0.447215, 0.52572), vec3(0.276385, 0.447215, 0.85064), vec3(0, 1, 0), vec3(-0.7236, 0.447215, -0.52572), vec3(-0.7236, 0.447215, 0.52572), vec3(0, 1, 0), vec3(0.276385, 0.447215, -0.85064), vec3(-0.7236, 0.447215, -0.52572), vec3(0, 1, 0), vec3(0.894425, 0.447215, 0), vec3(0.276385, 0.447215, -0.85064), vec3(0, 1, 0) };
	}
}
void Collider::InitialiseMeshVertices() {
	ViewModel* objectViewModel = parentObject->GetComponent<ViewModel*>();

	if (objectViewModel->verticesType == VERTICES_POINTS_ONLY) {
		int vertexCount = objectViewModel->vertices.size();

		for (int i = 0; i < vertexCount; i += 6) {
			vec3 newPoint = vec3(0.0f);

			for (int j = 0; j < 3; j++) {
				newPoint[j] = roundFloat(objectViewModel->vertices[i + j]);
			}

			triangleFaceVertices.push_back(newPoint);
		}
	}
	if (objectViewModel->verticesType == VERTICES_POINTS_TEXTURE) {
		int vertexCount = objectViewModel->vertices.size();

		for (int i = 0; i < vertexCount; i += 8) {
			vec3 newPoint = vec3(0.0f);

			for (int j = 0; j < 3; j++) {
				newPoint[j] = roundFloat(objectViewModel->vertices[i + j]);
			}

			triangleFaceVertices.push_back(newPoint);
		}
	}
}

void Collider::Initialise() {
	if (initialised) {
		return;
	}

	if (colliderType == COLLIDER_MESH) {
		InitialiseMeshVertices();
	}
	else {
		InitialiseShapeVertices();
	}

	initialised = true;
}
void Collider::Mainloop() {
	Initialise();

	if (PhysicsEngine::frameNumber > lastFrameClear) {
		alreadyCollidedObjects.clear();
		lastFrameClear = PhysicsEngine::frameNumber;
	}

	updateCollisions();
}

// Point in Triangle Detection
float Collider::sign(vec2 pointOne, vec2 pointTwo, vec2 pointThree) {
	return (pointOne.x - pointThree.x) * (pointTwo.y - pointThree.y) - (pointTwo.x - pointThree.x) * (pointOne.y - pointThree.y);
}
bool Collider::pointInTriangle(vec2 point, vec2 pointOne, vec2 pointTwo, vec2 pointThree) {
	float dOne = sign(point, pointOne, pointTwo);
	float dTwo = sign(point, pointTwo, pointThree);
	float dThree = sign(point, pointThree, pointOne);

	bool hasNegative = (dOne < 0) || (dTwo < 0) || (dThree < 0);
	bool hasPositive = (dOne > 0) || (dTwo > 0) || (dThree > 0);

	return !(hasNegative && hasPositive);
}

// Multiply by matrices only once for efficiency
void Collider::updateMatrixVertices() {
	if (PhysicsEngine::frameNumber == lastMatrixVertexFrameUpdate) {
		return;
	}

	modelMatrixVertices.clear();
	int count = triangleFaceVertices.size();
	
	mat4 modelMatrix = parentObject->GetComponent<Transform*>()->getModelMatrix();
	for (int i = 0; i < count; i++) {
		vec3 modelPoint = modelMatrix * vec4(triangleFaceVertices[i], 1.0f);
		modelMatrixVertices.push_back(modelPoint);
	}

	lastMatrixVertexFrameUpdate = PhysicsEngine::frameNumber;
}

// Detection
bool Collider::checkCollider2D(vec3 point, int pointOneShift, int pointTwoShift) {
	int vertexCount = triangleFaceVertices.size();

	vec2 checkPoint = vec2(point[pointOneShift], point[pointTwoShift]);
	for (int i = 0; i < vertexCount; i += 3) {
		vec3 pointOne = modelMatrixVertices[i];
		vec3 pointTwo = modelMatrixVertices[i + 1];
		vec3 pointThree = modelMatrixVertices[i + 2];

		vec2 pointOneDimension = vec2(pointOne[pointOneShift], pointOne[pointTwoShift]);
		vec2 pointTwoDimension = vec2(pointTwo[pointOneShift], pointTwo[pointTwoShift]);
		vec2 pointThreeDimension = vec2(pointThree[pointOneShift], pointThree[pointTwoShift]);
		
		// check points are not the same (system breaks)
		if (pointOneDimension == pointTwoDimension || pointOneDimension == pointThreeDimension || pointTwoDimension == pointThreeDimension) {
			continue;
		}

		if (pointInTriangle(checkPoint, pointOneDimension, pointTwoDimension, pointThreeDimension)) {
			return true;
		}
	}

	return false;
}
bool Collider::pointInColliderXY(vec3 point) {
	return checkCollider2D(point, 0, 1);
}
bool Collider::pointInColliderXZ(vec3 point) {
	return checkCollider2D(point, 0, 2);
}
bool Collider::pointInColliderYZ(vec3 point) {
	return checkCollider2D(point, 1, 2);
}

bool Collider::pointInCollider(vec3 point) {
	if (pointInColliderXY(point)) {
		if (pointInColliderXZ(point)) {
			if (pointInColliderYZ(point)) {
				return true;
			}
		}
	}

	return false;
}

// Correction
void Collider::updateCollisions() {
	map<const char*, Object>* allSceneObjects = &PhysicsEngine::loadedScenes[PhysicsEngine::currentScene].SceneObjects;
	updateMatrixVertices();
	Transform* thisTransform = parentObject->GetComponent<Transform*>();

	for (map<const char*, Object>::iterator it = allSceneObjects->begin(); it != allSceneObjects->end(); it++) {
		if (it->first == parentObject->name) {
			continue;
		}
		
		// check if collided with object already
		if (find(alreadyCollidedObjects.begin(), alreadyCollidedObjects.end(), it->first) != alreadyCollidedObjects.end()) {
			continue;
		}

		// check for collision
		if (it->second.HasComponent("Collider")) {
			Collider* secondCollider = it->second.GetComponent<Collider*>();
			secondCollider->updateMatrixVertices();

			Transform* secondTransform = it->second.GetComponent<Transform*>();
			vector<vec3> secondColliderPoints = secondCollider->modelMatrixVertices;
			
			int count = secondColliderPoints.size();
			for (int i = 0; i < count; i++) {
				if (pointInCollider(secondColliderPoints[i])) {
					// Assume perfectly elastic collision due to no heat energy concept
					
					// First Object
					float scalarOne = (thisTransform->mass - secondTransform->mass) / (thisTransform->mass + secondTransform->mass);
					float scalarTwo = (2.0f * secondTransform->mass) / (thisTransform->mass + secondTransform->mass);

					vec3 newVelocityOne = scalarOne * thisTransform->velocity + scalarTwo * secondTransform->velocity;

					// Second Object
					float scalarThree = (2.0f * thisTransform->mass) / (thisTransform->mass + secondTransform->mass);
					float scalarFour = (secondTransform->mass - thisTransform->mass) / (thisTransform->mass + secondTransform->mass);
					
					vec3 newVelocityTwo = scalarThree * thisTransform->velocity + scalarFour * secondTransform->velocity;

					// Assign
					thisTransform->velocity = newVelocityOne;
					secondTransform->velocity = newVelocityTwo;
					
					secondCollider->alreadyCollidedObjects.push_back(parentObject->name);
					
					break;
				}
			}
		}
	}
}