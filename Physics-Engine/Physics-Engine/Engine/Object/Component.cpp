#include <Engine/Object/Component.h>
#include <Engine/Engine.h>

void Component::Mainloop() {

}

Object* Component::ParentObject() {
	return PhysicsEngine::loadedScenes[PhysicsEngine::currentScene].GetSceneObjectByID(ParentObjectName);
}