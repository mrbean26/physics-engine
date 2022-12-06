#pragma once

#include <vector>
using namespace std;

#include <OpenGL/GLEW/glew.h>
#include <OpenGL/GLFW/glfw3.h>

#include <Engine/Scene/Scene.h>

class PhysicsEngine {
public:
	PhysicsEngine(const char* title, int width, int height, bool fullscreen);

	void EngineMainloop();
	void StopEngine();

	GLFWwindow* mainWindow;
	vector<Scene> loadedScenes;
	int currentScene = -1;
};