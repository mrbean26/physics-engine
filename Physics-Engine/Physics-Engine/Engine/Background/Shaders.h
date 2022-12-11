#pragma once

#include <GLM/glm.hpp>
using namespace glm;

#include <OpenGL/GLEW/glew.h>
#include <OpenGL/GLFW/glfw3.h>

#include <vector>
using namespace std;

int CreateShader(const char* filePath, GLenum shaderType);
int CreateProgram(vector<int> shaders);

void SetShaderInt(int shader, const char* intName, int usedInt);
void SetShaderMat4(int shader, const char* matrixName, mat4 usedMatrix);
void SetShaderVec3(int shader, const char* vectorName, vec3 usedVector);