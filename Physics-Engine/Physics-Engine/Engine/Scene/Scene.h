#pragma once

using namespace std;
#include <map>

#include <Engine/Object/Object.h>

class Scene {
public:
	Scene(string newName);
	string name;
	void SceneMainloop();

	map<string, Object> SceneObjects;
	Object * CreateSceneObject(string name);
	Object * GetSceneObjectByID(string name);
	void DeleteObjectByID(string name);

	Camera* mainCamera;
	AudioListener* mainAudioListener;
};