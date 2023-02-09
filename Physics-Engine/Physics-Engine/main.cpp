#include <Engine/Engine.h>
#include <Engine/Background/Shaders.h>

int main(void) {
    Scene newScene = Scene("New Scene");
	    
    Object* ParentObject = newScene.CreateSceneObject("Parent");
    ParentObject->AddComponent<Camera>();
    ParentObject->GetComponent<Transform*>()->position = vec3(0.0f, 0.0f, 95.0f);
    ParentObject->AddComponent<PointLight>();
    ParentObject->GetComponent<PointLight*>()->intensity = 10000.0f;

    newScene.mainCamera = ParentObject->GetComponent<Camera*>();

    Object* SunObject = newScene.CreateSceneObject("Sun");
    SunObject->AddComponent<ViewModel>();
    SunObject->GetComponent<ViewModel*>()->LoadOBJ("Assets/sphere.obj");
    SunObject->GetComponent<ViewModel*>()->ObjectColour = vec3(1.0f, 0.96f, 0.04f);
    SunObject->GetComponent<Transform*>()->mass = 5e14;    
    SunObject->GetComponent<Transform*>()->scale = vec3(2.5f);
    SunObject->GetComponent<Transform*>()->position = vec3(0.0f, 0.0f, 0.0f);

    Object* SunParticleObject = newScene.CreateSceneObject("SunParticles");
    SunParticleObject->AddComponent<ParticleSystem>();
    ViewModel ParticleModel = ViewModel();
    ParticleModel.ObjectColour = vec3(1.0f, 0.96f, 0.04f);
    ParticleModel.LoadOBJ("Assets/Cube.obj");
    SunParticleObject->GetComponent<ParticleSystem*>()->ParticleViewmodel = ParticleModel;
    SunParticleObject->GetComponent<ParticleSystem*>()->ParticleVelocity = 15.0f;
    SunParticleObject->GetComponent<Transform*>()->scale = vec3(0.5f);

    Object* EarthObject = newScene.CreateSceneObject("Earth");
    EarthObject->AddComponent<ViewModel>();
    EarthObject->GetComponent<ViewModel*>()->LoadOBJ("Assets/sphere.obj");
    EarthObject->GetComponent<ViewModel*>()->ObjectColour = vec3(0.25f, 0.96f, 0.04f);
    EarthObject->GetComponent<Transform*>()->mass = 0.001f;
    EarthObject->GetComponent<Transform*>()->scale = vec3(1.2f);
    EarthObject->GetComponent<Transform*>()->position = vec3(-35.0f, 0.0f, 0.0f);
    EarthObject->GetComponent<Transform*>()->velocity = vec3(0.0f, 30.877f, 0.0f);
    
    Object* MoonObject = newScene.CreateSceneObject("Mercury");
    MoonObject->AddComponent<ViewModel>();
    MoonObject->GetComponent<ViewModel*>()->LoadOBJ("Assets/sphere.obj");
    MoonObject->GetComponent<ViewModel*>()->ObjectColour = vec3(0.9f);
    MoonObject->GetComponent<Transform*>()->mass = 0.001f;
    MoonObject->GetComponent<Transform*>()->velocity = vec3(0.0f, 36.53f, 0.0f);
    MoonObject->GetComponent<Transform*>()->scale = vec3(0.5f);
    MoonObject->GetComponent<Transform*>()->position = vec3(-18.0f, 0.0f, 0.0f);

    Object* TextBox = newScene.CreateSceneObject("TextBox");
    TextBox->AddComponent<Text>();
    TextBox->AddComponent<CustomComponent>();
    TextBox->GetComponent<Transform*>()->scale = vec3(0.1f, 0.05f, 1.0f);
    TextBox->GetComponent<Transform*>()->position = vec3(-0.5f, 0.9f, 0.0f);

    PhysicsEngine gameEngine("Game Engine", 1600, 900, false, newScene);
    return 0;
}