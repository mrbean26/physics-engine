#pragma once

#include <map>
#include <memory>
#include <string>
using namespace std;

#include <Engine/Object/Component.h>

#include <iostream>
using namespace std;

class Object {
public:
	const char* name;

	Object();
	void ObjectMainloop();

	map<const char*, Component*> components;
	void AddComponent(Component* newComponent, const char * name);
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