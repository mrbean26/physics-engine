#pragma once

#include <Engine/Object/Component.h>

#include <OpenGL/GLEW/glew.h>
#include <OpenGL/GLFW/glfw3.h>

class Button : public Component {
public:
	void Mainloop();
	void Initialise();

	mat4 GetUIMatrix();
	void Render();

	// GL Attributes
	inline static GLuint ButtonVAO = -1;
	inline static GLuint ButtonVBO = -1;
	inline static GLuint ButtonShader = -1;

	GLuint ButtonTextureID;
	string texturePath;
	
	vec3 ButtonColour = vec3(1.0f);

	// Shader and Vertices
	void InitialiseShader();
	void InitialiseVertices();
};