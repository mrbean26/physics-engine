#include <Engine/Object/Object.h>

#include <iostream>
using namespace std;

Object::Object() {
	
}
void Object::ObjectMainloop() {
	for (map<const char*, Component*>::iterator it = components.begin(); it != components.end(); it++) {
		it->second->Mainloop();
		
	}
}

bool Object::HasComponent(const char* name) {
	if (components.find(name) != components.end()) {
		return true;
	}
	return false;
}

void Object::AddComponent(const char * componentName) {
	Component* newComponent = nullptr;

	if (componentName == "Camera") {
		allComponents.camera = Camera();
		newComponent = &allComponents.camera;
	}
	if (componentName == "Collider") {
		allComponents.collider = Collider();
		newComponent = &allComponents.collider;
	}
	if (componentName == "DirectionalLight") {
		allComponents.directionalLight = DirectionalLight();
		newComponent = &allComponents.directionalLight;
	}
	if (componentName == "PointLight") {
		allComponents.pointLight = PointLight();
		newComponent = &allComponents.pointLight;
	}
	if (componentName == "Transform") {
		allComponents.transform = Transform();
		newComponent = &allComponents.transform;
	}
	if (componentName == "ViewModel") {
		allComponents.viewModel = ViewModel();
		newComponent = &allComponents.viewModel;
	}

	newComponent->componentObjectParentName = name;
	newComponent->parentObject = this;
	components.insert(make_pair(componentName, newComponent));
}
