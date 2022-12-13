#pragma once

using namespace std;
#include <map>

#include <Engine/Object/Object.h>

class Scene {
public:
	Scene();
	void SceneMainloop();

	map<const char*, Object> SceneObjects;
	Object * CreateSceneObject(const char * name);
	Object * GetSceneObjectByID(const char * name);
};