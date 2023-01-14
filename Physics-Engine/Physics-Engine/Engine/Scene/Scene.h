#pragma once

using namespace std;
#include <map>

#include <Engine/Object/Object.h>

class Scene {
public:
	Scene(string newName);
	string name;
	void SceneMainloop();

	map<const char*, Object> SceneObjects;
	Object * CreateSceneObject(const char * name);
	Object * GetSceneObjectByID(const char * name);

	Camera* mainCamera;
	AudioListener* mainAudioListener;
};