#include <Engine/Engine.h>

int main(void) {
    Scene newScene = Scene("New Scene");
	
	Object* cameraObject = newScene.CreateSceneObject("Adam");
	cameraObject->AddComponent<Camera>();
	cameraObject->AddComponent<PointLight>();
	cameraObject->GetComponent<PointLight*>()->intensity = 50.0f;

	newScene.mainCamera = cameraObject->GetComponent<Camera*>();

	Object* viewObject = newScene.CreateSceneObject("Toby");
	viewObject->AddComponent<ViewModel>();
	viewObject->GetComponent<ViewModel*>()->verticesType = VERTICES_POINTS_ONLY;
	viewObject->GetComponent<ViewModel*>()->LoadOBJ("assets/cube.obj");
	viewObject->GetComponent<ViewModel*>()->ObjectColour = vec3(1.0f);
	viewObject->GetComponent<Transform*>()->position = vec3(0.0f, 0.0f, -25.0f);

    PhysicsEngine gameEngine("Game Engine", 1280, 720, false, newScene);
    return 0;
}