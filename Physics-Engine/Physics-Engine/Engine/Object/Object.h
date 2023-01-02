#pragma once

#include <map>
#include <memory>
#include <string>
using namespace std;

#include <Engine/Object/Component.h>

#include <Engine/Background/FileLoading.h>

#include <Engine/Components/Camera.h>
#include <Engine/Components/Collider.h>
#include <Engine/Components/DirectionalLight.h>
#include <Engine/Components/PointLight.h>
#include <Engine/Components/Transform.h>
#include <Engine/Components/ViewModel.h>

/*
----ADDING A NEW COMPONENT---
Include here
Add to AllComponents struct below
Add to CreateComponent method in object.cpp
Try not to include engine.h in the component header, and if needed in cpp file, include first
*/

struct AllComponents {
	Camera camera;
	Collider collider;
	DirectionalLight directionalLight;
	PointLight pointLight;
	Transform transform;
	ViewModel viewModel;
};

Component* CreateComponent(AllComponents* objectComponents, string componentName);

#include <iostream>
using namespace std;

class Object {
public:
	const char* name;

	Object();
	void ObjectMainloop();
	
	AllComponents allComponents;
	map<string, Component*> components;
	bool HasComponent(string name);

	//void AddComponent(string name);
	template<typename T> void AddComponent() {
		string templateName = typeid(T).name();
		string componentName = templateName.substr(6, templateName.size() - 6);
		
		Component * newComponent = CreateComponent(&allComponents, componentName);
		newComponent->componentObjectParentName = name;
		newComponent->parentObject = this;
		components.insert(make_pair(componentName, newComponent));
	}

	template<typename T> T GetComponent() {
		string templateName = typeid(T).name();
		string componentName = templateName.substr(6, templateName.find("*") - 6 - 1);

		if (components.find(componentName) != components.end()) {
			return (T) (components[componentName]);
		}
		// create exception
		cout << "Unfound component:" << componentName.data() << endl;
		throw ("Component with name " + componentName + " not found.").data();
	}
};
