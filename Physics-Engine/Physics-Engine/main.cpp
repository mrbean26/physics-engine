#include <Engine/Engine.h>

int main(void) {
    Scene newScene = Scene("New Scene");
	
    Object* ParentObject = newScene.CreateSceneObject("Parent");
    ParentObject->AddComponent<Camera>();
    ParentObject->AddComponent<PointLight>();
    ParentObject->GetComponent<PointLight*>()->intensity = 200.0f;

    newScene.mainCamera = ParentObject->GetComponent<Camera*>();

    Object* ButtonObject = newScene.CreateSceneObject("Viewm");
    ButtonObject->AddComponent<ViewModel>();
    ButtonObject->GetComponent<ViewModel*>()->LoadOBJ("Assets/sphere.obj");
    ButtonObject->GetComponent<ViewModel*>()->ObjectColour = vec3(0.9f, 0.2f, 0.2f);
    ButtonObject->GetComponent<Transform*>()->mass = 10000000000.0f;
    ButtonObject->GetComponent<Transform*>()->position = vec3(0.0f, 0.0f, -25.0f);

    Object* childLight = newScene.CreateSceneObject("childlight");
    childLight->GetComponent<Transform*>()->position = vec3(-5.0f, 0.0f, -25.0f);
    childLight->GetComponent<Transform*>()->mass = 10.0f;
    childLight->AddComponent<ViewModel>();
    childLight->GetComponent<ViewModel*>()->LoadOBJ("Assets/sphere.obj");
    //childLight->AddComponent<PointLight>();
    //childLight->GetComponent<PointLight*>()->intensity = 50.0f;

    PhysicsEngine gameEngine("Game Engine", 1280, 720, false, newScene);
    return 0;
}