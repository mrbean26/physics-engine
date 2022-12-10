#include <Engine/Scene/Scene.h>

#include <iostream>
using namespace std;


Scene::Scene() {

}
void Scene::SceneMainloop() {
	// Run Mainloop of All Objects
	for (map<int, Object>::iterator it = SceneObjects.begin(); it != SceneObjects.end(); it++) {
		it->second.ObjectMainloop();
	}
}

Object * Scene::CreateSceneObject() {
	Object newSceneObject = Object();
	
	// generate object ID
	int newID = 0;
	while (true) {
		// check if key exists
		if (SceneObjects.find(newID) == SceneObjects.end()) {
			break;
		}
		else {
			newID = rand();
		}
	}

	// insert
	SceneObjects.insert(make_pair(newID, newSceneObject));
	return &SceneObjects[newID];
}
Object * Scene::GetSceneObjectByID(int ID) {
	return &SceneObjects[ID];
}