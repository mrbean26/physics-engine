#pragma once

#include <Engine/Object/Component.h>

#include <OpenGL/GLEW/glew.h>
#include <OpenGL/GLFW/glfw3.h>

#include <GLM/glm.hpp>
using namespace glm;

#include <vector>
using namespace std;

#define VERTICES_POINTS_ONLY 0 
#define VERTICES_POINTS_TEXTURE 2

class ViewModel : public Component {
public:
	void Mainloop();
	void Initialise();

	GLuint ObjectVAO;
	GLuint ObjectVBO;
	GLuint ObjectDrawSize;
	vec3 ObjectColour = vec3(1.0f);

	// OBJ Loading - MAKE SURE FACES ARE TRIANGLES (CTRL+T IN BLENDER)
	void LoadOBJ(const char* filePath);
	void LoadOBJFace(vector<string> faceData, vector<vec3> fileVertices, vector<vec2> textureVertices, vector<vec3> vertexNormals);
	
	ivec3 LoadOBJFacePoint(string point);
	static void AddVec3ToVector(vector<float>* UsedVector, vec3 UsedPoint);
	static void AddVec2ToVector(vector<float>* UsedVector, vec2 UsedPoint);

	// Shaders
	inline static GLuint ViewModelPointsShader = -1;

	// Texture
	inline static GLuint ViewModelPointsTextureShader = -1;
	string texturePath;
	GLuint ObjectTextureID;

	void initialiseShader();

	int verticesType = VERTICES_POINTS_ONLY;
	vector<float> vertices;

	void InitialiseVertices();

	void Render();
};