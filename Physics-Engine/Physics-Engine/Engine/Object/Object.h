#pragma once

#include <map>
#include <memory>
#include <string>
using namespace std;

#include <Engine/Object/Component.h>

#include <iostream>
using namespace std;

#include <Engine/Components/Camera.h>
#include <Engine/Components/Collider.h>
#include <Engine/Components/DirectionalLight.h>
#include <Engine/Components/PointLight.h>
#include <Engine/Components/Transform.h>
#include <Engine/Components/ViewModel.h>

struct AllComponents {
	Camera camera;
	Collider collider;
	DirectionalLight directionalLight;
	PointLight pointLight;
	Transform transform;
	ViewModel viewModel;
};

class Object {
public:
	const char* name;

	Object();
	void ObjectMainloop();
	
	AllComponents allComponents;
	map<const char*, Component*> components;
	bool HasComponent(const char* name);

	void AddComponent(const char * name);
	template<typename T> T GetComponent(const char* name) {
		if (components.find(name) != components.end()) {
			return (T) (components[name]);
		}

		// create exception
		string componentName(name);
		cout << componentName << endl;
		throw ("Component with name " + componentName + " not found.").data();
	}
};
