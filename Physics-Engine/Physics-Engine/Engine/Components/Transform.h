#pragma once

#include <Engine/Object/Component.h>

#include <GLM/glm.hpp>
using namespace glm;

class Transform : public Component {
public:
	Transform();

	vec3 position;
	vec3 scale;
	vec3 rotation;

	mat4 getModelMatrix();
};