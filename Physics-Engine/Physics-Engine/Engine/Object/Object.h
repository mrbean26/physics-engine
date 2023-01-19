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
#include <Engine/Components/AudioListener.h>
#include <Engine/Components/AudioSource.h>
#include <Engine/Components/Button.h>

/*
----ADDING A NEW COMPONENT---
Include here
Add to AllComponents struct below
Add to CreateComponent method in object.cpp
Include Engine.h first in componentName.cpp
*/

struct AllComponents {
	Camera camera;
	Collider collider;
	DirectionalLight directionalLight;
	PointLight pointLight;
	Transform transform;
	ViewModel viewModel;
	AudioListener audioListener;
	AudioSource audioSource;
	Button button;
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

	// Template functions
	template<typename T> bool HasComponent() {
		string templateName = typeid(T).name();
		string componentName = templateName.substr(6, templateName.size() - 6);

		if (components.find(componentName) != components.end()) {
			return true;
		}
		return false;
	}
	template<typename T> void AddComponent() {
		string templateName = typeid(T).name();
		string componentName = templateName.substr(6, templateName.size() - 6);
		
		Component * newComponent = CreateComponent(&allComponents, componentName);
		newComponent->componentObjectParentName = name;
		newComponent->parentObject = this;
		components.insert(make_pair(componentName, newComponent));
	}
	template<typename T> void RemoveComponent() {
		string templateName = typeid(T).name();
		string componentName = templateName.substr(6, templateName.size() - 6);

		if (components.find(componentName) != components.end()) {
			components.erase(componentName);
			return;
		}
		// create exception
		cout << "Unfound component:" << componentName.data() << endl;
		throw ("Component with name " + componentName + " not found.").data();
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
