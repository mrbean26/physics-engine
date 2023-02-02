#pragma once

#include <Engine/Object/Component.h>

#include <OpenGL/GLEW/glew.h>
#include <OpenGL/GLFW/glfw3.h>

class Button : public Component {
public:
	void Mainloop();
	void Initialise();

	void Render();

	// Button OnClicks
	int LastFrameClickUpdate = -1;
	bool ClickedLastFrame = false;
	
	bool ButtonPressedDown = false;
	bool ButtonClicked = false;

	void UpdateClicks();
	void (*ButtonOnClickFunction)() = nullptr;

	// Colour Changes
	bool ColourEffects = true;
	float HoverColourMultiplier = 0.95f;
	float ClickColourMultiplier = 0.85f;

	float CurrentColourMultiplier = 1.0f;

	// GL Attributes
	inline static GLuint ButtonVAO = -1;
	inline static GLuint ButtonVBO = -1;
	inline static GLuint ButtonShader = -1;

	GLuint ButtonTextureID;
	string texturePath = "Assets/Defaults/Texture.png";
	
	vec3 ButtonColour = vec3(1.0f);

	// Shader and Vertices
	void InitialiseShader();
	void InitialiseVertices();
};