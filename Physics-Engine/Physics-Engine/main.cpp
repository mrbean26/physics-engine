#include <Engine/Engine.h>

int main(void) {
    Scene newScene = Scene("New Scene");
	
	Object* cameraObject = newScene.CreateSceneObject("Adam");
	cameraObject->AddComponent<Camera>();
	cameraObject->AddComponent<PointLight>();
	cameraObject->GetComponent<PointLight*>()->intensity = 200.0f;
	cameraObject->GetComponent<Transform*>()->position = vec3(0.0f, 0.0f, 15.0f);

	newScene.mainCamera = cameraObject->GetComponent<Camera*>();

	Object* NewModel = newScene.CreateSceneObject("Dropdown");

	NewModel->AddComponent<Dropdown>();
	NewModel->GetComponent<Transform*>()->scale = vec3(0.8f, 0.08f, 1.0f);

    PhysicsEngine gameEngine("Game Engine", 1280, 720, false, newScene);
    return 0;
}