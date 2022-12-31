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
	
	Object* newObject = loadedScenes[0].CreateSceneObject("Adam");
	Transform newTranform = Transform();
	newTranform.position = vec3(0.0f, 0.0f, -25.0f);
	newTranform.mass = 0.1f;
	newObject->AddComponent(&newTranform, "Transform");
	ViewModel newViewModel = ViewModel();
	newViewModel.ObjectColour = vec3(1.0f, 1.0f, 1.0f);
	newViewModel.verticesType = VERTICES_POINTS_ONLY;
	newViewModel.LoadOBJ("Assets/cube.obj");
	newObject->AddComponent(&newViewModel, "ViewModel");
	Collider c = Collider();
	newObject->AddComponent(&c, "Collider");
	PointLight newLight = PointLight();
	newObject->AddComponent(&newLight, "PointLight");

	Object* newObject1 = loadedScenes[0].CreateSceneObject("Adam1");
	Transform newTranform1 = Transform();
	newTranform1.velocity = vec3(5.0f, 0.0f, 0.0f);
	newTranform1.position = vec3(-20.0f, 0.0f, -25.0f);
	newTranform1.rotation = vec3(0.0f, 0.0f, 0.0f);
	newTranform1.mass = 1.0f;
	newObject1->AddComponent(&newTranform1, "Transform");
	ViewModel newViewModel1 = ViewModel();
	newViewModel1.ObjectColour = vec3(1.0f, 1.0f, 1.0f);
	newViewModel1.verticesType = VERTICES_POINTS_ONLY;
	newViewModel1.LoadOBJ("Assets/sphere.obj");
	newObject1->AddComponent(&newViewModel1, "ViewModel");
	Collider c1 = Collider();
	newObject1->AddComponent(&c1, "Collider");
	
	Object* secondObject = loadedScenes[0].CreateSceneObject("Toby");
	Transform secondTransform = Transform();
	secondTransform.position = vec3(0.0f, -0.0f, 0.0f);
	secondObject->AddComponent(&secondTransform, "Transform");
	Camera newCamera = Camera();
	loadedScenes[currentScene].mainCamera = &newCamera;
	secondObject->AddComponent(&newCamera, "Camera");
	
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