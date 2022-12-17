#pragma once

#include <Engine/Object/Component.h>

#include <GLM/glm.hpp>
using namespace glm;

class Camera : public Component {
public:
	float nearViewProjection = 0.1f;
	float farViewProjection = 500.0f;

	mat4 viewMatrix();
};