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
	if (componentName == "AudioSource") {
		objectComponents->audioSource = AudioSource();
		newComponent = &objectComponents->audioSource;
	}
	if (componentName == "AudioListener") {
		objectComponents->audioListener = AudioListener();
		newComponent = &objectComponents->audioListener;
	}
	if (componentName == "Button") {
		objectComponents->button = Button();
		newComponent = &objectComponents->button;
	}
	if (componentName == "Text") {
		objectComponents->text = Text();
		newComponent = &objectComponents->text;
	}
	if (componentName == "Scrollbar") {
		objectComponents->scrollbar = Scrollbar();
		newComponent = &objectComponents->scrollbar;
	}
	if (componentName == "Dropdown") {
		objectComponents->dropdown = Dropdown();
		newComponent = &objectComponents->dropdown;
	}

	return newComponent;
}

Object::Object() {
	//AddComponent<Transform>();
}
void Object::ObjectMainloop() {
	for (unordered_map<string, Component*>::iterator it = components.begin(); it != components.end(); it++) {
		it->second->Mainloop();
	}
}