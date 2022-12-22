#pragma once

#include <vector>
using namespace std;

#include <GLM/glm.hpp>
using namespace glm;

#include <Engine/Object/Component.h>

#define COLLIDER_CUBE 0 // Shapes are only effective when mesh is from -1 to 1 when unscaled
#define COLLIDER_SPHERE 1
#define COLLIDER_MESH 2

class Collider : public Component {
public:
	int colliderType = COLLIDER_MESH;

	void InitialiseShapeVertices();
	void InitialiseMeshVertices();

	void Initialise();
	void Mainloop();

	// Point in Triangle Detection
	float sign(vec2 pointOne, vec2 pointTwo, vec2 pointThree);
	bool pointInTriangle(vec2 point, vec2 pointOne, vec2 pointTwo, vec2 pointThree);

	// Detection
	vector<vec3> triangleFaceVertices;

	vector<vec3> modelMatrixVertices;
	void updateMatrixVertices();
	int lastMatrixVertexFrameUpdate = 0;

	static inline int lastFrameClear = 0;
	vector<const char*> alreadyCollidedObjects;

	bool checkCollider2D(vec3 point, int pointOneShift, int pointTwoShift);
	bool pointInColliderXY(vec3 point);
	bool pointInColliderXZ(vec3 point);
	bool pointInColliderYZ(vec3 point);

	bool pointInCollider(vec3 point);

	// Correction
	void updateCollisions();
};