#pragma once

#include <Engine/Object/Component.h>

class DirectionalLight : public Component {
public:
	float intensity = 1.0f;

	float attenuationConstant = 1.0f;
	float attenuationLinear = 0.09f;
	float attenuationQuadratic = 0.032f;
};