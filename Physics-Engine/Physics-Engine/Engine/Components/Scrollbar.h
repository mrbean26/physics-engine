#pragma once

#include <Engine/Object/Component.h>

class Scrollbar : public Component {
public:
	void Mainloop();
	void Initialise();

	void CreateSubObjects();
	mat4 GetUIMatrix();
	void UpdateObjectTransforms();

	Object* ScrollbarSlider;
	float ScrollbarValue = 0.5f;
	vec3 ScrollbarSliderScale = vec3(0.5f);

	string ScrollbarBackgroundTexturePath = "Assets/Defaults/ScrollbarBackground.png";
	string ScrollbarSliderTexturePath = "Assets/Defaults/ScrollbarSlider.png";
};