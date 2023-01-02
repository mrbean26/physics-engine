#include <Engine/Engine.h>

#include <Engine/Components/ViewModel.h>
#include <Engine/Components/Camera.h>
#include <Engine/Background/Shaders.h>

#include <GLM/gtc/matrix_transform.hpp>

#include <Engine/Components/Transform.h>
#include <Engine/Components/Collider.h>
#include <Engine/Components/PointLight.h>
#include <Engine/Components/DirectionalLight.h>

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

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);

	
	Object* cameraObject = loadedScenes[0].CreateSceneObject("Adam");
	cameraObject->AddComponent<Transform>();
	cameraObject->AddComponent<Camera>();
	cameraObject->AddComponent<PointLight>();
	cameraObject->GetComponent<PointLight*>()->intensity = 50.0f;
	
	loadedScenes[0].mainCamera = cameraObject->GetComponent<Camera*>();

	Object* viewObject = loadedScenes[0].CreateSceneObject("Toby");
	viewObject->AddComponent<Transform>();
	viewObject->AddComponent<ViewModel>();
	viewObject->GetComponent<ViewModel*>()->verticesType = VERTICES_POINTS_ONLY;
	viewObject->GetComponent<ViewModel*>()->LoadOBJ("assets/cube.obj");
	viewObject->GetComponent<ViewModel*>()->ObjectColour = vec3(1.0f);
	viewObject->GetComponent<Transform*>()->position = vec3(0.0f, 0.0f, -25.0f);
	
	
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

mat4 PhysicsEngine::viewMatrix() {
	return loadedScenes[currentScene].mainCamera->viewMatrix();
}