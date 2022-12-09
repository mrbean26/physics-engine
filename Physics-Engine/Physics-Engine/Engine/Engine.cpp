#include <Engine/Engine.h>

PhysicsEngine::PhysicsEngine(const char* title, int width, int height, bool fullscreen) {
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

	
	EngineMainloop();
}

void PhysicsEngine::EngineMainloop() {
	glfwMakeContextCurrent(mainWindow);

	while (!glfwWindowShouldClose(mainWindow)) {
		glClear(GL_COLOR_BUFFER_BIT);
		
		if (currentScene > -1) {
			loadedScenes[currentScene].SceneMainloop();
			
		}

		glfwSwapBuffers(mainWindow);
		glfwPollEvents();
	}

	StopEngine();
}
void PhysicsEngine::StopEngine() {
	glfwTerminate();
}