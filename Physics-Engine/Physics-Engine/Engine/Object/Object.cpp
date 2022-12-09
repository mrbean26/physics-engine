#include <Engine/Object/Object.h>
#include <iostream>
using namespace std;
Object::Object() {

}
void Object::ObjectMainloop() {
	cout << "HI1" << endl;
	for (map<const char*, Component*>::iterator it = components.begin(); it != components.end(); it++) {
		it->second->Mainloop();
	}
}