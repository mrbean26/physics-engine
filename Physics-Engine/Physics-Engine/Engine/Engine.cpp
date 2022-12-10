#include <Engine/Engine.h>

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
	
	// Run Mainloop
	EngineMainloop();
}

void PhysicsEngine::EngineMainloop() {
	glfwMakeContextCurrent(mainWindow);

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