#pragma once

using namespace std;
#include <map>

#include <Engine/Object/Object.h>

class Scene {
public:
	Scene();
	void SceneMainloop();

	map<int, Object> SceneObjects;
};