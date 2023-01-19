#include <Engine/Engine.h>

int main(void) {
    Scene newScene = Scene("New Scene");
	
	Object* cameraObject = newScene.CreateSceneObject("Adam");
	cameraObject->AddComponent<Camera>();
	cameraObject->GetComponent<Transform*>()->position = vec3(0.5f, 0.0f, 0.0f);
	cameraObject->GetComponent<Transform*>()->scale = vec3(0.5f);
	cameraObject->AddComponent<Button>();
	cameraObject->GetComponent<Button*>()->texturePath= "Assets/a.png";

	newScene.mainCamera = cameraObject->GetComponent<Camera*>();

    PhysicsEngine gameEngine("Game Engine", 1280, 720, false, newScene);
    return 0;
}