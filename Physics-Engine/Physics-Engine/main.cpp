#include <Engine/Engine.h>

int main(void) {
    Scene newScene = Scene("New Scene");
	
	Object* cameraObject = newScene.CreateSceneObject("Adam");
	cameraObject->AddComponent<Camera>();
	cameraObject->AddComponent<PointLight>();
	cameraObject->GetComponent<PointLight*>()->intensity = 50.0f;
	cameraObject->GetComponent<Transform*>()->position = vec3(0.0f, 8.0f, 0.0f);
	cameraObject->GetComponent<Transform*>()->rotation = vec3(0.0f, -20.0f, 0.0f);
	
	newScene.mainCamera = cameraObject->GetComponent<Camera*>();

	Object* listenerObject = newScene.CreateSceneObject("AAA");
	listenerObject->AddComponent<AudioListener>();
	listenerObject->AddComponent<ViewModel>();
	listenerObject->GetComponent<ViewModel*>()->verticesType = VERTICES_POINTS_ONLY;
	listenerObject->GetComponent<ViewModel*>()->LoadOBJ("assets/cube.obj");
	listenerObject->GetComponent<ViewModel*>()->ObjectColour = vec3(1.0f);
	listenerObject->GetComponent<Transform*>()->position = vec3(0.0f, 0.0f, -25.0f);
	listenerObject->GetComponent<ViewModel*>()->ObjectColour = vec3(1.0f, 0.0f, 0.0f);
	listenerObject->GetComponent<Transform*>()->rotation = vec3(0.0f, 0.0f, 0.0f);
	listenerObject->GetComponent<Transform*>()->velocity = vec3(0.0f, 0.0f, 0.0f);

	newScene.mainAudioListener = listenerObject->GetComponent<AudioListener*>();

	Object* viewObject = newScene.CreateSceneObject("Toby");
	viewObject->AddComponent<AudioSource>();
	viewObject->GetComponent<AudioSource*>()->audioFileMP3Filename = "Assets/tone.mp3";
	viewObject->AddComponent<ViewModel>();
	viewObject->GetComponent<ViewModel*>()->verticesType = VERTICES_POINTS_ONLY;
	viewObject->GetComponent<ViewModel*>()->LoadOBJ("assets/cube.obj");
	viewObject->GetComponent<ViewModel*>()->ObjectColour = vec3(1.0f);
	viewObject->GetComponent<Transform*>()->position = vec3(0.0f, 0.0f, -30.0f);

    PhysicsEngine gameEngine("Game Engine", 1280, 720, false, newScene);
    return 0;
}