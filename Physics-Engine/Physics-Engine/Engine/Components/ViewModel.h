#pragma once

#include <Engine/Object/Component.h>

#include <OpenGL/GLEW/glew.h>
#include <OpenGL/GLFW/glfw3.h>

#include <GLM/glm.hpp>
using namespace glm;

#include <vector>
using namespace std;

#define VERTICES_POINTS_ONLY 0 
#define VERTICES_POINTS_COLOURS 1
#define VERTICES_POINTS_TEXTURE 2
#define VERTICES_POINTS_COLOUR_TEXTURE 3

class ViewModel : public Component {
public:
	void Mainloop();
	void Initialise();

	GLuint ObjectVAO;
	GLuint ObjectVBO;
	GLuint ObjectDrawSize;

	// Shaders
	inline static GLuint ViewModelPointsShader = -1;

	// Colour
	inline static GLuint ViewModelPointsColourShader = -1;
	vec3 ObjectColour;

	// Texture
	inline static GLuint ViewModelPointsTextureShader = -1;
	GLuint ObjectTextureID;

	inline static GLuint ViewModelPointsColourTextureShader = -1;
	void initialiseShader();

	int verticesType = VERTICES_POINTS_ONLY;
	vector<float> vertices;

	void InitialiseVertices();

	void Render();
};