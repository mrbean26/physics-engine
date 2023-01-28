#include <Engine/Engine.h>

int main(void) {
    Scene newScene = Scene("New Scene");
	
	Object* cameraObject = newScene.CreateSceneObject("Adam");
	cameraObject->AddComponent<Scrollbar>();
	cameraObject->GetComponent<Transform*>()->scale = vec3(1.5f, 0.025f, 1.0f);
	cameraObject->GetComponent<Scrollbar*>()->ScrollbarSliderScale = vec3(0.025f, 1.5f, 1.0f);

    PhysicsEngine gameEngine("Game Engine", 1280, 720, false, newScene);
    return 0;
}