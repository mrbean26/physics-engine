#pragma once

#include <vector>
using namespace std;

/* STEPS FOR ADDING COMPONENT
1. Add Vector<Component> into .cpp file of new component
2. Add static function addComponent() into component's class
3. define function as adding to vector then returning pointer of item in vector
*/

class Object;

class Component {
public:
	bool initialised = false;
	const char* componentObjectParentName;

	virtual void Mainloop();
	Object* parentObject;
};

#include <Engine/Object/Object.h>
