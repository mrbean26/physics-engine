#include <Engine/Engine.h>

#include <Engine/Components/ViewModel.h>
#include <Engine/Background/Shaders.h>

#include <GLM/gtc/matrix_transform.hpp>

#include <Engine/Components/Transform.h>

PhysicsEngine::PhysicsEngine(const char* title, int width, int height, bool fullscreen) {
	// Initialise An Empty Scene
	loadedScenes.push_back(Scene());
	
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

	glEnable(GL_TEXTURE_2D);
	

	Object* newObject = loadedScenes[0].CreateSceneObject("Adam");

	Transform newTransform = Transform();
	newObject->AddComponent(&newTransform, "Transform");
	

	ViewModel newViewModel = ViewModel();
	newViewModel.ObjectColour = vec3(1.0f, 1.0f, 1.0f);
	newViewModel.verticesType = VERTICES_POINTS_TEXTURE;
	
	newViewModel.ObjectTextureID = LoadTexture("Assets/image.png");

	newViewModel.vertices = { 0.0f, 0.0f, -0.5f, 0.0f, 0.0f,
							1.0f, 0.0f, -0.5f, 1.0f, 0.0f,
							0.0f, 1.0f, -0.5f, 0.0f, 1.0f };

	newObject->AddComponent(&newViewModel, "ViewModel");

	
	// Run Mainloop
	EngineMainloop();
}

void PhysicsEngine::EngineMainloop() {
	while (!glfwWindowShouldClose(mainWindow)) {
		glClear(GL_COLOR_BUFFER_BIT);
		
		loadedScenes[currentScene].SceneMainloop();

		glfwSwapBuffers(mainWindow);
		glfwPollEvents();
	}

	StopEngine();
}
void PhysicsEngine::StopEngine() {
	glfwTerminate();
}

mat4 PhysicsEngine::viewMatrix() {
	return mat4(1.0f);
}
mat4 PhysicsEngine::projectionMatrix() {
	return perspective(radians(45.0f), displayWidth / displayHeight, 0.1f, 500.0f);
}