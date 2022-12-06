#include <Engine/Object/Object.h>

Object::Object() {

}
void Object::ObjectMainloop() {
	for (map<const char*, Component>::iterator it = components.begin(); it != components.end(); it++) {
		it->second.Mainloop();
	}
}