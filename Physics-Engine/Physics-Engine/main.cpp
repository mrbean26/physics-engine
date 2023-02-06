#include <Engine/Engine.h>

int main(void) {
    Scene newScene = Scene("New Scene");
	
	Object* cameraObject = newScene.CreateSceneObject("Adam");
	cameraObject->AddComponent<Camera>();
	cameraObject->AddComponent<PointLight>();
	cameraObject->GetComponent<PointLight*>()->intensity = 10.0f;
	cameraObject->GetComponent<Transform*>()->position = vec3(0.0f, 0.0f, 15.0f);

	newScene.mainCamera = cameraObject->GetComponent<Camera*>();

	Object* NewModel = newScene.CreateSceneObject("Earth");
	NewModel->AddComponent<ViewModel>();
	NewModel->GetComponent<ViewModel*>()->LoadOBJ("Assets/Cube.obj");
	NewModel->GetComponent<ViewModel*>()->ObjectColour = vec3(0.2f, 0.9f, 0.2f);
	NewModel->GetComponent<Transform*>()->mass = 1000000000000.0f;

	Object* OrbitingModel = newScene.CreateSceneObject("Moon");
	OrbitingModel->AddComponent<ViewModel>();
	OrbitingModel->GetComponent<ViewModel*>()->LoadOBJ("Assets/sphere.obj");
	OrbitingModel->GetComponent<ViewModel*>()->ObjectColour = vec3(0.9f, 0.2f, 0.2f);
	OrbitingModel->GetComponent<Transform*>()->position = vec3(0.0f, 4.0f, 0.0f);
	OrbitingModel->GetComponent<Transform*>()->scale = vec3(0.2f);
	OrbitingModel->GetComponent<Transform*>()->mass = 1.0f;
	OrbitingModel->GetComponent<Transform*>()->velocity = vec3(4.08f, 0.0f, 0.0f);

    PhysicsEngine gameEngine("Game Engine", 1280, 720, false, newScene);
    return 0;
}