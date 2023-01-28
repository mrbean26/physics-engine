#include <Engine/Engine.h>

int main(void) {
    Scene newScene = Scene("New Scene");
	
	Object* cameraObject = newScene.CreateSceneObject("Adam");
	
	cameraObject->AddComponent<Camera>();
	newScene.mainCamera = cameraObject->GetComponent<Camera*>();

	cameraObject->GetComponent<Transform*>()->position = vec3(0.0f, 0.0f, 0.0f);
	cameraObject->GetComponent<Transform*>()->scale = vec3(0.9f, 0.1f, 1.0f);
	
	cameraObject->AddComponent<Text>();
	cameraObject->GetComponent<Text*>()->Colour = vec3(1.0f, 1.0f, 0.0f);

	

    PhysicsEngine gameEngine("Game Engine", 1280, 720, false, newScene);
    return 0;
}