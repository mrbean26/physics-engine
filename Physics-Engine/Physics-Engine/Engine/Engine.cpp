#include <Engine/Engine.h>

#include <Engine/Components/ViewModel.h>
#include <Engine/Components/Camera.h>
#include <Engine/Background/Shaders.h>

#include <GLM/gtc/matrix_transform.hpp>

#include <Engine/Components/Transform.h>
#include <Engine/Components/Collider.h>
#include <Engine/Components/PointLight.h>
#include <Engine/Components/DirectionalLight.h>

PhysicsEngine::PhysicsEngine(const char* title, int width, int height, bool fullscreen, Scene initialScene) {
	// Initialise An Empty Scene
	loadedScenes.push_back(initialScene);
	
	// Initialise Graphics
	if (!glfwInit()) { return; }
	
	if (fullscreen) {
		GLFWmonitor* primaryMonitor;
		primaryMonitor = glfwGetPrimaryMonitor();
		mainWindow = glfwCreateWindow(width, height, title, primaryMonitor, NULL);
	}
	else {
		mainWindow = glfwCreateWindow(width, height, title, NULL, NULL);
	}

	if (!mainWindow) {
		glfwTerminate();
		return;
	}
	
	glfwMakeContextCurrent(mainWindow);
	displayWidth = width;
	displayHeight = height;

	if (glewInit() != GLEW_OK) {
		return;
	}

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
	
	// Run Mainloop
	EngineMainloop();
}

void PhysicsEngine::EngineMainloop() {
	while (!glfwWindowShouldClose(mainWindow)) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		loadedScenes[currentScene].SceneMainloop();

		deltaTime = glfwGetTime() - runtime;
		runtime = glfwGetTime();

		glfwSwapBuffers(mainWindow);
		glfwPollEvents();

		frameNumber = frameNumber + 1;
	}

	StopEngine();
}
void PhysicsEngine::StopEngine() {
	glfwTerminate();
}

void PhysicsEngine::AddScene(Scene newScene) {
	loadedScenes.push_back(newScene);
}
void PhysicsEngine::LoadScene(string name) {
	int sceneCount = loadedScenes.size();

	for (int i = 0; i < sceneCount; i++) {
		if (loadedScenes[i].name == name) {
			currentScene = i;
			return;
		}
	}

	// Scene not found
	throw ("Scene with name: " + name + " not found.").data();
}

mat4 PhysicsEngine::viewMatrix() {
	return loadedScenes[currentScene].mainCamera->viewMatrix();
}