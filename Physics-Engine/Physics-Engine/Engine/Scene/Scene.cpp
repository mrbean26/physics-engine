#include <Engine/Scene/Scene.h>

#include <Engine/Components/Transform.h>

#include <iostream>
using namespace std;


Scene::Scene() {

}
void Scene::SceneMainloop() {
	// Run Mainloop of All Objects
	for (map<const char*, Object>::iterator it = SceneObjects.begin(); it != SceneObjects.end(); it++) {
		it->second.ObjectMainloop();
	}
}

Object * Scene::CreateSceneObject(const char * name) {
	Object newSceneObject = Object();
	newSceneObject.name = name;

	//Transform newTransform = Transform();
	//newSceneObject.AddComponent(&newTransform, "Transform");

	// insert
	SceneObjects.insert(make_pair(name, newSceneObject));
	return &SceneObjects[name];
}
Object * Scene::GetSceneObjectByID(const char * name) {
	return &SceneObjects[name];
}