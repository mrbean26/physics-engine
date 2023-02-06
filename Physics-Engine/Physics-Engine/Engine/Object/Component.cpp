#include <Engine/Object/Component.h>
#include <Engine/Engine.h>

void Component::Mainloop() {

}

Object* Component::ParentObject() {
	return PhysicsEngine::FindSceneObject(ParentObjectName);
}