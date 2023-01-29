#include <Engine/Engine.h>

int main(void) {
    Scene newScene = Scene("New Scene");
	
	Object* cameraObject = newScene.CreateSceneObject("Adam");
	cameraObject->AddComponent<Dropdown>();

	cameraObject->GetComponent<Transform*>()->scale = vec3(0.2f, 0.05f, 1.0f);

    PhysicsEngine gameEngine("Game Engine", 1280, 720, false, newScene);
    return 0;
}