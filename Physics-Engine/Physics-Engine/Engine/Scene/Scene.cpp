#include <Engine/Scene/Scene.h>

Scene::Scene() {

}
void Scene::SceneMainloop() {
	// Run Mainloop of All Objects
	for (map<int, Object>::iterator it = SceneObjects.begin(); it != SceneObjects.end(); it++) {
		it->second.ObjectMainloop();
	}
}