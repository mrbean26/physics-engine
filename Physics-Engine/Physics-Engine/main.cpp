#include <Engine/Engine.h>

int main(void) {
    Scene newScene = Scene("New Scene");
	
	Object* cameraObject = newScene.CreateSceneObject("Adam");
	cameraObject->AddComponent<Camera>();
	cameraObject->AddComponent<PointLight>();
	cameraObject->GetComponent<PointLight*>()->intensity = 200.0f;
	cameraObject->GetComponent<Transform*>()->position = vec3(0.0f, 0.0f, 15.0f);

	newScene.mainCamera = cameraObject->GetComponent<Camera*>();

	Object* NewModel = newScene.CreateSceneObject("Viewmodel");

	ViewModel ParticleObject = ViewModel();
	ParticleObject.LoadOBJ("Assets/cube.obj");
	ParticleObject.ObjectColour = vec3(0.0f, 1.0f, 1.0f);
	Transform ParticleTransform = Transform();
	ParticleTransform.scale = vec3(0.2f);

	NewModel->AddComponent<ParticleSystem>();
	NewModel->GetComponent<ParticleSystem*>()->ParticleViewmodel = ParticleObject;
	NewModel->GetComponent<ParticleSystem*>()->ParticleTransform = ParticleTransform;

    PhysicsEngine gameEngine("Game Engine", 1280, 720, false, newScene);
    return 0;
}