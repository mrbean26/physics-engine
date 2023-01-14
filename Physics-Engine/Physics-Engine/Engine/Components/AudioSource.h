#pragma once

#include <Engine/Object/Component.h>

class AudioSource : public Component {
public:
	void Mainloop();

	float attenuationConstant = 1.0f;
	float attenuationLinear = 0.09f;
	float attenuationQuadratic = 0.032f;
};