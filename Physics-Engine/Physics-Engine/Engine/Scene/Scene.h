#pragma once

using namespace std;
#include <map>

#include <Engine/Object/Object.h>
#include <Engine/Components/Camera.h>

class Scene {
public:
	Scene();
	void SceneMainloop();

	map<const char*, Object> SceneObjects;
	Object * CreateSceneObject(const char * name);
	Object * GetSceneObjectByID(const char * name);

	Camera* mainCamera;
};