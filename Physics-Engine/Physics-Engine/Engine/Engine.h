#pragma once

#include <vector>
using namespace std;

#include <OpenGL/GLEW/glew.h>
#include <OpenGL/GLFW/glfw3.h>

#include <AL/al.h>
#include <AL/alc.h>

#include <Engine/Scene/Scene.h>

#include <GLM/glm.hpp>

#define SHADOW_RESOLUTION 1024

class PhysicsEngine {
public:
	PhysicsEngine(const char* title, int width, int height, bool fullscreen, Scene initialScene);

	void EngineMainloop();
	void StopEngine();

	// Display
	inline static float displayWidth;
	inline static float displayHeight;

	GLFWwindow* mainWindow;

	inline static float deltaTime;
	inline static float runtime;
	inline static int frameNumber = 0;

	// Input
	static void UpdateMouseEvent(GLFWwindow* window, int button, int action, int mods);

	inline static dvec2 MousePosition;
	inline static vec2 DisplayMousePosition;

	inline static bool MouseRightDown;
	inline static bool MouseLeftDown;

	// Audio
	ALCdevice* mainAudioDevice;
	ALCcontext* audioContext;

	// Scenes
	void AddScene(Scene newScene);
	void LoadScene(string name);

	inline static vector<Scene> loadedScenes;
	inline static int currentScene = 0;

	static glm::mat4 viewMatrix();
};