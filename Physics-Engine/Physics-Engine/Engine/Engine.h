#pragma once

#include <vector>
using namespace std;

#include <OpenGL/GLEW/glew.h>
#include <OpenGL/GLFW/glfw3.h>

#include <Engine/Scene/Scene.h>

#include <GLM/glm.hpp>

class PhysicsEngine {
public:
	PhysicsEngine(const char* title, int width, int height, bool fullscreen);

	void EngineMainloop();
	void StopEngine();

	inline static float displayWidth;
	inline static float displayHeight;

	GLFWwindow* mainWindow;

	inline static float deltaTime;
	inline static float runtime;
	inline static int frameNumber = 0;

	inline static vector<Scene> loadedScenes;
	inline static int currentScene = 0;

	static glm::mat4 viewMatrix();
};