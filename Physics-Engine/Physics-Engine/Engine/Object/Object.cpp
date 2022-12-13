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

void Object::AddComponent(Component* newComponent, const char * componentName) {
	newComponent->componentObjectParentName = name;
	newComponent->parentObject = this;
	components.insert(make_pair(componentName, newComponent));
}
