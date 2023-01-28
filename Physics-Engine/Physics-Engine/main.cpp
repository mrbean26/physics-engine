#include <Engine/Engine.h>

void xx() {
	cout << "white" << endl;
}
void xx2() {
	cout << "red" << endl;
}

int main(void) {
    Scene newScene = Scene("New Scene");
	
	Object* cameraObject = newScene.CreateSceneObject("Adam");
	
	cameraObject->AddComponent<Camera>();
	newScene.mainCamera = cameraObject->GetComponent<Camera*>();

	cameraObject->GetComponent<Transform*>()->position = vec3(0.0f, 0.0f, 0.0f);
	cameraObject->GetComponent<Transform*>()->scale = vec3(0.9f, 0.1f, 1.0f);
	
	cameraObject->AddComponent<Button>();
	cameraObject->GetComponent<Button*>()->ButtonOnClickFunction = &xx;


	Object* newobj = newScene.CreateSceneObject("Toby");
	newobj->AddComponent<Button>();
	newobj->GetComponent<Button*>()->ButtonColour = vec3(1.0f, 0.0f, 0.0f);
	newobj->GetComponent<Transform*>()->position = vec3(0.5f, 0.0f, -0.9f);
	newobj->GetComponent<Transform*>()->scale = vec3(0.9f, 0.1f, 1.0f);
	newobj->GetComponent<Button*>()->ButtonOnClickFunction = &xx2;
	

    PhysicsEngine gameEngine("Game Engine", 1280, 720, false, newScene);
    return 0;
}