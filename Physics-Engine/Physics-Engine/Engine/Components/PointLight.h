#pragma once

#include <Engine/Object/Component.h>

class PointLight : public Component {
public:
	float intensity = 1.0f;

	float attenuationConstant = 1.0f;
	float attenuationLinear = 0.09f;
	float attenuationQuadratic = 0.032f;

	float ambient = 0.05f;
	float diffuse = 0.8f;
	float specular = 1.0f;

	static void ApplyPointLights(int shaderValue);
};