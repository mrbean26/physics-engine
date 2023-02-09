#include <Engine/Engine.h>
#include <Engine/Background/Shaders.h>

int main(void) {
    Scene newScene = Scene("New Scene");
	    
    Object* ParentObject = newScene.CreateSceneObject("Parent");
    ParentObject->AddComponent<Camera>();
    ParentObject->GetComponent<Transform*>()->position = vec3(0.0f, 0.0f, 25.0f);
    ParentObject->AddComponent<PointLight>();
    ParentObject->GetComponent<PointLight*>()->intensity = 20.0f;

    newScene.mainCamera = ParentObject->GetComponent<Camera*>();

    Object* ButtonObject = newScene.CreateSceneObject("Viewm");
    ButtonObject->AddComponent<ViewModel>();
    ButtonObject->GetComponent<ViewModel*>()->LoadOBJ("Assets/Cube.obj");
    ButtonObject->GetComponent<ViewModel*>()->ObjectColour = vec3(0.9f, 0.2f, 0.2f);
    ButtonObject->GetComponent<Transform*>()->mass = 80000000000.0f;
    ButtonObject->GetComponent<Transform*>()->position = vec3(0.0f, 0.0f, 0.0f);
    ButtonObject->AddComponent<Collider>();
    
    Object* childLight = newScene.CreateSceneObject("childlight");
    childLight->GetComponent<Transform*>()->position = vec3(-5.0f, 0.0f, 0.0f);
    childLight->GetComponent<Transform*>()->mass = 10.0f;
    childLight->AddComponent<ViewModel>();
    childLight->GetComponent<ViewModel*>()->LoadOBJ("Assets/Cube.obj");
    childLight->AddComponent<Collider>();

    PhysicsEngine gameEngine("Game Engine", 1280, 720, false, newScene);
    return 0;
}