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
	glfwSetMouseButtonCallback(mainWindow, UpdateMouseEvent);
	displayWidth = width;
	displayHeight = height;

	if (glewInit() != GLEW_OK) {
		return;
	}

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);

	// Initialise OpenAL
	mainAudioDevice = alcOpenDevice(NULL);
	audioContext = alcCreateContext(mainAudioDevice, NULL);
	alcMakeContextCurrent(audioContext);

	ALenum errorCheck = alGetError();
	if (errorCheck != AL_NO_ERROR) {
		cout << "OpenAL Error." << endl;
		return;
	}
	
	// Run Mainloop
	EngineMainloop();
}

void PhysicsEngine::EngineMainloop() {
	while (!glfwWindowShouldClose(mainWindow)) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glfwGetCursorPos(mainWindow, &MousePosition.x, &MousePosition.y);
		
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
	
	if (Text::FreetypeInitialised) {
		FT_Done_FreeType(Text::FreetypeLibrary);
	}
}

void PhysicsEngine::UpdateMouseEvent(GLFWwindow* window, int button, int action, int mods) {
	if (button == GLFW_MOUSE_BUTTON_LEFT) {
		if (action == GLFW_PRESS) {
			MouseLeftDown = true;
		}
		if (action == GLFW_RELEASE) {
			MouseLeftDown = false;
		}
	}
	if (button == GLFW_MOUSE_BUTTON_RIGHT) {
		if (action == GLFW_PRESS) {
			MouseRightDown = true;
		}
		if (action == GLFW_RELEASE) {
			MouseRightDown = false;
		}
	}
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