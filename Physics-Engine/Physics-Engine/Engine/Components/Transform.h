#pragma once

#include <Engine/Object/Component.h>

#include <GLM/glm.hpp>
using namespace glm;

class Transform : public Component {
public:
	Transform();
	void Mainloop();

	vec3 position;
	vec3 scale;
	vec3 rotation;

	mat4 getModelMatrix();

	// Forces
	void UpdateGravityElectricalForce(Transform* secondTransform);

	// Physics Elements
	vec3 velocity;
	vec3 force;
	
	float mass = 0.0f;
	float charge = 0.0f;
};