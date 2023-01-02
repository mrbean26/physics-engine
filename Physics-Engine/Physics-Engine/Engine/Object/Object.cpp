#include <Engine/Object/Object.h>

#include <iostream>
using namespace std;

Component* CreateComponent(AllComponents* objectComponents, string componentName) {
	Component* newComponent = nullptr;

	if (componentName == "Camera") {
		objectComponents->camera = Camera();
		newComponent = &objectComponents->camera;
	}
	if (componentName == "Collider") {
		objectComponents->collider = Collider();
		newComponent = &objectComponents->collider;
	}
	if (componentName == "DirectionalLight") {
		objectComponents->directionalLight = DirectionalLight();
		newComponent = &objectComponents->directionalLight;
	}
	if (componentName == "PointLight") {
		objectComponents->pointLight = PointLight();
		newComponent = &objectComponents->pointLight;
	}
	if (componentName == "Transform") {
		objectComponents->transform = Transform();
		newComponent = &objectComponents->transform;
	}
	if (componentName == "ViewModel") {
		objectComponents->viewModel = ViewModel();
		newComponent = &objectComponents->viewModel;
	}

	return newComponent;
}

Object::Object() {
	
}
void Object::ObjectMainloop() {
	for (map<string, Component*>::iterator it = components.begin(); it != components.end(); it++) {
		it->second->Mainloop();
	}
}

bool Object::HasComponent(string name) {
	if (components.find(name) != components.end()) {
		return true;
	}
	return false;
}


